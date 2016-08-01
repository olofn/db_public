#include "entities/ceilingdrop.hpp"
#include "room.hpp"

namespace nmc 
{
    CeilingDrop::CeilingDrop(int x, int y)
        : Entity(x, y, 1, 1),
        mFrameCounter(0),
        mStateTime(rand() % 500),
        mState(NONE),
        mOriginalX(x),
        mOriginalY(y),
		mDY(0)
    {
    }

    void CeilingDrop::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
    {
		int color = makecol(150, 150, 200);
        if (mState != NONE)
        {
            putpixel(dest, mX - scrollx, mY - scrolly, color);
        }

		 if (mState == FALLING)
        {
            putpixel(dest, mX - scrollx, mY - scrolly - 1, color);
        }

        if (mState == HIT && mFrameCounter <= 3)
        {
            putpixel(dest, mX - scrollx, mY - scrolly, color);
            putpixel(dest, mX - scrollx - 2, mY - scrolly, color);
            putpixel(dest, mX - scrollx + 2, mY - scrolly, color);
        }
        else if (mState == HIT)
        {
            putpixel(dest, mX - scrollx, mY - scrolly - 3, color);
            putpixel(dest, mX - scrollx - 4, mY - scrolly - 3, color);
            putpixel(dest, mX - scrollx + 4, mY - scrolly - 3, color);
        }
    }

    void CeilingDrop::logic(Room *room)
    {
        mFrameCounter++;

        if (mState == FALLING)
        {
			mDY++;
			if (mDY / 5 < 15)
			{
				mY += mDY / 5;
			}
			else
			{
				mY += 15;
			}			
        }

        if (room->getTileMap()->isSolid(mX / 16, mY / 16) 
            && mState != HIT 
            && mState != NONE)
        {
            mState = HIT;
            mStateTime = 6;
            mFrameCounter = 0;
            mY = mY - mY % 16;
            return;
        }

        if (room->getPlayer()->getX() <= mX 
            && room->getPlayer()->getX() + room->getPlayer()->getWidth() > mX
            && room->getPlayer()->getY() <= mY
            && room->getPlayer()->getY() + room->getPlayer()->getHeight() > mY
            && mState != HIT 
            && mState != NONE)
        {
            mState = HIT;
            mStateTime = 6;
            mFrameCounter = 0;
            mY = room->getPlayer()->getY();
            return;
        }

       if (mState == HIT && mStateTime <= mFrameCounter)
       {
            mState = NONE;
            mStateTime = 20 + rand() % 500;
            mFrameCounter = 0;
            return;
       }

       if (mState == CEILING && mStateTime <= mFrameCounter)
       {
            mState = FALLING;
            return;
       }

       if (mState == NONE && mStateTime <= mFrameCounter)
       {
            mState = CEILING;
            mY = mOriginalY;
            mX = mOriginalX;
			mDY = 0;
            mStateTime = 20 + rand() % 20;
            mFrameCounter = 0;
            return;
       }
    }
}