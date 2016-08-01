#include <iostream>

#include "mine.hpp"
#include "level.hpp"
#include "resourcehandler.hpp"
#include "gamestate.hpp"

Mine::Mine(int x, int y, bool isMagnetic)
: Enemy(x, y, 16, 16, true),
  mToBeDeleted(false),
  mHitCount(30),
  mIsMagnetic(isMagnetic)
{
	mAnimation = new Animation(isMagnetic?"magneticmine.bmp":"mine.bmp");
	mRenderAsHit = false;
	mY = getY();
	mX = getX();
	mDy = 0;
	mDx = 0;
	mFrameCount = 0;

	mExplosionSample = ResourceHandler::getInstance()->getSample("explo2.wav");
	mBeepSample = ResourceHandler::getInstance()->getSample("beep.wav");
}

Mine::~Mine()
{
    delete mAnimation;
}

void Mine::logic(Level* level)
{
	if(mIsMagnetic) {
		int playerDiffX = level->getPlayer()->getCenterX() - getX();
		int playerDiffY = level->getPlayer()->getCenterY() - getY();

		if (playerDiffX * playerDiffX + playerDiffY * playerDiffY < 150 * 150)			
		{
			if ((mFrameCount % 10) == 0)
			{
				int pan = (getCenterX() * 256) / 240;

				if (pan < 0)
				{
					pan = 0;
				} 
				else if (pan > 255)
				{
					pan = 255;
				}

				play_sample(mBeepSample, 100, pan, 2000, 0);
			}

			mDx += playerDiffX / 1000.0f;
			mDy += playerDiffY / 1000.0f;
		}
	}

	float targetDy, dyDy, dxDx;

	if (!mIsMagnetic)
	{
		targetDy = 0.4;
		dyDy = targetDy - mDy;
		dxDx = -mDx;
	}
	else
	{
		targetDy = 0.0;
		dyDy = targetDy - mDy;
		dxDx = -mDx;
	}
	

	mY += mDy;
	mX += mDx;
	mFrameCount++;

	if (!mIsMagnetic)
	{
		mDy += dyDy/20.0f;
		mDx += dxDx/20.0f;
	}
	else
	{
		mDy += dyDy/30.0f;
		mDx += dxDx/30.0f;
	}

	setY((int)mY);
	setX((int)mX);

	if((getY() - level->getScrollY()) + getHeight() < 0)
	{
		mToBeDeleted = true;
	}
}

void Mine::handleCollision(Entity *other, Level *level)
{
	if(other->getType() == Entity::PLAYER_BULLET_TYPE)
	{
		int dx = getCenterX() - other->getCenterX();
		//int dy = getCenterY() - other->getCenterY();

		mHitCount -= other->getDamage();
		mRenderAsHit = true;
		mDy += 1.0;
		//std::cout << "dx: " << dx << std::endl;
		mDx += dx / 20.0f;
		//spawnDebris(level, 1, mX, mY, mW, mH);
		if(mHitCount <= 0)
		{
			mToBeDeleted = true;
			mCollidable = false; //do not collide while blinking
		}
	} 
    else if (other->getType() == Entity::PLAYER_TYPE)
    {
        level->getPlayer()->kill();

		mToBeDeleted = true;
		mCollidable = false;
    }
    else if(other->isCollidable())
	{
		mCollidable = false;
		mToBeDeleted = true;
	}
	if(!mCollidable)
	{
		level->spawnDebris(8, mX, mY, mW, mH);
        level->spawnExplosions(10, mX, mY, mW, mH);
		level->addShakeAmount(100);
		
		GameState::getInstance()->addPoints(100);
		level->addKilledEnemy(1);

		int pan = (getCenterX() * 256) / 240;
		if (pan < 0)
		{
			pan = 0;
		} 
		else if (pan > 255)
		{
			pan = 255;
		}

		play_sample(mExplosionSample, 150, pan, 750, 0);
	}

}

void Mine::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	mAnimation->drawFrame(dest, mRenderAsHit?2:(mFrameCount%10)<5?0:1, getX(), getY() - scrolly);
	mRenderAsHit = false;
}

bool Mine::isToBeDeleted()
{
    return mToBeDeleted && !mRenderAsHit;
}