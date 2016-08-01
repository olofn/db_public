#include <ctime>
#include <cmath>

#include "random.h"
#include "scalarfunc.h"
#include "vectorfunc.h"

namespace math3d
{
	long long Random::staticSeed = 0;

	Random::Random() :
		haveNextGaussian(false)
	{
		seed = (long long)std::time(0) + staticSeed;
		staticSeed++;
	}

	Random::Random(long long seed) :
		haveNextGaussian(false)
	{		
		this->seed = seed & seedMask;
	}

	long long Random::getSeed()
	{
		return seed;
	}

	void Random::setSeed(long long seed)
	{
		this->seed = seed;
	}

	bool Random::getBool()
	{
		return next(1) != 0;
	}

	int Random::getInt()
	{
		return next(32);
	}

	int Random::getInt(int n)
	{
		if ((n & -n) == n)  // n is a power of 2
			return (int)((n * (long)next(31)) >> 31);

		int bits, val;
		do {
			bits = next(31);
			val = bits % n;
		} while(bits - val + (n-1) < 0);

		return val;
	}

	int Random::getInt(int min, int max)
	{
		return min + getInt(max - min);
	}

	float Random::getFloat()
	{
		return next(24) / ((float)(1 << 24));
	}

	float Random::getFloat(float max)
	{
		return getFloat() * max;
	}

	float Random::getFloat(float min, float max)
	{
		return min + getFloat() * (max - min);
	}

	float Random::getGaussianFloat()
	{
		if (haveNextGaussian) {
			haveNextGaussian = false;
			return nextGaussian;
		} else {
			float2 v;
			float s;
			
			do { 
				v = getFloat2(-float2::ONE, float2::ONE);
				s = lengthSquared(v);
			} while (s >= 1.0f || s == 0.0f);

			float multiplier = std::sqrt(-2 * std::log(s)/s);
			nextGaussian = v.y * multiplier;
			haveNextGaussian = true;
			return v.x * multiplier;
		}
	}

	float2 Random::getFloat2(float2 min, float2 max)
	{
		float2 range = max - min;
		return min + float2(getFloat() * range.x, getFloat() * range.y);
	}

	float2 Random::getFloat2(float maxRadius)
	{
		float2 result;
		do {
			result = getFloat2(-float2::ONE, float2::ONE);
		} while (lengthSquared(result) >= 1.0f);

		return result * maxRadius;
	}

	float2 Random::getFloat2(float minRadius, float maxRadius)
	{
		float2 v = getFloat2(1.0f);
		float ratio = minRadius / maxRadius;
		return lerp(v, normalize(v), ratio) * maxRadius;
	}

	float2 Random::getGaussianFloat2()
	{
		return float2(getGaussianFloat(), getGaussianFloat());
	}

	float3 Random::getFloat3(float3 min, float3 max)
	{
		float3 range = max - min;
		return min + float3(getFloat() * range.x, getFloat() * range.y, getFloat() * range.z);
	}

	float3 Random::getFloat3(float maxRadius)
	{
		float3 result;
		do {
			result = getFloat3(-float3::ONE, float3::ONE);
		} while (lengthSquared(result) >= 1.0f);

		return result * maxRadius;
	}

	float3 Random::getFloat3(float minRadius, float maxRadius)
	{
		float3 v = getFloat3(1.0f);
		float ratio = minRadius / maxRadius;
		return lerp(v, normalize(v), ratio) * maxRadius;
	}

	float3 Random::getGaussianFloat3()
	{
		return float3(getGaussianFloat(), getGaussianFloat(), getGaussianFloat());
	}

	float4 Random::getFloat4(float4 min, float4 max)
	{
		float4 range = max - min;
		return min + float4(getFloat() * range.x, getFloat() * range.y, getFloat() * range.z, getFloat() * range.w);
	}

	float4 Random::getFloat4(float maxRadius)
	{
		float4 result;
		do {
			result = getFloat4(-float4::ONE, float4::ONE);
		} while (lengthSquared(result) >= 1.0f);

		return result * maxRadius;
	}

	float4 Random::getFloat4(float minRadius, float maxRadius)
	{
		float4 v = getFloat4(1.0f);
		float ratio = minRadius / maxRadius;
		return lerp(v, normalize(v), ratio) * maxRadius;
	}

	float4 Random::getGaussianFloat4()
	{
		return float4(getGaussianFloat(), getGaussianFloat(), getGaussianFloat(), getGaussianFloat());
	}

	int Random::next(int bits) {
       seed = (seed * 0x5DEECE66DLL + 0xBLL) & seedMask;
       return (int)(seed >> (48 - bits));
	}
}