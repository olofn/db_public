#pragma once

#define _USE_MATH_DEFINES 
#include <math.h>

class Chorus
{
public:
	Chorus() :
	  writePointer(0),
	  phase(0.0f)
	{
		for(int i = 0; i < BUFFER_SIZE; i++)
		{
			buffer[i] = 0.0f;
		}
	}

	void process(float *left, float *right, int length, float depth, float rate, float wet, float leftGain, float rightGain)
	{
		for(int i = 0; i < length; i++)
		{
			float in = left[i];
			put(in);
			phase = fmodf(phase + rate, 1.0f);
			float delayLeft = depth * BUFFER_SIZE * (0.45f + sinf(phase * (float)M_PI * 2) * 0.4f);
			float delayRight = depth * BUFFER_SIZE * (0.45f + cosf(phase * (float)M_PI * 2) * 0.4f);
			left[i] = (wet * get(delayLeft) + in) * leftGain;
			right[i] = (wet * get(delayRight) + in) * rightGain;
		}
	}

private:
	void put(float s) {
		buffer[writePointer] = s;
		writePointer = (writePointer + 1) % BUFFER_SIZE;
	}

	float get(float t) {
		t = writePointer - t + 2 * BUFFER_SIZE;
		int r = (int)t;
		float f = t - r;
		return buffer[r % BUFFER_SIZE] * (1.0f - f) + buffer[(r + 1) % BUFFER_SIZE] * f;
	}

	static const int BUFFER_SIZE = 512;
	int writePointer;
	float buffer[BUFFER_SIZE];
	float phase;

};