#include "globals.hpp"

Vec3 normalize(const Vec3 &v)
{
	return v / length(v);
}

Vec2 normalize(const Vec2 &v)
{
	return v / length(v);
}

float dot(const Vec3 &v1, const Vec3 &v2)
{
	return D3DXVec3Dot(&v1, &v2);
}

float dot(const Vec2 &v1, const Vec2 &v2)
{
	return D3DXVec2Dot(&v1, &v2);
}

Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
	Vec3 res;
	return *D3DXVec3Cross(&res, &v1, &v2);
}

float length(const Vec3 &v)
{
	return D3DXVec3Length(&v);
}

float length(const Vec2 &v)
{
	return D3DXVec2Length(&v);
}

float lengthSq(const Vec3 &v)
{
	return D3DXVec3LengthSq(&v);
}

float lengthSq(const Vec2 &v)
{
	return D3DXVec2LengthSq(&v);
}

float frand()
{
	return rand() / (float)RAND_MAX;
}

float frand(float min, float max)
{
	return frand() * (max - min) + min;
}
