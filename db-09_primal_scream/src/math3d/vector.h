#pragma once
#ifndef __math3d_vector_h__
#define __math3d_vector_h__

namespace math3d
{
	class float2
	{
	public:
		static const int NUM_AXIS = 2;

		static const float2 ZERO;
		static const float2 ONE;
		static const float2 UNIT_X;
		static const float2 UNIT_Y;
		static const float2 UNIT_AXIS[2];
		
		float x, y;
		
		inline float2() : x(0.0f), y(0.0f) { }
		inline explicit float2(float xy) : x(xy), y(xy) { }
		inline float2(float x, float y) : x(x), y(y) { }	
		inline explicit float2(const float *d) : x(d[0]), y(d[1]) { }

		inline float &operator[](int i)
		{
			return ((float *)this)[i];
		}

		inline float operator[](int i) const
		{
			return ((float *)this)[i];
		}
	};


	class float3
	{
	public:
		static const int NUM_AXIS = 3;

		static const float3 ZERO;
		static const float3 ONE;
		static const float3 UNIT_X;
		static const float3 UNIT_Y;
		static const float3 UNIT_Z;
		static const float3 UNIT_AXIS[3];
		
		float x, y, z;

		inline float3() : x(0.0f), y(0.0f), z(0.0f) { }
		inline explicit float3(float xyz) : x(xyz), y(xyz), z(xyz) { }
		inline float3(float x, float y, float z) : x(x), y(y), z(z) { }
		inline float3(float2 xy, float z) : x(xy.x), y(xy.y), z(z) { }
		inline explicit float3(const float *d) : x(d[0]), y(d[1]), z(d[2]) { }

		inline float2& xy() { return *((float2 *)this); }
		inline const float2& xy() const { return *((float2 *)this); }

		inline float &operator[](int i)
		{
			return ((float *)this)[i];
		}

		inline float operator[](int i) const
		{
			return ((float *)this)[i];
		}
	};


	class float4
	{
	public:
		static const int NUM_AXIS = 4;

		static const float4 ZERO;  
		static const float4 ONE;   
		static const float4 UNIT_X;
		static const float4 UNIT_Y;
		static const float4 UNIT_Z;
		static const float4 UNIT_W;
		static const float4 UNIT_ZW;
		static const float4 UNIT_XW;
		static const float4 UNIT_YW;
		static const float4 UNIT_AXIS[4];
		static const float4 UNIT_AXIS_W[3];

		float x, y, z, w;

		inline float4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }		
		inline float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
		inline explicit float4(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
		inline float4(float2 xy, float z, float w) : x(xy.x), y(xy.y), z(z), w(w) { }
		inline float4(float3 xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
		inline explicit float4(const float *d) : x(d[0]), y(d[1]), z(d[2]), w(d[3]) { }

		inline float2& xy() { return *((float2 *)this); }
		inline float3& xyz() { return *((float3 *)this); }

		inline const float2& xy() const { return *((float2 *)this); }
		inline const float3& xyz() const { return *((float3 *)this); }

		inline float &operator[](int i)
		{
			return ((float *)this)[i];
		}

		inline float operator[](int i) const
		{
			return ((float *)this)[i];
		}
	};


	inline float2 operator*(float2 v, float s) { return float2(v.x * s, v.y * s); }
	inline float3 operator*(float3 v, float s) { return float3(v.x * s, v.y * s, v.z * s); }
	inline float4 operator*(float4 v, float s) { return float4(v.x * s, v.y * s, v.z * s, v.w * s); }

	inline float2 operator*(float s, float2 v) { return float2(v.x * s, v.y * s); }
	inline float3 operator*(float s, float3 v) { return float3(v.x * s, v.y * s, v.z * s); }
	inline float4 operator*(float s, float4 v) { return float4(v.x * s, v.y * s, v.z * s, v.w * s); }

	inline float2 operator/(float2 v, float s) { return v * (1.0f / s); }
	inline float3 operator/(float3 v, float s) { return v * (1.0f / s); }
	inline float4 operator/(float4 v, float s) { return v * (1.0f / s); }

	inline float2 operator+(float2 a, float2 b) { return float2(a.x + b.x, a.y + b.y); }
	inline float3 operator+(float3 a, float3 b) { return float3(a.x + b.x, a.y + b.y, a.z + b.z); }
	inline float4 operator+(float4 a, float4 b) { return float4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }

	inline float2 operator-(float2 a, float2 b) { return float2(a.x - b.x, a.y - b.y); }
	inline float3 operator-(float3 a, float3 b) { return float3(a.x - b.x, a.y - b.y, a.z - b.z); }
	inline float4 operator-(float4 a, float4 b) { return float4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }

	inline float2 operator-(float2 v) { return float2(-v.x, -v.y); }
	inline float3 operator-(float3 v) { return float3(-v.x, -v.y, -v.z); }
	inline float4 operator-(float4 v) { return float4(-v.x, -v.y, -v.z, -v.w); }

	inline const float2& operator+=(float2 &a, float2 b) { a.x += b.x; a.y += b.y; return a; }
	inline const float3& operator+=(float3 &a, float3 b) { a.x += b.x; a.y += b.y; a.z += b.z; return a; }
	inline const float4& operator+=(float4 &a, float4 b) { a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; return a; }

	inline const float2& operator-=(float2 &a, float2 b) { a.x -= b.x; a.y -= b.y; return a; }
	inline const float3& operator-=(float3 &a, float3 b) { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; }
	inline const float4& operator-=(float4 &a, float4 b) { a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; return a; }

	inline const float2& operator*=(float2 &a, float s) { a.x *= s; a.y *= s; return a; }
	inline const float3& operator*=(float3 &a, float s) { a.x *= s; a.y *= s; a.z *= s; return a; }
	inline const float4& operator*=(float4 &a, float s) { a.x *= s; a.y *= s; a.z *= s; a.w *= s; return a; }

	inline const float2& operator/=(float2 &a, float s) { return a *= 1.0f / s; }
	inline const float3& operator/=(float3 &a, float s) { return a *= 1.0f / s; }
	inline const float4& operator/=(float4 &a, float s) { return a *= 1.0f / s; }
}
#endif