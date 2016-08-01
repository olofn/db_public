#include "SimpleWalkingMonster.hpp"

#include "Room.hpp"
#include "Hero.hpp"
#include "Sound.hpp"

#include "Resource.hpp"
#include "ParticleSystem.hpp"
#include "Animation.hpp"

#include "PlayerSkill.hpp"

const float WALKING_SPEED = 14.0f;
const float WALK_TO_IDLE_CHANCE = 0.01;
const float IDLE_TO_WALK_CHANCE = 0.05;

void SimpleWalkingMonster::update()
{
	switch(mState)
	{
	case State_Walking:
		{
			mVelocity.y += 6.0f;
			mVelocity.x = 20.0f * ((mFacing==Facing_Left)?-1:1);

			setVelocity(mVelocity);
			int bumps = moveWithCollision();

			if ((bumps & (Direction_Up | Direction_Down)) != 0) 
			{
				mVelocity.y = 0;
			}

			if ((bumps & (Direction_Left)) != 0)
			{
				mFacing = Facing_Right;
			}

			if ((bumps & (Direction_Right)) != 0)
			{
				mFacing = Facing_Left;
			}


			int offsetX = (mState==Facing_Right)?-getHalfSize().x-2:getHalfSize().x+2;
			int offsetY = getHalfSize().y+2;
		
			float2 position = getPosition();

			int x = (position.x+offsetX) / (float)mRoom->getTileWidth();
			int y = (position.y+offsetY) / (float)mRoom->getTileHeight();

			if (!mRoom->isCollidable(x, y))
			{
				if (mFacing == Facing_Left)
				{
					mFacing = Facing_Right;
				}
				else
				{
					mFacing = Facing_Left;
				}
			}

			if (mRand.getFloat(1.0f) < WALK_TO_IDLE_CHANCE)
			{
				mState = State_Idling;
			}
		}

		break;
	case State_Idling:

		if (mRand.getFloat(1.0f) < IDLE_TO_WALK_CHANCE)
		{
			if (mRand.getFloat(1.0f) > 0.5)
			{
				mFacing = Facing_Left;
			}
			else
			{
				mFacing = Facing_Right;
			}
			mState = State_Walking;
		}

		break;
	}

	Hero* hero = mRoom->getHero();
	if (Collides(hero->getCollisionRect(), getCollisionRect()))
	{
		hero->kill();
	}

	mFrame++;
}

SimpleWalkingMonster::SimpleWalkingMonster()
: mFacing(Facing_Left)
, mState(State_Idling)
, mFrame(0)
{
	mAnimation = Resource::getAnimation("data/images/robot.bmp", 4);	
	setSize(float2(20,20));
}

void SimpleWalkingMonster::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	float2 pos = getPosition();
	pos -= float2(mAnimation->getFrameWidth(), mAnimation->getFrameHeight())/2;
	pos += float2(offsetX, offsetY);

	mAnimation->drawFrame(buffer, mFrame/15, pos.x, pos.y, mFacing == Facing_Right);
}

bool SimpleWalkingMonster::isDamagable()
{
	return true;
}

void SimpleWalkingMonster::onDamage()
{
	PlayerSkill::playerDidSomethingClever(0.5f, 0.1f);
	die();
}

void SimpleWalkingMonster::die()
{
	Sound::playSample("data/sounds/damage.wav");

	ParticleSystem* ps = new ParticleSystem(Resource::getAnimation("data/images/debris.bmp", 4), 10, 30, 10, 1, 50, 5, -float2(0.0f, 30.0f), 2.0f);
	ps->setPosition(getPosition(), 5.0f);
	mRoom->addEntity(ps);
	remove();
}