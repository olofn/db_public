#pragma once
#ifndef __random_h__
#define __random_h__

#include "vector.h"

namespace math3d
{

	class Random
	{
	public:
		Random();

		Random(long long seed);


		long long getSeed();

		void setSeed(long long seed);


		bool getBool();


		int getInt();

		int getInt(int max);

		int getInt(int min, int max);


		float getFloat();

		float getFloat(float max);

		float getFloat(float min, float max);

		float getGaussianFloat();


		float2 getFloat2(float2 min, float2 max);

		float2 getFloat2(float maxRadius);

		float2 getFloat2(float minRadius, float maxRadius);

		float2 getGaussianFloat2();


		float3 getFloat3(float3 min, float3 max);

		float3 getFloat3(float maxRadius);

		float3 getFloat3(float minRadius, float maxRadius);

		float3 getGaussianFloat3();


		float4 getFloat4(float4 min, float4 max);

		float4 getFloat4(float maxRadius);

		float4 getFloat4(float minRadius, float maxRadius);

		float4 getGaussianFloat4();

	private:
		int next(int bits);
		
		static long long staticSeed;
		static const long long seedMask = ((1LL << 48LL) - 1);

		long long seed;
		float nextGaussian;
		bool haveNextGaussian;
	};
}

#endif