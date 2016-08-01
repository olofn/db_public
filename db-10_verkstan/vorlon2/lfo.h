#pragma once

#define _USE_MATH_DEFINES 
#include <math.h>

class LFO
{
public:
	LFO() :
	  phase(0.0f),
	  value(0.0f)
	{}

	float get()
	{
		return value;
	}

	float increment(float freq, float depth, float dt)
	{
		phase = fmod(phase + freq * dt, 1.0f);
		value = sinf(phase * 2.0f * (float)M_PI) * depth;
		return value;
	}
	
private:
	float phase;
	float value;
};