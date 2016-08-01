#pragma once
#ifndef __math3d_frame_h__
#define __math3d_frame_h__

namespace math3d
{
	class Frame
	{
	public:
		virtual ~Frame();

		virtual float3 transformToLocal(float3 v, float w) = 0;

		virtual float3 transformToParent(float3 v, float w) = 0;
		
		virtual float4 transformToLocal(float4 v)
		{
			return float4(transformToLocal(v.xyz(), v.w), v.w);
		}

		virtual float4 transformToParent(float4 v)
		{
			return float4(transformToParent(v.xyz(), v.w), v.w);
		}

		virtual float4x4 matrixToLocal() = 0;

		virtual float4x4 matrixToParent() = 0;
	};

	class FrameTR : public Frame
	{
	public:
		float3 translation;
		quaternion rotation;

		FrameTR() {}

		FrameTR(float3 translation, quaternion rotation) :
			translation(translation),
			rotation(rotation)
		{}

		float3 transformToLocal(float3 v, float w)
		{
			return transform(rotation, v) + translation * w;
		}

		float3 transformToParent(float3 v, float w)
		{
			return transformInverse(rotation, v - translation * w);
		}

		float4x4 matrixToLocal()
		{
			return float4x4::makeTranslation(translation) * float4x4::makeRotation(rotation);
		}

		float4x4 matrixToParent()
		{
			return float4x4::makeRotation(conjugate(rotation)) * float4x4::makeTranslation(-translation);
		}
	};
}

#endif