#include <iostream>
#include <cmath>

#include "floater.hpp"
#include "level.hpp"
#include "resourcehandler.hpp"
#include "util.hpp"
#include "gamestate.hpp"

Floater::Floater(int x, int y, int hitCount)
: Enemy(x, y, 16, 16, true),
  mToBeDeleted(false),
  mHitCount(150)
{
	mAnimation = new Animation("floater.bmp", 4);
	mRenderAsHit = false;
	mY = getY();
	mX = getX();
	mDy = 0;
	mDx = 0;
	mFrameCount = 0;
	mKillsPlayer = false;

	mExplosionSample = ResourceHandler::getInstance()->getSample("explo2.wav");
}

Floater::~Floater()
{
    delete mAnimation;
}

void Floater::logic(Level* level)
{
	static float f = 0;
	f += 0.1;
	if(mFrameCount % 60 == 0)
	{
		float arc = M_PI*0.5f;
		float leftArc = M_PI - arc;

		mRadius = 60+60*frand();
		mAngle = -(arc/2.0f)+(arc * frand()); 
	}

	int playerX = level->getPlayer()->getX();
	int playerY = level->getPlayer()->getY();

	//float angle = (float)std::atan2((float)(playerX - getX()), (float)(playerY - getY()));

	int targetX = playerX + std::sin(mAngle)*mRadius;
	int targetY = playerY + std::cos(mAngle)*mRadius;

	mTargetX = targetX; mTargetY = targetY;
	int playerDiffX = targetX - (getX());
	int playerDiffY = targetY - (getY());
		
	mDx = playerDiffX/4.0f;
	mDy = playerDiffY/4.0f;
	

	mY += mDy;
	mX += mDx;
	mFrameCount++;

	setY((int)mY);
	setX((int)mX);

	if((getY() - level->getScrollY()) + getHeight() < -30)
	{
		mToBeDeleted = true;
	}
}

void Floater::handleCollision(Entity *other, Level *level)
{
	
	if(other->getType() == Entity::PLAYER_BULLET_TYPE)
	{
		mHitCount -= other->getDamage();
		mRenderAsHit = true;
		if(mHitCount <= 0)
		{
			mToBeDeleted = true;
			mCollidable = false; //do not collide while blinking
		}
	} 
	if(!mCollidable)
	{
		level->spawnDebris(8, mX, mY, mW, mH);
        level->spawnExplosions(10, mX, mY, mW, mH);
		level->addShakeAmount(100);
		GameState::getInstance()->addPoints(120);
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

void Floater::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	int frame = (mFrameCount / 10) % 2;
	
	if (mRenderAsHit)
	{
		frame += 2;
	}

	mAnimation->drawFrame(dest, frame, getX() - 2, getY() - scrolly - 2);	
	mRenderAsHit = false;
	
	//circlefill(dest, mTargetX, mTargetY-scrolly, 2, makecol(200, 200, 200));
}

bool Floater::isToBeDeleted()
{
    return mToBeDeleted && !mRenderAsHit;
}