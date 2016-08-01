#include <cmath>
#include <vector>
#include "item.hpp"
#include "itementity.hpp"
#include "room.hpp"
#include "tilemap.hpp"
#include "random.hpp"
#include "util.hpp"
#include "resourcehandler.hpp"

#include <allegro.h>

ItemEntity::ItemEntity(Animation* animation, int x, int y, bool bounceAway, int coins, int hearts)
:Entity(Entity::OTHER, x, y, animation->getFrameWidth(), animation->getFrameHeight(), true),
mAnimation(animation), 
mCoins(coins),
mHearts(hearts),
mSampleCoin(ResourceHandler::getInstance()->getSample("sound/coin.wav")),
mSampleHeart(ResourceHandler::getInstance()->getSample("sound/heart.wav"))
{
	mIsToBeDeleted = false;
	mXasFloat = getX();
	mYasFloat = getY();
	mSpeed = 0;
	mTimeLeftToLive = 400;
	if(bounceAway)
	{
		Random random;
		mSpeed = 1 + random.getUFloat();
		mDirection = M_PI*2*random.getUFloat();
		
		mBounceOffset = 0;
		mBounceSpeed = mSpeed;
	}
}

int ItemEntity::getCoins()
{
	return mCoins;
}

ItemEntity::~ItemEntity()
{
	delete(mAnimation);
}

bool ItemEntity::isToBeDeleted()
{
	return mIsToBeDeleted;
}

void ItemEntity::logic()
{
	if(mTimeLeftToLive < 380)
	{
		std::vector<Entity*> collisions = mRoom->collidesWith(this, Entity::PLAYER, 0);
		if (collisions.size() > 0)
		{
			Player* player = mRoom->getPlayer();
			
			mIsToBeDeleted = true;
			
			if(mCoins > 0)
			{
				player->addCoins(mCoins);
				play_sample(mSampleCoin, 127, 127, 1000, 0);
			}
			if(mHearts > 0)
			{
				player->setHealth(player->getHealth() + mHearts);
				play_sample(mSampleHeart, 127, 127, 1000, 0);
			}
		}
	}

	mTimeLeftToLive--;

	if(mTimeLeftToLive == 0)
	{
		mIsToBeDeleted = true;
	}

	if(mSpeed > 0.1)
	{
		float speedX = sin(mDirection) * mSpeed;
		float speedY = cos(mDirection) * mSpeed;

		mXasFloat += speedX;
		mYasFloat += speedY;
		mSpeed /= 1.06;

	}
	setX(mXasFloat);
	setY(mYasFloat);
	mBounceOffset += mBounceSpeed;
	mBounceSpeed -= 0.15;
	if(mBounceOffset <= 0)
	{
		mBounceOffset = 0;
		mBounceSpeed = -mBounceSpeed*0.6;
		if(abs(mBounceSpeed) <= 0.70) mBounceSpeed = 0;
	}


}

void ItemEntity::draw(BITMAP *dest, int scrollx, int scrolly)
{
	if(mTimeLeftToLive > 60 || mTimeLeftToLive % 6 < 3)
	{
		ellipsefill(dest, mX - scrollx + getWidth()/2, mY - scrolly + getHeight()*0.9, getWidth()*0.4, getHeight()*0.2, 0);
		mAnimation->drawFrame(dest, 0, mX - scrollx, mY - scrolly - mBounceOffset);
	}
}
