#pragma once

#include "machine.h"

class DrumBox : public Machine
{
public:
	DrumBox();

	~DrumBox();

	void noteOn(int note, float velocity);

	void noteOff(int note, float velocity);

	void controllerChange(int controller, float value);

	void pitchWheelChange(float value);

	void render(float *left, float *right, int length);

	void reset();

private:
	class Sample
	{
	public:
		Sample() :
		  data(0),
		  length(0),
		  readCursor(0),
		  playing(false),
		  volume(0.0f)
		{}
	    		
		float *data;
		int length;
		int readCursor;
		bool playing;
		float volume;
	};

	class KeyPosition
	{
	public:
		int position;
		float value;
	};

	static void generateSample(Sample &outSample, const KeyPosition *sampleKeys, const KeyPosition *noiseKeys, float sampleGain, float noiseGain, float f = 0.5f, float q = 0.3f);
	//static void ringmodSample(Sample &outSample, const Sample &inSample, float freq);
	static void cymbalFilter(float *data, int length);

	static const int NUM_SAMPLES = 4;
	static const KeyPosition sampleKeysSilent[];
	static const KeyPosition sampleKeysKick[]; 
	static const KeyPosition noiseKeysKick[];
	static const KeyPosition sampleKeysSnare[]; 
	static const KeyPosition noiseKeysSnare[];
	static const KeyPosition noiseKeysClap[];
	static const KeyPosition noiseKeysHatClosed[];
	Sample samples[NUM_SAMPLES];
};