#include "random.hpp"
#include "util.hpp"

#include <ctime>

Random Random::staticRandom;
unsigned int Random::autoSeed;

Random::Random()
{
	unsigned int time = (unsigned int)std::time(0);
	setSeed(time + autoSeed);
	autoSeed = getUInt();
}

Random::Random(int seed)
{
	setSeed(seed);
}

void Random::setSeed(int seed)
{
	mirand = seed;
}

int Random::getUInt()
{
	mirand ^= 0x000f0000;
	mirand *= 16807;

	return mirand >> 8;
}

int Random::getInt(int max)
{
	return mod(getUInt(), max);
}

int Random::getInt(int min, int max)
{
	return min + getInt(max - min + 1);
}

float Random::getSFloat()
{
	unsigned int a = (getUInt() & 0x007fffff) | 0x40000000;
    return (*((float*)&a) - 3.0f);
}

float Random::getUFloat()
{
	return (getSFloat() + 1.0f) / 2.0f;
}

Random &Random::get()
{
	return staticRandom;
}

