#pragma once

#include "core/externals.hpp"

////////////////////////////////////////////////////////////////////
// Vector helpers
////////////////////////////////////////////////////////////////////

typedef D3DXVECTOR4 Vec4;
typedef D3DXVECTOR3 Vec3;
typedef D3DXVECTOR2 Vec2;

// Returns normalized vector
Vec3 normalize(const Vec3 &v);
Vec2 normalize(const Vec2 &v);

// Computes dot product
float dot(const Vec3 &v1, const Vec3 &v2);
float dot(const Vec2 &v1, const Vec2 &v2);

// Computes cross product
Vec3 cross(const Vec3 &v1, const Vec3 &v2);

// Computes length
float length(const Vec3 &v);
float length(const Vec2 &v);

// Computes squared length
float lengthSq(const Vec3 &v);
float lengthSq(const Vec2 &v);


////////////////////////////////////////////////////////////////////
// Random numbers
////////////////////////////////////////////////////////////////////

// Returns random float in [0, 1]
float frand();

// Returns random float in [min, max]
float frand(float min, float max);


////////////////////////////////////////////////////////////////////
// Number crunching helpers
////////////////////////////////////////////////////////////////////

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

template<typename T> inline T abs(T a) { return a < 0 ? -a : a; }
template<typename T> inline T min(T a, T b) { return a < b ? a : b; }
template<typename T> inline T max(T a, T b) { return a > b ? a : b; }
template<typename T> inline T clamp(T a, T min, T max) { return a < min ? min : (a > max ? max : a); }

inline float saturate(float a) { return clamp(a, 0.0f, 1.0f); }



#ifndef M_PI
#define M_PI 3.141592f
#endif