#include <cmath>
#include <iostream>

#include "entities/eyeball.hpp"
#include "room.hpp"

namespace nmc
{
	EyeBall::EyeBall(int x, int y) :
		Enemy(x, y, 26, 26, 2),
		mSprite("eyeball.bmp"), mFacingRight(false),
		mDX(0), mDY(0), mFX(x), mFY(y),
		mPursuing(false), mHealth(2)
	{
		mFrame = rand();
	}
		
	void EyeBall::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
    {
		if (mHealth > 0 || mFrame % 2 || mFrame < 5) 
        {
			mSprite.drawFrame(dest, 0, mX - scrollx - 2, mY - scrolly - 2, mFacingRight, false, isFrozen() ? Animation::FROZEN : Animation::NONE);
		}

        //rect(dest, mX -scrollx, mY - scrolly, mX - scrollx + mW - 1, mY - scrolly + mH - 1, makecol(255,100,155));
	}

	void EyeBall::enemyLogic(Room *room) {
		mFrame++;

		Player *player = room->getPlayer();
		
		float targetX = player->getCenterX() - mFX - mW / 2;
		float targetY = player->getCenterY() - mFY - mH / 2;
		float len = std::sqrt(targetX * targetX + targetY * targetY);
		mFacingRight = targetX > 0;
		
		if (len < 180.0f) {
			mPursuing = true;
		}

		if (mPursuing && len > 0.0f) {
			targetX = targetX / len;
			targetY = targetY / len;
		} else {
			targetX = targetY = 0;
		}

		if (mHealth > 0) {
			mDX += (targetX + sin(mFrame / 12.7)) / 6;
			mDY += (targetY + sin(mFrame / 10.0)) / 6;

			len = std::sqrt(mDX * mDX + mDY * mDY);

			if (len > 2.5f) {
				mDX = 2.5f * mDX / len;
				mDY = 2.5f * mDY / len;
			}
		} else {
			mDY += 0.2;
		}
		
		mFX += mDX;
		mFY += mDY;

		mX = (int)mFX;
		mY = (int)mFY;
	}

	bool EyeBall::isToBeDeleted() {
		return mHealth <= 0 && mFrame > 15;
	}

	void EyeBall::damage(Shot *s, int amount) {
		mHealth -= amount;
		mFrame = 0;

		if (s->getDX() > 0) {
			mDX = 5;
		}
		if (s->getDX() < 0) {
			mDX = -5;
		}
		if (s->getDY() > 0) {
			mDY = 5;
		}
		if (s->getDY() < 0) {
			mDY = -5;
		}
	}

}