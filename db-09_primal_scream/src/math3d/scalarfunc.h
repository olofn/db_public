#pragma once
#ifndef __math3d_scalarfunc_h__
#define __math3d_scalarfunc_h__

namespace math3d
{
	const float EPSILON = 0.0000001f;
	const float PI = 3.1415926535897932384626433832795f;
	const float TWO_PI = 2 * PI;
	const float HALF_PI = PI / 2;

	// TODO: clamp, saturate, max, min, abs for vectors and matrices(?) too!
	// TODO: De-template
	// TODO: Implement functions from http://msdn.microsoft.com/en-us/library/ee418344%28VS.85%29.aspx

	template<class T>
	inline T clamp(T t, T a, T b) { return t < a ? a : (t > b ? b : t); }

	inline float saturate(float a) { return a < 0.0f ? 0.0f : (a > 1.0f ? 1.0f : a); }
	inline double saturate(double a) { return a < 0.0 ? 0.0 : (a > 1.0 ? 1.0 : a); }

	template<class T>
	inline T max(T a, T b) { return a > b ? a : b; }

	template<class T>
	inline T min(T a, T b) { return a < b ? a : b; }
	
	template<class T>
	inline T abs(T a) {	return a > 0 ? a : -a; }

	inline bool floatIsZero(float a) { return abs(a) <= EPSILON; }
	
	inline bool floatEq(float a, float b) {	return abs(a - b) <= EPSILON * max(1.0f, max(abs(a), abs(b))); }		

	inline float square(float a) { return a * a; }
}

#endif