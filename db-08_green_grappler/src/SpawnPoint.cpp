#include "SpawnPoint.hpp"

#include "Room.hpp"
#include "Hero.hpp"

#include "Animation.hpp"
#include "Resource.hpp"
#include "PlayerSkill.hpp"

void SpawnPoint::update()
{
 	Hero* hero = mRoom->getHero();
	
	if (Collides(hero->getCollisionRect(), getCollisionRect()))
	{
		if (mState == State_Unchecked) {
			PlayerSkill::playerDidSomethingClever(0.7f, 0.5f);
		}

		mState = State_SemiChecked;
		hero->setLastSpawnPoint(this->getPosition());
	}

	if (mState == State_SemiChecked)
	{
		mFrame++;
	}

	if (mFrame > 5)
	{
		mState = State_Checked;
	}
}

SpawnPoint::SpawnPoint()
: mState(State_Unchecked)
, mFrame(0)
{
	mAnimation = Resource::getAnimation("data/images/checkpoint.bmp", 3);
	setSize(float2(22,25));
}

void SpawnPoint::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	float2 pos = getPosition();
	pos -= float2(mAnimation->getFrameWidth(), mAnimation->getFrameHeight())/2;
	pos += float2(offsetX, offsetY);

	mAnimation->drawFrame(buffer, mState, pos.x, pos.y);
//	Entity::draw(buffer, offsetX, offsetY, layer);
}