#ifndef DB_RANDOM
#define DB_RANDOM

class Random
{
public:
	Random();

	Random(int seed);

	void setSeed(int seed);

	// Returns random unsigned integer in the range [0,0xffffff]
	int getUInt();

	// Returns integer in the range [0,max) (not including max)
	int getInt(int max);
	
	// Returns integer in the range [min,max] (including max)
	int getInt(int min, int max);

	// Returns float in the range [-1.0f,1.0f]
	float getSFloat();

	// Returns float in the range [0.0f,1.0f]
	float getUFloat();

	// Gets a static Random instance
	static Random &get();

private:
	static Random staticRandom;
	static unsigned int autoSeed;

	unsigned int mirand;
};

#endif