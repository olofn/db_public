#pragma once

#include "util.h"

class Envelope {
public:
	Envelope() :
		currentValue(0),
		state(RELEASE)
	{}
	

	float process(float a, float d, float s, float r, float dt) {
		switch(state) {
		case ATTACK:
			{
				currentValue += dt / (a + 0.00001f);
				if (currentValue >= 1.0f) {
					currentValue = 1.0f;
					state = DECAY;				
				}
			}
			break;

		case DECAY:
			{
				currentValue = expFalloff(currentValue, s, 2.0f / (d + 0.001f), dt);
			//	float toSustain = currentValue - s;
			//	currentValue -= (toSustain * powf(2.0f, -d * dt * 1000.0f));
			}
			break;

		case RELEASE:
			{
				currentValue = expFalloff(currentValue, 0.0f, 2.0f / (r + 0.001f), dt);
				//currentValue *= 1.0f - powf(2.0f, -r * dt * 1000.0f);
			}
			break;
		}

		return currentValue;
	}

	void gateOn() {
		state = ATTACK;
	}

	void gateOff() {
		state = RELEASE;
	}
	
	float currentValue;	

	enum State {
		ATTACK,
		DECAY,
		RELEASE
	};

	State state;
};