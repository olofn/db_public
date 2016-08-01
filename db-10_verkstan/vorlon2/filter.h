#pragma once

class Filter {
public:
	Filter() :
	  buf0(0.0f), buf1(0.0f)
	{}

	enum Mode
	{
		LOWPASS,
		HIGHPASS,
		RESONANT
	};

	// TODO: Add freq2f : f = 2.0*sin(pi*freq/samplerate);
	void process(float *buffer, int length, float f, float q, Mode mode = LOWPASS);

	bool isActive();

	void reset();

private:
	float buf0, buf1;
};