#include "Precompiled.hpp"
#include "ParticleSystem.hpp"

#include "Animation.hpp"
#include "Room.hpp"
#include "Time.hpp"
#include "Util.hpp"

void ParticleSystem::update()
{
	mFrameNum ++;
	if (mLifeTimeTicks)
	{
		for (unsigned int i = 0; i < mParticlesVel.size(); i++)
		{
			mParticlesPos[i] += mParticlesVel[i] / Time::TicksPerSecond;
			mParticlesVel[i].y += mGravity;
		}

		mLifeTimeTicks--;
	}
	else
	{
		remove();
	}
}

ParticleSystem::ParticleSystem(
	Animation* aAnimation,
	int aAnimationSpeed,
	int aLifeTime,
	int aBlinkTime,
	int aMinSpeed,
	int aMaxSpeed,
	int aNumParticles,
	float2 aInitialVel,
	float aGravity
	)
: mLifeTimeTicks(aLifeTime)
, mBlinkTimeTicks(aBlinkTime)
, mAnimationSpeed(aAnimationSpeed)
, mFrameNum(0)
, mAnimation(aAnimation)
, mNumParticles(aNumParticles)
, mMaxSpeed(aMaxSpeed)
, mMinSpeed(aMinSpeed)
, mInitialVel(aInitialVel)
, mGravity(aGravity)
{
	setSize(float2(30, 30));
}

void ParticleSystem::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	if (mLifeTimeTicks < mBlinkTimeTicks && mLifeTimeTicks % 2 == 0)
		return;

	Random random(0);

	for (unsigned int i = 0; i < mParticlesPos.size(); i++)
	{
		mAnimation->drawFrame(buffer, mFrameNum/mAnimationSpeed + random.getInt(), mParticlesPos[i].x + offsetX - mAnimation->getFrameWidth()/2, mParticlesPos[i].y + offsetY - mAnimation->getFrameHeight()/2);
	}
}

void ParticleSystem::setPosition( float2 position, float randomAmount, bool randomVel )
{
	Entity::setPosition(position);

	Random random;

	for (int i = 0; i < mNumParticles; i++)
	{
		float2 pos = getPosition();
		pos += float2((frand() * 2.0f - 1.0f) * randomAmount, (frand() * 2.0f - 1.0f) * randomAmount);
		mParticlesPos.push_back(pos);
		
		float2 velocity = randomVel ? random.getFloat2(0.7f, 1.0f) :sincos(2* 3.1415 * random.getFloat(0.0f,1.0f));
		velocity *= random.getFloat(mMinSpeed, mMaxSpeed);

		velocity += mInitialVel;

		mParticlesVel.push_back(velocity);
	}
}

void ParticleSystem::onRespawn()
{
	remove();
}