#include "channel.h"
#include "core/externals.hpp"
#include "core/util.hpp"

Channel::Channel(int sampleRate) :
	//currentNote(0),
	//currentPitch(0.0f),
	lastPitchWheelPos(0.0f),
	currentPitchWheelPos(0.0f),
	voiceBufferLength(0),
	voiceLeft(0),
	voiceRight(0)
{
	this->sampleRate = sampleRate;

	for (int i = 0; i < MAX_CONTROLLER; i++) {
		controllers[i] = 0.0f;
	}

	controllers[PITCHWHEEL] = 0.0f;
	controllers[MODWHEEL] = 0.0f;	

	controllers[VOLUME] = 0.5f;

	controllers[ATTACK] = 0.1f;
	controllers[DECAY] = 0.3f;
	controllers[SUSTAIN] = 0.7f;
	controllers[RELEASE] = 0.3f;

	controllers[PAN] = 0.5f;
	controllers[WAVEFORM] = 0.0f;
	controllers[CUTOFF] = 0.45f;
	controllers[RESONANCE] = 0.1f;
			
	controllers[DISTORTION] = 0.0f;
	controllers[CHORUS_AMT] = 0.0f;

	controllers[DELAY_TIME] = 0.5f;
	controllers[DELAY_AMT] = 0.0f;

	controllers[MOD_DECAY] = 0.5f;
	controllers[MOD_AMT] = 0.5f;

	controllers[DETUNE] = 0.0f;

	for (int i = 0; i < NUM_VOICES; i++)
	{
		voices[i] = new Voice(this);
	}
}

Channel::~Channel()
{
	for (int i = 0; i < NUM_VOICES; i++)
	{
		delete voices[i];
	}

	delete[] voiceLeft;
	delete[] voiceRight;
}

void Channel::noteOn(int note, float velocity)
{
	float detune = controllers[DETUNE] / 4.0f;
	int unison = detune == 0.0f ? 1 : 2;

	for (int i = 0; i < NUM_VOICES; i++)
	{
		if (voices[i]->currentNote == note)
		{
			voices[i]->noteOn(note, velocity, unison & 1 ? detune : -detune);
			
			unison--;

			if (!unison)
			{
				return;
			}
		}
	}

	for (int i = 0; i < NUM_VOICES; i++)
	{
		if (!voices[i]->isActive())
		{
			voices[i]->noteOn(note, velocity, unison & 1 ? detune : -detune);
			
			unison--;

			if (!unison)
			{
				return;
			}
		}
	}

	int last = -1;
	while(unison)
	{
		int v = rand() % NUM_VOICES; 

		if (v != last)
		{
			voices[v]->noteOn(note, velocity, unison & 1 ? detune : -detune);
			last = v;
			unison--;
		}
	}
}

void Channel::noteOff(int note, float velocity)
{
	for(int i = 0; i < NUM_VOICES; i++)
	{
		if (voices[i]->isActive() && voices[i]->currentNote == note)
		{
			voices[i]->noteOff();
		}
	}
}

void Channel::controllerChange(int controller, float value)
{
	controllers[controller] = value;
}

void Channel::pitchWheelChange(float value)
{
	controllers[PITCHWHEEL] = value;
}

void Channel::render(float *left, float *right, int length)
{
	allocateVoiceBuffers(length);

	float dt = length / (float)sampleRate;

	lastPitchWheelPos = currentPitchWheelPos;
	currentPitchWheelPos += (controllers[PITCHWHEEL] - currentPitchWheelPos) * powf(2, -dt * 400.0f);

	float lastLFO = lfo.get();
	float currentLFO = lfo.increment(controllers[MODWHEEL] * 7.0f + 4.0f, controllers[MODWHEEL] * 0.5f, dt);
	
	bool silence = true;

	for (int v = 0; v < NUM_VOICES; v++)
	{
		if (voices[v]->isActive())
		{
			silence = false;

			ZeroMemory(voiceLeft, sizeof(float) * length); 
			ZeroMemory(voiceRight, sizeof(float) * length);

			voices[v]->render(voiceLeft, voiceRight, length, dt, lastLFO, currentLFO);
			
			for (int i = 0; i < length; i++)
			{
				left[i] += voiceLeft[i];
				right[i] += voiceRight[i];
			}
		}
	}



	float volume = (controllers[VOLUME] * 1.5f) * (controllers[VOLUME] * 1.5f);
	float leftGain = volume * sqrt(1.0f - controllers[PAN]);
	float rightGain = volume * sqrt(controllers[PAN]);
	
	// TODO: Turn off chorus and delay if unneeded.
	// a simple silence check is not enough since they may
	// have data in their buffers

	if (controllers[CHORUS_AMT] > 0.0f)
	{
		// Chorus
		float wet = __min(controllers[CHORUS_AMT] * 2.0f, 1.0f);
		float depth = controllers[CHORUS_AMT] * controllers[CHORUS_AMT];
		float rate = (controllers[CHORUS_AMT] * controllers[CHORUS_AMT] + 0.5f) / sampleRate;
		chorus.process(left, right, length, depth, rate, wet, leftGain, rightGain);
	}
	else if (!silence)
	{
		// Volume, pan. Done by chorus effect if enabled.
		for (int i = 0; i < length; i++) {
			float in = left[i];
			left[i] = in * leftGain;
			right[i] = in * rightGain;
		}
	}

	// Delay
	{
		float feedback = controllers[DELAY_AMT] * controllers[DELAY_AMT] * 0.85f;
		float wet = controllers[DELAY_AMT] * 0.75f;
		delay.process(left, right, length, controllers[DELAY_TIME], feedback, wet);
	}
}

void Channel::reset()
{
	for (int i = 0; i < NUM_VOICES; i++)
	{
		voices[i]->noteOff();
	}
}

void Channel::allocateVoiceBuffers(int length)
{
	if (length == voiceBufferLength)
	{
		return;
	}

	voiceBufferLength = length;

	delete[] voiceLeft;
	delete[] voiceRight;

	voiceLeft = new float[length];
	voiceRight = new float[length];
}

Channel::Voice::Voice(Channel *channel_) :
	channel(channel_)
{
}

void Channel::Voice::noteOn(int note, float velocity, float detune)
{
	currentNote = note;
	currentPitch = note + detune;
	ampEnvelope.gateOn();
	modValue = 1.0f;	
	filter.reset();
}

void Channel::Voice::noteOff()
{
	ampEnvelope.gateOff();
}

void Channel::Voice::render(float *left, float *right, int length, float dt, float lastLFO, float currentLFO)
{
	float lastPitch = currentPitch;
    /*
	{
		float notesPerSec = 20.0f / (channel->controllers[GLIDE] + 0.001f);
		if (currentPitch < (float)currentNote)
		{
			currentPitch = min((float)currentNote, currentPitch + notesPerSec * dt);
		}
		else if (currentPitch > (float)currentNote)
		{
			currentPitch = max((float)currentNote, currentPitch - notesPerSec * dt);
		}
	}
    */


	float startModValue = modValue;
	
	{
		float d = channel->controllers[MOD_DECAY];
		modValue = expFalloff(modValue, 0.0f, 1.0f / (d * d + 0.001f), dt);
	}

	float modToPitch = 0.0f;
	float modToFilter = 0.0f;
	
	if (channel->controllers[MOD_AMT] < 0.495f)
	{
		modToPitch = (0.5f - channel->controllers[MOD_AMT]) * 2.0f;
		modToPitch = modToPitch * modToPitch * 48.0f;
	} 
	else if (channel->controllers[MOD_AMT] > 0.505f) 
	{
		modToFilter = (channel->controllers[MOD_AMT] - 0.5f) * 2.0f;
	}
	
	// Oscillator & amp envelope
	float startAmp = ampEnvelope.currentValue;
	float endAmp;

	{
		float a = channel->controllers[ATTACK];
		float d = channel->controllers[DECAY];
		float s = channel->controllers[SUSTAIN];
		float r = channel->controllers[RELEASE];
		endAmp = ampEnvelope.process(a * a, d * d, s, r * r, dt);
	}
	
	if (startAmp > (1.0f / 65536.0f) || endAmp > (1.0f / 65536.0f))
	{
		float startFreq = Channel::pitchToFreq(lastPitch + channel->lastPitchWheelPos * 7.0f + modToPitch * startModValue + lastLFO);
		float endFreq = Channel::pitchToFreq(currentPitch + channel->currentPitchWheelPos * 7.0f + modToPitch * modValue + currentLFO);
		float startPhasePerSample = startFreq / channel->sampleRate;
		float endPhasePerSample = endFreq / channel->sampleRate;			

		float phaseOffset = channel->controllers[WAVEFORM];
		float pulseFade = __min(channel->controllers[WAVEFORM] * 2.0f, 1.0f);
		
		if (channel->controllers[WAVEFORM] >= 1.0f)
		{
			// Noise
			for (int i = 0; i < length; i++) {
				float amp = (i * endAmp + (length - i) * startAmp) / length;				
			    left[i] = ((rand() / (float)RAND_MAX) - 0.5f) * amp * 2.0f;
			}
		}
		else
		{
			// Waveform
			for (int i = 0; i < length; i++) {
				float amp = (i * endAmp + (length - i) * startAmp) / length;
				float pps = (startPhasePerSample * (length - i) + endPhasePerSample * i) / length;
				left[i] = oscillator.get(pps, phaseOffset, pulseFade) * amp;
			}
		}
	}

	// Filter
	{
		float co;		
		Filter::Mode mode;

		if (channel->controllers[CUTOFF] > 0.5f)
		{
			mode = Filter::HIGHPASS;
			co = (channel->controllers[CUTOFF] - 0.5f) * 2.0f + modToFilter * modValue;
		}
		else
		{
			mode = Filter::LOWPASS;			
			co = channel->controllers[CUTOFF] * 2.0f + modToFilter * modValue;
		}

		float f = pow(16.0f, __max(__min(co, 1.2f), 0.0f)) * 2000.0f / channel->sampleRate;
		float q = sqrtf(channel->controllers[RESONANCE]) * 0.98f;

		filter.process(left, length, f, q, mode);
	}

	// Distortion
	if (channel->controllers[DISTORTION] > 0.0f)
	{
		float fade = __min(channel->controllers[DISTORTION] * 2.0f, 1.0f);
		for (int i = 0; i < length; i++) {
			float distorted = tanh(left[i] * 8.0f * channel->controllers[DISTORTION]);
			left[i] = fade * distorted + (1.0f - fade) * left[i];
		}
	}
}

bool Channel::Voice::isActive()
{
	return ampEnvelope.state != ampEnvelope.RELEASE || ampEnvelope.currentValue > (1.0f / 65536.0f) || filter.isActive();
}
