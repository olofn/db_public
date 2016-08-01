#pragma once

#include "machine.h"
#include "oscillator.h"
#include "envelope.h"
#include "filter.h"
#include "chorus.h"
#include "delay.h"
#include "lfo.h"

class Channel : public Machine {
public:
	Channel(int sampleRate);

	~Channel();

	void noteOn(int note, float velocity);

	void noteOff(int note, float velocity);

	void controllerChange(int controller, float value);

	void pitchWheelChange(float value);

	void render(float *left, float *right, int length);	

	void reset();

private:
	static float pitchToFreq(float pitch)
	{
		return powf(2.0f, (pitch - 69.0f) / 12.0f) * 440.0f;
	}

	void allocateVoiceBuffers(int length);

	enum {
		MODWHEEL = 1,
		PITCHWHEEL = 128,

		VOLUME = 39,

		ATTACK = 11,
		DECAY = 12,
		SUSTAIN = 13,
		RELEASE = 14,

		PAN = 74,
		WAVEFORM = 71,
		CUTOFF = 73,
		RESONANCE = 72,
				
		DISTORTION = 10,
		CHORUS_AMT = 15,

		DELAY_TIME = 91,
		DELAY_AMT = 16,

		MOD_DECAY = 17,
		MOD_AMT = 93,		
				
		DETUNE = 18,

		MAX_CONTROLLER = 129
	};

	class Voice
	{
	public:
		Voice(Channel *channel);

		void noteOn(int note, float velocity, float detune);

		void noteOff();

		void render(float *left, float *right, int length, float dt, float lastLFO, float currentLFO);

		bool isActive();

		Channel *channel;
		int currentNote;
		float currentPitch;
		
		float modValue;

		Oscillator oscillator;
		Envelope ampEnvelope;
		Filter filter;
	};

	int sampleRate;
	float controllers[MAX_CONTROLLER];

	//int currentNote;
	//float currentPitch;
	float currentPitchWheelPos;
	float lastPitchWheelPos;

	//float modValue;

	//Oscillator oscillator;
	//Envelope ampEnvelope;
	//Filter filter;
	static const int NUM_VOICES = 8;
	Voice *voices[NUM_VOICES];
	Chorus chorus;
	Delay delay;
	LFO lfo;

	int voiceBufferLength;
	float *voiceLeft;
	float *voiceRight;
};