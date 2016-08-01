#pragma once

#include "Entity.hpp"

class Animation;

class ParticleSystem : public Entity
{
public:
	ParticleSystem(
		Animation* aAnimation,
		int aAnimationSpeed,
		int aLifeTime,
		int aBlinkTime,
		int aMinSpeed,
		int aMaxSpeed,
		int aNumParticles,
		float2 aInitialVel,
		float aGravity);
	virtual int getLayer(){return 3;}

	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	virtual void setPosition(float2 position, float randomAmount = 0.0f, bool randomVel = false);
	void onRespawn();

private:

	Animation* mAnimation;

	std::vector<float2> mParticlesPos;
	std::vector<float2> mParticlesVel;
	int mFrameNum;
	int mLifeTimeTicks;
	int mBlinkTimeTicks;
	int mAnimationSpeed;
	int mNumParticles;
	int mMaxSpeed;
	int mMinSpeed;

	float2 mInitialVel;
	float mGravity;
};