#include <iostream>
#include <cmath>

#include "turret.hpp"
#include "enemybullet.hpp"
#include "playerbullet.hpp"
#include "level.hpp"
#include "gamestate.hpp"
#include "util.hpp"

Turret::Turret(int x, int y, FireDirection direction, int shots)
: Enemy(x, y, 16, 16, true),
  mIsToBeDeleted(false),
  mDirection(direction),
  mFrameCount(0),
  mHitCount(15),
  mShots(shots)
{
    mAnimation = new Animation("turret.bmp");
	mKillsPlayer = true;
}

Turret::~Turret()
{
    delete mAnimation;
}

void Turret::logic(Level* level)
{
	mFrameCount++;
	if(mFrameCount%60 == 0)
	{
		float speed = 1.5;
		float shootingArc = (M_PI*(1/4.0f));
		float leftArc = M_PI - shootingArc;
		float angle = M_PI/2.0f;
		
		if(mShots <= 1) {
				if(mDirection == LEFT) angle += M_PI;
				if(mDirection == DOWN) angle -= M_PI/2.0f;
				if(mDirection == UP) angle += M_PI/2.0f;
				float xSpeed=std::sin(angle)*speed, ySpeed=std::cos(angle)*speed;

				level->addEntity(new EnemyBullet(getCenterX(), getCenterY(), xSpeed, ySpeed, 1, angle));

		} else {
			for(int i=0; i<mShots; i++)
			{
				angle = shootingArc*(i/((float)(mShots-1)));
				angle += leftArc/2.0f;
				if(mDirection == LEFT) angle += M_PI;
				if(mDirection == DOWN) angle -= M_PI/2.0f;
				if(mDirection == UP) angle += M_PI/2.0f;
				float xSpeed=std::sin(angle)*speed, ySpeed=std::cos(angle)*speed;

				level->addEntity(new EnemyBullet(getCenterX(), getCenterY(), xSpeed, ySpeed, 1, angle));
			}
		}

	}

	if (getY() + getHeight() + 64 < level->getScrollY())
	{
		mIsToBeDeleted = true;
	}
}

void Turret::handleCollision(Entity *other, Level *level)
{
	if(other->getType() == Entity::PLAYER_BULLET_TYPE)
	{
		int dx = getCenterX() - other->getCenterX();

		mHitCount -= other->getDamage();
		mRenderAsHit = true;

		if(mHitCount <= 0)
		{
			mIsToBeDeleted = true;
			mCollidable = false; //do not collide while blinking

			level->spawnDebris(8, mX, mY, mW, mH);
		    level->spawnExplosions(10, mX, mY, mW, mH);
			level->addShakeAmount(100);
			GameState::getInstance()->addPoints(150);
			level->addKilledEnemy(1);
		}
	}


}

void Turret::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	int frame = mRenderAsHit?2:(mFrameCount%20)<10?0:1;

	if(mDirection==UP||mDirection==DOWN) {
		mAnimation->drawRotatedFrame(dest, frame, getX(), getY() - scrolly, mDirection==UP?-64:64, false);
	}
	else
	{
		mAnimation->drawFrame(dest, frame, getX(), getY() - scrolly, mDirection==LEFT?true:false, false);
	}
	mRenderAsHit = false;
}

bool Turret::isToBeDeleted()
{
    return mIsToBeDeleted && !mRenderAsHit;
}