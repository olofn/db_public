#include "drumbox.h"
#include "filter.h"
#include "core/externals.hpp"

const DrumBox::KeyPosition DrumBox::sampleKeysSilent[] =
{
	{   -1, 0.00f}
};

const DrumBox::KeyPosition DrumBox::sampleKeysKick[] =
{
	{   0,  0.00f},
	{  66,  0.22f},
	{ 136, -0.22f},
	{ 235, -0.60f},
	{ 437,  0.85f},
	{ 732, -0.75f},
	{ 800, -0.75f},
	{1100,  0.60f},
	{1250,  0.15f},
	{1350,  0.00f},
	{1485, -0.25f},
	{1650, -0.10f},
	{1763, -0.10f},
	{1925,  0.00f},
	{2093,  0.15f},
	{2450, -0.05f},
	{2628,  0.02f},
	{2871, -0.08f},
	{3193,  0.08f},
	{3421, -0.02f},
	{3750,  0.00f},
	{4500,  0.00f},
	{  -1,  0.00f}
};

const DrumBox::KeyPosition DrumBox::noiseKeysKick[] =
{
	{   0,  0.20f},
	{  82,  0.05f},
	{ 111,  0.50f},
	{ 400,  0.15f},
	{1000,  0.03f},
	{3134,  0.00f},
	{  -1,  0.00f}
};

const DrumBox::KeyPosition DrumBox::sampleKeysSnare[] =
{
	{   0,  0.40f},
	{   9,  0.40f},
	{  72, -0.65f},
	{ 142,  0.70f},
	{ 208, -0.15f},
	{ 285, -0.50f},
	{ 400,  0.62f},
	{ 500, -0.72f},
	{ 600,  0.55f},
	{ 693, -0.30f},
	{ 750, -0.09f},
	{ 778, -0.11f},
	{ 894,  0.27f},
	{1018, -0.37f},
	{1107,  0.38f},
	{1155,  0.10f},
	{1257, -0.20f},
	{1347,  0.00f},
	{1416,  0.35f},
	{1516, -0.45f},
	{1625,  0.37f},
	{1744, -0.30f},
	{1978,  0.20f},
	{1900,  0.21f},
	{1921,  0.20f},
	{1953,  0.10f},
	{2017, -0.34f},
	{2150,  0.29f},
	{2243, -0.20f},
	{2379,  0.10f},
	{2450,  0.07f},
	{2532, -0.11f},
	{2589, -0.10f},
	{2675,  0.15f},
	{2795, -0.12f},
	{2858,  0.00f},
	{2958,  0.05f},
	{3044,  0.00f},
	{3109, -0.10f},
	{3227,  0.12f},
	{3319, -0.07f},
	{3450,  0.00f},
	{3544,  0.09f},
	{3590,  0.00f},
	{3646, -0.12f},
	{3750,  0.12f},
	{3867, -0.09f},
	{3958,  0.02f},
	{4054,  0.06f},
	{4160, -0.10f},
	{4265,  0.10f},
	{4384, -0.09f},
	{4484,  0.07f},
	{4586, -0.02f},
	{4732,  0.00f},
	{  -1,  0.00f}
};

const DrumBox::KeyPosition DrumBox::noiseKeysSnare[] =
{
	{    0, 1.00f},
	{  148, 0.20f},
	{  200, 0.60f},
	{  525, 0.20f},
	{  695, 0.30f},
	{ 1000, 0.30f},
	{ 3000, 0.10f},
	{ 5000, 0.05f},
	{ 7200, 0.01f},
	{10600, 0.00f},
	{   -1, 0.00f}
};				

const DrumBox::KeyPosition DrumBox::noiseKeysClap[] =
{
	{   0, 0.50f},
	{  60, 0.80f},
	{ 340, 0.10f},
	{ 372, 1.00f},
	{ 449, 1.00f},
	{ 640, 0.10f},
	{ 800, 0.08f},
	{ 885, 0.77f},
	{ 941, 0.77f},
	{1032, 0.30f},
	{1169, 0.20f},
	{1261, 0.05f},
	{1345, 0.88f},
	{2253, 0.60f},
	{2600, 0.40f},
	{2974, 0.30f},
	{3043, 0.10f},
	{3100, 0.25f},
	{3234, 0.10f},
	{3621, 0.23f},
	{7050, 0.00f},
	{7400, 0.00f},
	{  -1, 0.00f},
};

const DrumBox::KeyPosition DrumBox::noiseKeysHatClosed[] =
{
	{   0, 0.00f},
	{  20, 0.12f},
	{  50, 0.20f},
	{  65, 0.65f},
	{ 108, 0.90f},
	{ 411, 0.40f},
	{ 613, 0.50f},
	{ 900, 0.45f},
	{3200, 0.10f},
	{4200, 0.04f},
	{9831, 0.00f},
	{  -1, 0.00f},
};
				
DrumBox::DrumBox()
{
	// Kick
	generateSample(samples[0], sampleKeysKick,  noiseKeysKick,  1.5f, 0.6f);
	// Snare
	generateSample(samples[1], sampleKeysSnare, noiseKeysSnare, 1.4f, 0.4f);
	// Clap
	generateSample(samples[2], sampleKeysSilent, noiseKeysClap, 0.0f, 0.3f, 0.13f, 0.6f);
	// Hat closed
	generateSample(samples[3], sampleKeysSilent, noiseKeysHatClosed, 0.0f, 0.1f);

	// Kick
	Filter().process(samples[0].data, samples[0].length, 0.80f, 0.20f);
	
	// Snare
	Filter().process(samples[1].data, samples[1].length, 0.80f, 0.20f);

	// Clap
	Filter().process(samples[2].data, samples[2].length, 0.50f, 0.20f);

	// Hat closed
	cymbalFilter(samples[3].data, samples[3].length);
	Filter().process(samples[3].data, samples[3].length, 0.75f, 0.30f);		
	Filter().process(samples[3].data,               130, 0.60f, 0.30f);	
}

DrumBox::~DrumBox()
{
	for(int i = 0; i < NUM_SAMPLES; i++)
	{
		delete[] samples[i].data;
	}
}

void DrumBox::noteOn(int note, float velocity)
{
	int s = (note % 12) % NUM_SAMPLES;	
	samples[s].readCursor = 0;
	samples[s].playing = true;
	samples[s].volume = velocity * velocity * 2.0f;
}

void DrumBox::noteOff(int note, float velocity)
{
}

void DrumBox::controllerChange(int controller, float value)
{
}

void DrumBox::pitchWheelChange(float value)
{
}

void DrumBox::render(float *left, float *right, int length)
{
	for(int s = 0; s < NUM_SAMPLES; s++)
	{
		Sample &sample = samples[s];

		if (!sample.playing)
		{
			continue;
		}

		for(int i = 0; i < length; i++)
		{
			if (sample.readCursor >= sample.length)
			{
				sample.playing = false;
				sample.readCursor = 0;
				break;
			}

			left[i] += sample.data[sample.readCursor] * sample.volume;
			sample.readCursor++;
		}
	}

	for(int i = 0; i < length; i++)
	{
		right[i] = left[i];
	}
}

void DrumBox::reset()
{
}

void DrumBox::generateSample(Sample &outSample, const KeyPosition *sampleKeys, const KeyPosition *noiseKeys, float sampleGain, float noiseGain, float f, float q)
{
	outSample.length = 0;
	int numSampleKeys = 0;
	int numNoiseKeys = 0;

	{		
		int i = 0;
		while(true)
		{
			int pos = sampleKeys[i].position;
			if (pos < 0) break;
			numSampleKeys++;
			outSample.length = __max(outSample.length, pos);
			i++;
		}
	}

	{
		int i = 0;
		while(true)
		{
			int pos = noiseKeys[i].position;
			if (pos < 0) break;
			numNoiseKeys++;
			outSample.length = __max(outSample.length, pos);
			i++;
		}
	}

	outSample.data = new float[outSample.length];

	for(int i = 0; i < outSample.length; i++)
	{
		outSample.data[i] = 0.0f;
	}

	{
		for(int i = 0; i < numSampleKeys - 1; i++)
		{
			KeyPosition start = sampleKeys[i];
			KeyPosition end = sampleKeys[i + 1];
			int distance = end.position - start.position;

			for(int p = 0; p < distance; p++)
			{
				float val = (start.value * (distance - p) + end.value * p) / distance;
				outSample.data[p + start.position] += val * sampleGain;
			}
		}
		
		Filter filter;
		filter.process(outSample.data, outSample.length, 0.03f, 0.2f);
	}
/*
	int leftShift = 100;
	for(int i = 0; i < outSample.length; i++)
	{
		outSample.data[i] = i + leftShift >= outSample.length ? 0.0f : outSample.data[i + leftShift];
	}

*/

	float buf0 = 0.0f;
	float buf1 = 0.0f;

	float fb = q + q/(1.0f - f);

	float max = 0.0f;

	// TODO: Replace with a highpass filter
	for(int i = 0; i < numNoiseKeys - 1; i++)
	{
		KeyPosition start = noiseKeys[i];
		KeyPosition end = noiseKeys[i + 1];
		int distance = end.position - start.position;

		for(int p = 0; p < distance; p++)
		{
			float val = (start.value * (distance - p) + end.value * p) / distance;
		
            float noiseIn = ((rand() / (float)RAND_MAX) - 0.5f) * 2.0f;

			buf0 = buf0 + f * (noiseIn - buf0 + fb * (buf0 - buf1));
			buf1 = buf1 + f * (buf0 - buf1);

			float noiseOut = noiseIn - buf1;

	        outSample.data[p + start.position] += val * noiseOut * noiseGain;	
		}
	}


	for (int i = 0; i < outSample.length; i++)
	{
		max = __max(fabs(outSample.data[i]), max);
	}

	for (int i = 0; i < outSample.length; i++)
	{
		outSample.data[i] /= max;
	}
}

void DrumBox::cymbalFilter(float *data, int length)
{
	static const int NUM_PASSES = 20;

	//srand(3);

	for (int i = 0; i < NUM_PASSES; i++)
	{
        /* TODO Remove this comment when rand is in place.
		float co = rand() / (float)RAND_MAX;
		float f = pow(16.0f, co * 190.0f / 44100.0f);
		float q = 0.8f + (1.0f - co) * 0.19f;

		Filter().process(data, length, f, q, Filter::RESONANT);
        */
	}
}