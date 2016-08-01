#include "math3d.h"

namespace math3d
{
	const float2 float2::ZERO(0.0f, 0.0f);
	const float2 float2::ONE(1.0f, 1.0f);
	const float2 float2::UNIT_X(1.0f, 0.0f);
	const float2 float2::UNIT_Y(0.0f, 1.0f);
	const float2 float2::UNIT_AXIS[2] = { float2::UNIT_X, float2::UNIT_Y };

	const float3 float3::ZERO(0.0f, 0.0f, 0.0f);
	const float3 float3::ONE(1.0f, 1.0f, 1.0f);
	const float3 float3::UNIT_X(1.0f, 0.0f, 0.0f);
	const float3 float3::UNIT_Y(0.0f, 1.0f, 0.0f);
	const float3 float3::UNIT_Z(0.0f, 0.0f, 1.0f);
	const float3 float3::UNIT_AXIS[3] = { float3::UNIT_X, float3::UNIT_Y, float3::UNIT_Z };

	const float4 float4::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
	const float4 float4::ONE(1.0f, 1.0f, 1.0f, 1.0f);
	const float4 float4::UNIT_X(1.0f, 0.0f, 0.0f, 0.0f);	
	const float4 float4::UNIT_Y(0.0f, 1.0f, 0.0f, 0.0f);	
	const float4 float4::UNIT_Z(0.0f, 0.0f, 1.0f, 0.0f);	
	const float4 float4::UNIT_W(0.0f, 0.0f, 0.0f, 1.0f);
	const float4 float4::UNIT_XW(1.0f, 0.0f, 0.0f, 1.0f);
	const float4 float4::UNIT_YW(0.0f, 1.0f, 0.0f, 1.0f);
	const float4 float4::UNIT_ZW(0.0f, 0.0f, 1.0f, 1.0f);
	const float4 float4::UNIT_AXIS[4] = { float4::UNIT_X, float4::UNIT_Y, float4::UNIT_Z, float4::UNIT_W };
	const float4 float4::UNIT_AXIS_W[3] = { float4::UNIT_XW, float4::UNIT_YW, float4::UNIT_ZW };


	const quaternion quaternion::IDENTITY(0.0f, 0.0f, 0.0f, 1.0f);


	const float2x2 float2x2::ZERO
		(0.0f, 0.0f,
		 0.0f, 0.0f);

	const float2x2 float2x2::IDENTITY
		(1.0f, 0.0f,
		 0.0f, 1.0f);

	
	const float3x3 float3x3::ZERO
		(0.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 0.0f);

	const float3x3 float3x3::IDENTITY
		(1.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 1.0f);


	const float4x4 float4x4::ZERO
		(0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 0.0f, 0.0f);

	const float4x4 float4x4::IDENTITY
		(1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f, 0.0f, 0.0f, 1.0f);
}