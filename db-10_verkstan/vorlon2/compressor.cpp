#include "compressor.h"

#include "core/externals.hpp"

Compressor::Compressor(int samplerate_) :
	samplerate(samplerate_),
	currentGain(1.0f)
{
}

void Compressor::process(float *left, float *right, int length, float threshold, float ratio, float attack, float release)
{
	float peak = 0.0f;
	for (int i = 0; i < length; i++)
	{
		peak = __max(peak, abs(left[i]));
	}

	for (int i = 0; i < length; i++)
	{
		peak = __max(peak, abs(left[i]));
	}

	float dt = length / (float)samplerate;
	float wantedGain = peak <= threshold ? 1.0f : threshold / peak;
	wantedGain = ratio * (wantedGain - 1.0f) + 1.0f;
	float toWanted = wantedGain - currentGain;
	float f = toWanted < 0.0f ? attack : release;
	float newGain = currentGain + (float)(toWanted * pow(2, -f * dt));

	for (int i = 0; i < length; i++)
	{
		float t = i / (float)length;
		float gain = currentGain * (1.0f - t) + newGain * t;
		left[i] = left[i] * gain;
		right[i] = right[i] * gain;
	}

	currentGain = newGain;
}
