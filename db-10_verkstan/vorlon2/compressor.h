#pragma once

class Compressor
{
public:
	Compressor(int samplerate);

	void process(float *left, float *right, int length, float threshold, float ratio, float attack, float release);

private:
	int samplerate;
	float currentGain;
};
