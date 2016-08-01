#include "spider.hpp"
#include "room.hpp"

namespace nmc
{
	Spider::Spider(int x, int y) :
		Enemy(x, y, 28, 28, 1),
        mAnimation("spider.bmp"),
        mFrameCounter(0),
		mDY(1),
		mStartY(y),
		mHealth(2),
		mHurtTimer(0)
	{
		mStateCounter = rand() % 20 + 15;
	}

    void Spider::damage(Shot *s, int amount)
	{
		mHealth -= amount;
		mStateCounter = mHurtTimer = 10;
		mDY = 0;
		if (mHealth <= 0)
		{
			mStateCounter = mHurtTimer = 25;
			mCollidable = false;
			mDY = 2;
		}
	}

    void Spider::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
	{
		int l = mY + mH / 2 - mStartY;

		if (mHealth <= 0)
		{
			l = (l * mHurtTimer) / 25;
		}

		line(dest,
			 mX + mW / 2 - scrollx,
			 mY + mH / 2 - l - scrolly,
			 mX + mW / 2 - scrollx,
			 mY + mH / 2 - scrolly,
			 makecol(140, 140, 120));

		Animation::Blending blend = (mHurtTimer % 4 > 2) ? Animation::LIGHTEN : getBlendMode();
		mAnimation.drawFrame(dest, mY / 6, mX - scrollx - 2, mY - scrolly - 2, false, false, blend);
	}

    void Spider::enemyLogic(Room *room)
	{
		mFrameCounter++;
		mStateCounter--;

		if (mHurtTimer > 0)
		{
			mHurtTimer--;
			mY += mDY;
			return;
		}

		int dummy;

		if (solidBelow(room, dummy))
		{
			mDY = (rand() % 2) - 1;
			mStateCounter = rand() % 20 + 15;
		}

		if (mY <= mStartY)
		{
			mDY = (rand() % 2);
			mStateCounter = rand() % 20 + 15;
		}

		if (mStateCounter <= 0)
		{
			if (rand() % 2)
			{
				// Move towards player
				if (getCenterY() < room->getPlayer()->getCenterY())
				{
					mDY = 1;
				}
				else
				{
					mDY = -1;
				}
			}
			else
			{
				// Move randomly
				mDY = (rand() % 3) - 1;
			}
			mStateCounter = rand() % 20 + 15;
		}

		mY += mDY;
	}

    bool Spider::isToBeDeleted()
	{
		return mHealth <= 0 && mHurtTimer == 0;
	}
}