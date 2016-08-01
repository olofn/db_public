#pragma once
#ifndef __math3d_matrix_h__
#define __math3d_matrix_h__


#include <algorithm>

namespace math3d
{
	class float2x2
	{
	public:
		static const int NUM_COLUMNS = 2;
		static const int NUM_ROWS = 2;
		static const int NUM_VALUES = NUM_COLUMNS * NUM_ROWS;

		static const float2x2 ZERO;
		static const float2x2 IDENTITY;

		inline float2x2() 
		{
			*this = IDENTITY;
		}

		inline float2x2(float m00, float m01, 
		                float m02, float m03)
		{
			m[0] = m00;  m[1] = m01;  
			m[2] = m02;  m[3] = m03;
		}

		inline explicit float2x2(float *m)
		{
			for (int i = 0; i < NUM_VALUES; i++)
				this->m[i] = m[i];
		}

		inline float& at(int col, int row) { return m[col + row * NUM_COLUMNS]; }
		inline const float& at(int col, int row) const { return m[col + row * NUM_COLUMNS]; }
		inline float& operator[](int i) { return m[i]; }
		inline float operator[](int i) const { return m[i]; }
		inline float2 getRow(int i) const { return float2(m + i * NUM_COLUMNS); }
		inline void setRow(int i, float2 v) { at(i, 0) = v.x; at(i, 1) = v.y; }
		inline float2 getColumn(int i) const { return float2(at(i, 0), at(i, 1)); }
		inline void setColumn(int i, float2 v) { at(0, i) = v.x; at(1, i) = v.y; }
		
		inline static float2x2 makeRotation(float angle)
		{
			float sina = std::sin(angle);
			float cosa = std::cos(angle);

			return float2x2(cosa, -sina, 
			                sina, cosa);
		}

		inline static float2x2 makeScale(float s)
		{
			return float2x2(   s, 0.0f,
			                0.0f,    s);
		}

		inline static float2x2 makeScale(float2 v)
		{
			return float2x2( v.x, 0.0f,
                            0.0f,  v.y);
		}

	private:
		float m[NUM_VALUES];
	};

	class float3x3
	{
	public:
		static const int NUM_COLUMNS = 3;
		static const int NUM_ROWS = 3;
		static const int NUM_VALUES = NUM_COLUMNS * NUM_ROWS;

		static const float3x3 ZERO;
		static const float3x3 IDENTITY;

		inline float3x3() 
		{
			*this = IDENTITY;
		}

		inline float3x3(float m0, float m1, float m2,
			            float m3, float m4, float m5,
						float m6, float m7, float m8)
		{
			m[0] = m0;  m[1] = m1;  m[2] = m2;
			m[3] = m3;  m[4] = m4;  m[5] = m5;
			m[6] = m6;  m[7] = m7;  m[8] = m8;
		}

		inline explicit float3x3(float *m)
		{
			for (int i = 0; i < NUM_VALUES; i++)
				this->m[i] = m[i];
		}

		inline float& at(int col, int row) { return m[col + row * NUM_COLUMNS]; }
		inline float at(int col, int row) const { return m[col + row * NUM_COLUMNS]; }
		inline float& operator[](int i) { return m[i]; }
		inline float operator[](int i) const { return m[i]; }
		inline float3 getRow(int i) const { return float3(m + i * NUM_COLUMNS); }
		inline void setRow(int i, float3 v) { at(i, 0) = v.x; at(i, 1) = v.y; at(i, 2) = v.z; }
		inline float3 getColumn(int i) const { return float3(at(i, 0), at(i, 1), at(i, 2)); }
		inline void setColumn(int i, float3 v) { at(0, i) = v.x; at(1, i) = v.y; at(2, i) = v.z; }
		
		inline static float3x3 makeRotation(quaternion q);
		inline static float3x3 makeAxisAngleRotation(float3 axis, float angle);
		inline static float3x3 makeEulerAngleRotation(float xAngle, float yAngle, float zAngle);
		inline static float3x3 makeEulerAngleRotation(float3 angles);
		inline static float3x3 makeScale(float s);
		inline static float3x3 makeScale(float3 v);

	private:
		float m[NUM_VALUES];
	};

	class float4x4
	{
	public:
		static const int NUM_COLUMNS = 4;
		static const int NUM_ROWS = 4;
		static const int NUM_VALUES = NUM_COLUMNS * NUM_ROWS;

		static const float4x4 ZERO;
		static const float4x4 IDENTITY;

		inline float4x4() 
		{
			*this = IDENTITY;
		}

		inline float4x4(float m00, float m01, float m02, float m03,
			            float m04, float m05, float m06, float m07,
						float m08, float m09, float m10, float m11,
						float m12, float m13, float m14, float m15)
		{
			m[0] = m00;  m[1] = m01;  m[2] = m02;  m[3] = m03;
			m[4] = m04;  m[5] = m05;  m[6] = m06;  m[7] = m07;
			m[8] = m08;  m[9] = m09;  m[10] = m10; m[11] = m11;
			m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
		}

		inline explicit float4x4(float *m)
		{
			for (int i = 0; i < NUM_VALUES; i++)
				this->m[i] = m[i];
		}

		inline float& at(int col, int row) { return m[col + row * NUM_COLUMNS]; }
		inline float at(int col, int row) const { return m[col + row * NUM_COLUMNS]; }
		inline float& operator[](int i) { return m[i]; }
		inline float operator[](int i) const { return m[i]; }
		inline float4 getRow(int i) const { return float4(m + i * NUM_COLUMNS); }
		inline void setRow(int i, float4 v) { at(i, 0) = v.x; at(i, 1) = v.y; at(i, 2) = v.z; at(i, 3) = v.w; }
		inline float4 getColumn(int i) const { return float4(at(i, 0), at(i, 1), at(i, 2), at(i, 3)); }
		inline void setColumn(int i, float4 v) { at(0, i) = v.x; at(1, i) = v.y; at(2, i) = v.z; at(3, i) = v.w; }
		
		inline float3x3 getTopLeft3x3()
		{
			return float3x3
				(m[0], m[1], m[2],
				 m[4], m[5], m[6],
				 m[8], m[9], m[10]);
		}
		
		inline static float4x4 makeTranslation(float3 t)
		{
			return float4x4
				(1.0f, 0.0f, 0.0f, t.x,
				 0.0f, 1.0f, 0.0f, t.y,
				 0.0f, 0.0f, 1.0f, t.z,
				 0.0f, 0.0f, 0.0f, 1.0f);
		}

		inline static float4x4 makeRotation(quaternion q)
		{
			float xx = q.x * q.x;
			float xy = q.x * q.y;
			float xz = q.x * q.z;
			float xw = q.x * q.w;
			float yy = q.y * q.y;
			float yz = q.y * q.z;
			float yw = q.y * q.w;
			float zz = q.z * q.z;
			float zw = q.z * q.w;

			float a = 1 - 2 * (yy + zz);
			float b = 2 * (xy - zw);
			float c = 2 * (xz + yw);

			float d = 2 * (xy + zw);
			float e = 1 - 2 * (xx + zz);
			float f = 2 * (yz - xw);

			float g = 2 * (xz - yw);
			float h = 2 * (yz + xw);
			float i = 1 - 2 * (xx + yy);

			return float4x4
				(   a,    b,    c, 0.0f,
				    d,    e,    f, 0.0f,
				    g,    h,    i, 0.0f,
				 0.0f, 0.0f, 0.0f, 1.0f);

		}

		inline static float4x4 makeAxisAngleRotation(float3 axis, float angle)
		{
			return makeRotation(quaternion::makeAxisAngleRotation(axis, angle));
		}

		inline static float4x4 makeEulerAngleRotation(float xAngle, float yAngle, float zAngle)
		{
			float a = cos(xAngle);
			float b = sin(xAngle);
			float c = cos(yAngle);
			float d = sin(yAngle);
			float e = cos(zAngle);
			float f = sin(zAngle);

			float ad = a * d;
			float bd = b * d;

			return float4x4
				(      c*e,      -c*f,   -d, 0.0f,
				 -bd*e+a*f,  bd*f+a*e, -b*c, 0.0f,
				  ad*e+b*f, -ad*f+b*e,  a*c, 0.0f, 
				      0.0f,      0.0f, 0.0f, 1.0f );
		}

		inline static float4x4 makeEulerAngleRotation(float3 angles)
		{
			return makeEulerAngleRotation(angles.x, angles.y, angles.z);
		}

		inline static float4x4 makeScale(float s)
		{
			return float4x4
				(   s, 0.0f, 0.0f, 0.0f,
				 0.0f,    s, 0.0f, 0.0f,
				 0.0f, 0.0f,    s, 0.0f,
				 0.0f, 0.0f, 0.0f, 1.0f);
		}

		inline static float4x4 makeScale(float3 v)
		{
			return float4x4
				( v.x, 0.0f, 0.0f, 0.0f,
				 0.0f,  v.y, 0.0f, 0.0f,
				 0.0f, 0.0f,  v.z, 0.0f,
				 0.0f, 0.0f, 0.0f, 1.0f);
		}

	private:
		float m[NUM_VALUES];
	};

	

	inline float3x3 float3x3::makeRotation(quaternion q)
	{
		return float4x4::makeRotation(q).getTopLeft3x3();
	}

	inline float3x3 float3x3::makeAxisAngleRotation(float3 axis, float angle)
	{
		return float4x4::makeAxisAngleRotation(axis, angle).getTopLeft3x3();
	}

	inline float3x3 float3x3::makeEulerAngleRotation(float xAngle, float yAngle, float zAngle)
	{
		return float4x4::makeEulerAngleRotation(xAngle, yAngle, zAngle).getTopLeft3x3();
	}

	inline float3x3 float3x3::makeEulerAngleRotation(float3 angles)
	{
		return float4x4::makeEulerAngleRotation(angles).getTopLeft3x3();
	}

	inline float3x3 float3x3::makeScale(float s)
	{
		return float4x4::makeScale(s).getTopLeft3x3();
	}

	inline float3x3 float3x3::makeScale(float3 v)
	{
		return float4x4::makeScale(v).getTopLeft3x3();
	}




	inline float2x2 operator*(const float2x2 &a, const float2x2 &b)
	{
		float2x2 m;
		int i = 0;

		for(int col = 0; col < m.NUM_COLUMNS; col++)
		{
			for(int row = 0; row < m.NUM_ROWS; row++)
			{
				m[i++] = dot(a.getRow(row), b.getColumn(col));
			}
		}

		return m;
	}

	inline float3x3 operator*(const float3x3 &a, const float3x3 &b)
	{
		float3x3 m;
		int i = 0;

		for(int col = 0; col < m.NUM_COLUMNS; col++)
		{
			for(int row = 0; row < m.NUM_ROWS; row++)
			{
				m[i++] = dot(a.getRow(row), b.getColumn(col));
			}
		}

		return m;
	}

	inline float4x4 operator*(const float4x4 &a, const float4x4 &b)
	{
		float4x4 m;
		int i = 0;

		for(int col = 0; col < m.NUM_COLUMNS; col++)
		{
			for(int row = 0; row < m.NUM_ROWS; row++)
			{
				m[i++] = dot(a.getRow(row), b.getColumn(col));
			}
		}

		return m;
	}

	inline float2 operator*(const float2x2 &m, const float2 &v)
	{
		return float2(dot(m.getRow(0), v), 
		              dot(m.getRow(1), v));
	}

	inline float3 operator*(const float3x3 &m, const float3 &v)
	{
		return float3(dot(m.getRow(0), v), 
		              dot(m.getRow(1), v),
		              dot(m.getRow(2), v));
	}

	inline float4 operator*(const float4x4 &m, const float4 &v)
	{
		return float4(dot(m.getRow(0), v), 
		              dot(m.getRow(1), v),
		              dot(m.getRow(2), v), 
		              dot(m.getRow(3), v));
	}

	inline float2x2 operator*(const float2x2 &m, float s)
	{
		float2x2 r(m);
		
		for (int i = 0; i < r.NUM_VALUES; i++)
		{
			r[i] *= s;
		}

		return r;
	}

	inline float3x3 operator*(const float3x3 &m, float s)
	{
		float3x3 r(m);
		
		for (int i = 0; i < r.NUM_VALUES; i++)
		{
			r[i] *= s;
		}

		return r;
	}

	inline float4x4 operator*(const float4x4 &m, float s)
	{
		float4x4 r(m);
		
		for (int i = 0; i < r.NUM_VALUES; i++)
		{
			r[i] *= s;
		}

		return r;
	}

	inline float2x2 operator+(const float2x2 &a, const float2x2 &b)
	{
		float2x2 r(a);

		for (int i = 0; i < r.NUM_VALUES; i++)
		{
			r[i] += b[i];
		}

		return r;
	}

	inline float3x3 operator+(const float3x3 &a, const float3x3 &b)
	{
		float3x3 r(a);

		for (int i = 0; i < r.NUM_VALUES; i++)
		{
			r[i] += b[i];
		}

		return r;
	}

	inline float4x4 operator+(const float4x4 &a, const float4x4 &b)
	{
		float4x4 r(a);

		for (int i = 0; i < r.NUM_VALUES; i++)
		{
			r[i] += b[i];
		}

		return r;
	}

	inline float2x2 operator-(const float2x2 &a, const float2x2 &b)
	{
		float2x2 r(a);

		for (int i = 0; i < r.NUM_VALUES; i++)
		{
			r[i] -= b[i];
		}

		return r;
	}

	inline float3x3 operator-(const float3x3 &a, const float3x3 &b)
	{
		float3x3 r(a);

		for (int i = 0; i < r.NUM_VALUES; i++)
		{
			r[i] -= b[i];
		}

		return r;
	}

	inline float4x4 operator-(const float4x4 &a, const float4x4 &b)
	{
		float4x4 r(a);

		for (int i = 0; i < r.NUM_VALUES; i++)
		{
			r[i] -= b[i];
		}

		return r;
	}

	inline float2x2 operator-(const float2x2 &a) { return a * -1.0f; }
	inline float3x3 operator-(const float3x3 &a) { return a * -1.0f; }
	inline float4x4 operator-(const float4x4 &a) { return a * -1.0f; }

	inline float2x2 operator/(const float2x2 &m, float s) { return m * (1.0f / s); }
	inline float3x3 operator/(const float3x3 &m, float s) { return m * (1.0f / s); }
	inline float4x4 operator/(const float4x4 &m, float s) { return m * (1.0f / s); }

	inline float2x2 &operator+=(float2x2 &a, const float2x2 &b) { a = a + b; return a; }
	inline float3x3 &operator+=(float3x3 &a, const float3x3 &b) { a = a + b; return a; }
	inline float4x4 &operator+=(float4x4 &a, const float4x4 &b) { a = a + b; return a; }

	inline float2x2 &operator-=(float2x2 &a, const float2x2 &b) { a = a - b; return a; }
	inline float3x3 &operator-=(float3x3 &a, const float3x3 &b) { a = a - b; return a; }
	inline float4x4 &operator-=(float4x4 &a, const float4x4 &b) { a = a - b; return a; }

	inline float2x2 &operator*=(float2x2 &a, const float2x2 &b) { a = a * b; return a; }
	inline float3x3 &operator*=(float3x3 &a, const float3x3 &b) { a = a * b; return a; }
	inline float4x4 &operator*=(float4x4 &a, const float4x4 &b) { a = a * b; return a; }

	inline float2x2 &operator*=(float2x2 &m, float s) { m = m * s; return m; }
	inline float3x3 &operator*=(float3x3 &m, float s) { m = m * s; return m; }
	inline float4x4 &operator*=(float4x4 &m, float s) { m = m * s; return m; }
	
	inline float2x2 &operator/=(float2x2 &m, float s) { m = m / s; return m; }
	inline float3x3 &operator/=(float3x3 &m, float s) { m = m / s; return m; }
	inline float4x4 &operator/=(float4x4 &m, float s) { m = m / s; return m; }


	

	inline float4x4 transpose(const float4x4 &m)
	{
		return float4x4(m[0], m[4], m[8], m[12],
		                m[1], m[5], m[9], m[13],
						m[2], m[6], m[10], m[14], 
						m[3], m[7], m[11], m[15]);
	}

	inline float determinant(const float2x2 &m)
	{
		return m[0] * m[3] - m[1] * m[2];
	}

	inline float2x2 invert(const float2x2 &m, const float2x2 &ifDegenerate = float2x2::ZERO)
	{
		float det = determinant(m);

		if (floatIsZero(det))
		{
			return ifDegenerate;
		}

		return float2x2(m[3], -m[1], -m[2], m[0]) / det;
	}

	inline float4x4 invert(const float4x4 &m)
	{
		// TODO: Unbreak
		float2x2 a(m.at(0, 0), m.at(1, 0),
			       m.at(0, 1), m.at(1, 1));

		float2x2 b(m.at(2, 0), m.at(3, 0),
			       m.at(2, 1), m.at(3, 1));

		float2x2 c(m.at(0, 2), m.at(1, 2), 
			       m.at(0, 3), m.at(1, 3));

		float2x2 d(m.at(2, 2), m.at(3, 2),
			       m.at(2, 3), m.at(3, 3));

		float2x2 aInv = invert(a);
		float2x2 dcab = invert(d - c * aInv * b);
		float2x2 ab = aInv * b;		
		float2x2 ca = c * aInv;
		float2x2 dcabca = dcab * ca;

		float2x2 p = aInv + ab * dcabca;
		float2x2 q = -ab * dcab;
		float2x2 r = -dcabca;
		float2x2 s = dcab;

		return float4x4
			(p[0], p[1], q[0], q[1],
			 p[2], p[3], q[2], q[3],
			 r[0], r[1], s[0], s[1],
			 r[2], r[3], s[2], s[3]);
	}


	inline float3 transform(const float4x4 &m, const float3 &v, float w)
	{
		return (m * float4(v, w)).xyz();
	}

	template<class ItInOut>
	inline void transformMany(const float4x4 &m, ItInOut first, ItInOut last, float w)
	{
		for(ItInOut i = first; i != last; ++i)
		{
			*i = transform(m, *i, w);
		}
	}

	template<class ItOut, class ItIn>
	inline void transformMany(ItOut dest, const float4x4 &m, ItIn first, ItIn last, float w)
	{
		for(ItIn i = first; i != last; ++i)
		{
			*dest = transform(m, *i, w);
			++dest;
		}
	}

	inline bool floatEq(float2x2 a, float2x2 b) { return floatEq(a.getRow(0), b.getRow(0)) && floatEq(a.getRow(1), b.getRow(1)); }
	inline bool floatEq(float4x4 a, float4x4 b) { return floatEq(a.getRow(0), b.getRow(0)) && floatEq(a.getRow(1), b.getRow(1)) && floatEq(a.getRow(2), b.getRow(2)) && floatEq(a.getRow(3), b.getRow(3)); }
}

#endif