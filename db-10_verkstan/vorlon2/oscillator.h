#pragma once

#include <math.h>

class Oscillator
{
public:
	Oscillator() :
	  phase(0.0f)
	{}

	float get(float pps, float phaseOffset, float pulseFade)
	{
		float kernelSize = pps * 2.2f;
		float value = getBoxFilteredSaw(phase, kernelSize) - getBoxFilteredSaw(fmod(phase + phaseOffset, 1.0f), kernelSize) * pulseFade;
		phase = fmod(phase + pps, 1.0f);
		return value;
	}

	float getBoxFilteredSaw(float phase, float kernelSize)
	{
		float a, b;

		// Check if kernel is longer that one cycle
		if (kernelSize >= 1.0f) {
			return 0.0f;
		}

		// Remap phase and kernelSize from [0.0, 1.0] to [-1.0, 1.0]
		kernelSize *= 2.0f;
		phase = phase * 2.0f - 1.0f;

		if (phase + kernelSize > 1.0f)
		{
			// Kernel wraps around edge of [-1.0, 1.0]
			a = phase;
			b = phase + kernelSize - 2.0f;
		}
		else
		{
			// Kernel fits nicely in [-1.0, 1.0]
			a = phase;
			b = phase + kernelSize;
		}

		// Integrate and divide with kernelSize
		return (b * b - a * a) / (2.0f * kernelSize);
	}

/*
	float get(float pps, float phaseOffset, float pulseFade)
	{
		static const float LEAK = 0.99f + pulseFade * 0.0099999f;

		value = value + getPulseTrain(phase, pps) - getPulseTrain(fmod(phase + phaseOffset, 1.0f), pps) * pulseFade;
		value *= LEAK;
		
		phase = fmod(phase + pps, 1.0f);

		return value;;
	}*/
/*
/// TEMP
	static float pitchToFreq(float pitch)
	{
		return pow(2.0f, (pitch - 69.0f) / 12.0f) * 440.0f;
	}

	static void test() {
		static const int TESTLENGTH = 10000;
		
		for (int i = 0; i < 128; i++)
		{
			float freq = pitchToFreq((float)i);
			float pps = freq / 44100.0f;
			Oscillator o;
			float v = 0.0f;
			for (int j = 0; j < TESTLENGTH; j++) {
				v = v + o.get(pps);
			}
			System::Console::WriteLine(i + "; " + pps + "; " + v / TESTLENGTH);
		}
	}
// END TEMP
*/
private:
	float getPulseTrain(float phase, float pps)
	{
		return sinc((phase - 0.5f) / pps) - getAdjustment(pps);
	}

	float getAdjustment(float pps) {
		return (33368.46246f * pps + 15.0f) / 10000.0f;
	}

	float sinc(float x)
	{
		return x == 0.0f ? 1.0f : sin(x) / x;
	}

	
	//float value;
	float phase;
};