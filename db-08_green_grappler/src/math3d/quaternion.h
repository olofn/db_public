#pragma once
#ifndef __math3d_quaternion_h__
#define __math3d_quaternion_h__

namespace math3d
{
	class quaternion : public float4
	{
	public:
		static const quaternion IDENTITY;

		inline quaternion() { }
		inline quaternion(float x, float y, float z, float w) : float4(x, y, z, w) { }
		inline quaternion(float3 v, float w) : float4(v, w) { }

		inline static quaternion makeAxisAngleRotation(float3 axis, float angle)
		{
			float s = sin(angle / 2.0f);
			float c = cos(angle / 2.0f);
			return quaternion(axis * s, c);
		}
	};

	inline quaternion operator*(quaternion v, float s) { return quaternion(v.x * s, v.y * s, v.z * s, v.w * s); }
	inline quaternion operator*(float s, quaternion v) { return quaternion(v.x * s, v.y * s, v.z * s, v.w * s); }
	inline quaternion operator/(quaternion v, float s) { return v * (1.0f / s); }
	inline quaternion operator+(quaternion a, quaternion b) { return quaternion(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	inline quaternion operator-(quaternion a, quaternion b) { return quaternion(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
	inline quaternion operator-(quaternion v) { return quaternion(-v.x, -v.y, -v.z, -v.w); }
	inline const quaternion& operator+=(quaternion &a, quaternion b) { a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; return a; }
	inline const quaternion& operator-=(quaternion &a, quaternion b) { a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; return a; }
	inline const quaternion& operator*=(quaternion &a, float s) { a.x *= s; a.y *= s; a.z *= s; a.w *= s; return a; }
	inline const quaternion& operator/=(quaternion &a, float s) { return a *= 1.0f / s; }

	inline quaternion operator*(quaternion a, quaternion b)
	{
		return quaternion(cross(a.xyz(), b.xyz()) + a.xyz() * b.w + b.xyz() * a.w, -dot(a.xyz(), b.xyz()) + a.w * b.w);
	}

	inline quaternion normalize(quaternion v, quaternion ifZero = quaternion::IDENTITY)
	{
		float l = length(v);
		return floatIsZero(l) ? ifZero : v / l;
	}

	inline quaternion conjugate(quaternion q)
	{
		return quaternion(-q.xyz(), q.w);
	}

	inline float3 transform(quaternion q, float3 v)
	{
		quaternion qc = conjugate(q);
		quaternion p(v, 0.0f);
		return (q * p * qc).xyz();
	}

	inline float3 transformInverse(quaternion q, float3 v)
	{
		quaternion qc = conjugate(q);
		quaternion p(v, 0.0f);
		return (qc * p * q).xyz();
	}

	inline float4 transform(quaternion q, float4 v)
	{
		quaternion qc = conjugate(q);
		quaternion p(v.xyz(), 0.0f);
		return float4((q * p * qc).xyz(), v.w);
	}

	inline float4 transformInverse(quaternion q, float4 v)
	{
		quaternion qc = conjugate(q);
		quaternion p(v.xyz(), 0.0f);
		return float4((qc * p * q).xyz(), v.w);
	}

	template<class ItInOut>
	inline void transformMany(quaternion q, ItInOut first, ItInOut last)
	{
		for(It i = first; i != last; ++i)
		{
			*i = transform(m, *i);
		}
	}

	template<class ItInOut>
	inline void transformInverseMany(quaternion q, ItInOut first, ItInOut last)
	{
		for(It i = first; i != last; ++i)
		{
			*i = transformInverse(m, *i);
		}
	}

	template<class ItOut, class ItIn>
	inline void transformMany(ItOut dest, quaternion q, ItIn first, ItIn last)
	{
		for(ItI i = first; i != last; ++i)
		{
			*dest = transform(m, *i);
			++dest;
		}
	}

	template<class ItOut, class ItIn>
	inline void transformInverseMany(ItOut dest, quaternion q, ItIn first, ItIn last)
	{
		for(ItI i = first; i != last; ++i)
		{
			*dest = transformInverse(m, *i);
			++dest;
		}
	}
}

#endif