#pragma once
#ifndef __math3d_vectorfunc_h__
#define __math3d_vectorfunc_h__

namespace math3d
{
	inline bool floatIsZero(float2 a) { return floatIsZero(a.x) && floatIsZero(a.y); }
	inline bool floatIsZero(float3 a) { return floatIsZero(a.x) && floatIsZero(a.y) && floatIsZero(a.z); }
	inline bool floatIsZero(float4 a) { return floatIsZero(a.x) && floatIsZero(a.y) && floatIsZero(a.z) && floatIsZero(a.w); }
	
	inline bool floatEq(float2 a, float2 b)	{ return floatEq(a.x, b.x) && floatEq(a.y, b.y); }
	inline bool floatEq(float3 a, float3 b)	{ return floatEq(a.x, b.x) && floatEq(a.y, b.y) && floatEq(a.z, b.z); }
	inline bool floatEq(float4 a, float4 b) { return floatEq(a.x, b.x) && floatEq(a.y, b.y) && floatEq(a.z, b.z) && floatEq(a.w, b.w); }

	inline float dot(float2 a, float2 b) { return a.x * b.x + a.y * b.y; }
	inline float dot(float3 a, float3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	inline float dot(float4 a, float4 b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

	inline float3 cross(float3 a, float3 b)
	{
		return float3(a.y * b.z - b.y * a.z,
			          a.z * b.x - b.z * a.x,
					  a.x * b.y - b.x * a.y);
	}

	inline float length(float2 v) { return std::sqrtf(dot(v, v)); }
	inline float length(float3 v) { return std::sqrtf(dot(v, v)); }
	inline float length(float4 v) { return std::sqrtf(dot(v, v)); }

	inline float lengthSquared(float2 v) { return dot(v, v); }
	inline float lengthSquared(float3 v) { return dot(v, v); }
	inline float lengthSquared(float4 v) { return dot(v, v); }

	inline float lengthCompare(float2 a, float b) { return b >= 0.0f ? lengthSquared(a) - square(b) : lengthSquared(a) + square(b); }
	inline float lengthCompare(float3 a, float b) { return b >= 0.0f ? lengthSquared(a) - square(b) : lengthSquared(a) + square(b); }
	inline float lengthCompare(float4 a, float b) { return b >= 0.0f ? lengthSquared(a) - square(b) : lengthSquared(a) + square(b); }
	inline float lengthCompare(float b, float2 a) { return b >= 0.0f ? square(b) - lengthSquared(a) : -square(b) - lengthSquared(a); }
	inline float lengthCompare(float b, float3 a) { return b >= 0.0f ? square(b) - lengthSquared(a) : -square(b) - lengthSquared(a); }
	inline float lengthCompare(float b, float4 a) { return b >= 0.0f ? square(b) - lengthSquared(a) : -square(b) - lengthSquared(a); }
	inline float lengthCompare(float2 a, float2 b) { return lengthSquared(a) - lengthSquared(b); }
	inline float lengthCompare(float3 a, float3 b) { return lengthSquared(a) - lengthSquared(b); }
	inline float lengthCompare(float4 a, float4 b) { return lengthSquared(a) - lengthSquared(b); }

	inline float2 sincos(float a) { return float2(std::cos(a), std::sin(a)); }
	inline float atan2(float2 a) { return std::atan2(a.y, a.x); }

	// TODO: De-template
	inline float2 normalize(float2 v, float2 ifZero = float2::UNIT_X)
	{
		float l = length(v);
		return floatIsZero(l) ? ifZero : v / l;
	}

	inline float3 normalize(float3 v, float3 ifZero = float3::UNIT_X)
	{
		float l = length(v);
		return floatIsZero(l) ? ifZero : v / l;
	}

	inline float4 normalize(float4 v, float4 ifZero = float4::UNIT_X)
	{
		float l = length(v);
		return floatIsZero(l) ? ifZero : v / l;
	}

	inline float4 homogenize(float4 v)
	{
		if (!floatIsZero(v.w))
		{
			float wi = 1.0f / v.w;
			return float4(v.x * wi, v.y * wi, v.z * wi, 1.0f);
		}
		else
		{
			return v;
		}
	}

	template<class T>
	inline T lerp(T a, T b, float t)
	{
		return a * (1.0f - t) + b * t;
	}

	template<class T>
	inline T step(T a, T b, float t)
	{
		t = clamp(t, 0.0f, 1.0f);
		return lerp(a, b, t);
	}

	template<class T>
	inline T step(T a, T b, float t, float tMin, float tMax)
	{
		return step(a, b, (t - tMin) / (tMax - tMin));
	}

	template<class T>
	inline T smoothstep(T a, T b, float t)
	{
		t = clamp(t, 0.0f, 1.0f);
		t = t * t * (3 - 2 * t);
		return lerp(a, b, t);
	}

	template<class T>
	inline T smoothstep(T a, T b, float t, float tMin, float tMax)
	{
		return smoothstep(a, b, (t - tMin) / (tMax - tMin));
	}

	// TODO: De-template nlerp and slerp

	template<class T>
	inline T nlerp(T a, T b, float t, bool flipObtuse = false)
	{
		if (flipObtuse && dot(a, b) < 0.0f)
			t = -t;

		return normalize(lerp(a, b, t));
	}

	template<class T>
	inline T slerp(T a, T b, float t, bool flipObtuse = false)
	{
		double dp = dot(a, b);

		if (flipObtuse && dp < 0.0f)
		{
			b = -b;
			dp = -dp;
		}

		const double DOT_THRESHOLD = 0.9995;
		if (dp > DOT_THRESHOLD)
			return normalize(lerp(a, b, t)); 

		dp = clamp(dp, -1.0f, 1.0f);

		// angle between input vectors
		double theta0 = std::acos(dp);

		// angle between a and result
		double theta = theta0 * t;

		// { a, v } as an orthonormal basis
		T v = b – a * dp;
		v.normalize();

		return a * (float)cos(theta) + v * (float)sin(theta);
	}
}

#endif