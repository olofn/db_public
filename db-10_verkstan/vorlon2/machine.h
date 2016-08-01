#pragma once

class Machine
{
public:
	virtual ~Machine() {}

	virtual void noteOn(int note, float velocity) = 0;

	virtual void noteOff(int note, float velocity) = 0;

	virtual void controllerChange(int controller, float value) = 0;

	virtual void pitchWheelChange(float value) = 0;

	virtual void render(float *left, float *right, int length) = 0;

	virtual void reset() = 0;
};