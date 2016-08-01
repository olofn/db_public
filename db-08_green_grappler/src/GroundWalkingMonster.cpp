#include "GroundWalkingMonster.hpp"

#include "Room.hpp"
#include "Hero.hpp"
#include "Sound.hpp"

#include "Resource.hpp"
#include "Animation.hpp"
#include "PlayerSkill.hpp"

const float MIN_WALKING_SPEED = 40.0f;
const float MAX_WALKING_SPEED = 70.0f;

void GroundWalkingMonster::update()
{
	Hero* hero = mRoom->getHero();

	float2 vel;

	float adjustedSpeed = lerp(MIN_WALKING_SPEED, MAX_WALKING_SPEED, PlayerSkill::get());

	if (mType == Type_Floor||mType == Type_Roof)
	{
		if (mDirection == Facing_LeftUp)
			vel = float2(-adjustedSpeed, 0);
		else
			vel = float2(adjustedSpeed, 0);
	}
	else
	{
		if (mDirection == Facing_LeftUp)
			vel = float2(0, -adjustedSpeed);
		else
			vel = float2(0, adjustedSpeed);
	}

	setVelocity(vel);

	int bumps = moveWithCollision();

	if ((bumps & (Direction_Left) | bumps & (Direction_Up)) != 0) {
		mDirection = Facing_RightDown;
	}

	if ((bumps & (Direction_Right) | bumps & (Direction_Down)) != 0) {
		mDirection = Facing_LeftUp;
	}

	int offsetX;
	int offsetY;

	if (mType == Type_Floor || mType == Type_Roof)
	{
		offsetX = (mDirection==Facing_LeftUp)?-getHalfSize().x-2:getHalfSize().x+2;
		offsetY = (mType==Type_Floor)?getHalfSize().y+2:-getHalfSize().y-2;
	}
	else
	{
		offsetX = (mType==Type_LeftWall)?-getHalfSize().x-2:getHalfSize().x+2;
		offsetY = (mDirection==Facing_RightDown)?getHalfSize().y+2:-getHalfSize().y-2;
	}

	float2 position = getPosition();

	int x = (position.x+offsetX) / (float)mRoom->getTileWidth();
	int y = (position.y+offsetY) / (float)mRoom->getTileHeight();

	if (!mRoom->isCollidable(x, y))
	{
		if (mDirection == Facing_LeftUp)
		{
			mDirection = Facing_RightDown;
		}
		else
		{
			mDirection = Facing_LeftUp;
		}
	}

	if (Collides(hero->getCollisionRect(), getCollisionRect()))
	{
		hero->kill();
	}

	if (hero->hasHook() && Collides(hero->getHookCollisionRect(), getCollisionRect()))
	{
		Sound::playSample("data/sounds/hook.wav");
		hero->detachHook();
	}

	mFrame++;
}

GroundWalkingMonster::GroundWalkingMonster(
	Type aType)
: mDirection(Facing_RightDown)
, mType(aType)
, mFrame(0)
{
	setSize(float2(10,10));

	mAnimation = Resource::getAnimation("data/images/saw.bmp", 2);
}

void GroundWalkingMonster::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	float2 pos = getPosition();
	pos -= float2(mAnimation->getFrameWidth(), mAnimation->getFrameHeight())/2;
	pos += float2(offsetX, offsetY);

	mAnimation->drawFrame(buffer, mFrame/3, pos.x, pos.y);
}
