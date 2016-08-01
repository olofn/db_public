#include "entities/rat.hpp" 
#include "room.hpp"

namespace nmc
{
    Rat::Rat(int x, int y)
        :Enemy(x, y + 6, 26, 10, 1),
        mRunningAnimation("rat-running.bmp"),
        mSniffingAnimation("rat-sniffing.bmp"),
        mHurtAnimation("rat-hurt.bmp"),
        mHealth(2),
        mFrameCounter(0)
    {
        changeState();
    }
        
    void Rat::damage(Shot *s, int amount)
    {
        mHealth -= amount;
        mState = HURT;
        mFrameCounter = 0;
        mStateTimer = 10;
    }

    void Rat::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
    {
        if (mState == RUNNING)
        {
            if (mDirection == LEFT)
            {
                mRunningAnimation.drawFrame(dest, 
                                            mFrameCounter / 5, 
                                            mX - scrollx - 3, 
                                            mY - scrolly - 38, 
                                            true,
										    false,
										    isFrozen() ? Animation::FROZEN : Animation::NONE); 
            }
            else
            {
                mRunningAnimation.drawFrame(dest, 
                                            mFrameCounter / 5, 
                                            mX - scrollx - 19, 
                                            mY - scrolly - 38,
											false,
										    false,
										    isFrozen() ? Animation::FROZEN : Animation::NONE);
            }
        }
        else if (mState == SNIFFING)
        {
            if (mDirection == LEFT)
            {  
                mSniffingAnimation.drawFrame(dest, 
                                             mFrameCounter / 20, 
                                             mX - scrollx - 3, 
                                             mY - scrolly - 38, 
                                             true,
											 false,
											 isFrozen() ? Animation::FROZEN : Animation::NONE);
            }
            else
            {
                mSniffingAnimation.drawFrame(dest, 
                                             mFrameCounter / 20, 
                                             mX - scrollx - 19, 
                                             mY - scrolly - 38,
											 false,
											 false,
											 isFrozen() ? Animation::FROZEN : Animation::NONE); 
            }

        }
        else if (mState == HURT || mState == DYING)
        {
            if (mFrameCounter % 4 == 0)
            {
                return;
            }

            if (mDirection == LEFT)
            {  
                mHurtAnimation.drawFrame(dest, 
                                         mFrameCounter / 20, 
                                         mX - scrollx - 3, 
                                         mY - scrolly - 38, 
                                         true,
										 false,
										 isFrozen() ? Animation::FROZEN : Animation::NONE); 
            }
            else
            {
                mHurtAnimation.drawFrame(dest, 
                                         mFrameCounter / 20, 
                                         mX - scrollx - 19, 
                                         mY - scrolly - 38,
										 false,
										 false,
										 isFrozen() ? Animation::FROZEN : Animation::NONE); 
            }
        }
        
       // rect(dest, mX -scrollx, mY - scrolly, mX -scrollx + mW - 1, mY - scrolly + mH - 1, makecol(255,100,155));
    }

    void Rat::enemyLogic(Room *room)
    {
        if (mState == DEAD)
        {
            return;
        }

        mFrameCounter++;

        if (mHealth < 0 && mState != DYING)
        {
            mState = DYING;
            mFrameCounter = 0;
            mStateTimer = 25;
            mCollidable = false;
            return;
        }
        else if (mState == RUNNING && mDirection == LEFT)
        {
            mX-=3;

            int solidLeftOffset;
            if (solidLeft(room, solidLeftOffset) 
                || (mX < -100)
                || !(room->getTileMap()->isSolid((mX - 1) / 16, (mY + mH) / 16)
                    || room->getTileMap()->isPlatform((mX - 1) / 16, (mY + mH) / 16)))
            {
                mDirection = RIGHT;
            }
        }
        else if (mState == RUNNING && mDirection == RIGHT)
        {
            mX+=3;

            int solidRightOffset;
            if (solidRight(room, solidRightOffset)
                || (mX + mW - 100 > room->getTileMap()->getWidth() * 16)
                || !(room->getTileMap()->isSolid((mX + mW) / 16, (mY + mH) / 16)
                    || room->getTileMap()->isPlatform((mX + mW) / 16, (mY + mH) / 16)))
            {
                mDirection = LEFT;
            }
        }

        if (mFrameCounter > mStateTimer && mState == DYING)
        {
            mState = DEAD;  
        }
        else if (mFrameCounter > mStateTimer)
        {
            changeState();
        }
    }

    bool Rat::isToBeDeleted()
    {
        return mState == DEAD;
    }

    void Rat::changeState()
    {
        mState = rand() % 2;
        mDirection = rand() % 2;
        mFrameCounter = 0;

        if (mState == SNIFFING)
        {
            mStateTimer = 100 + rand() % 100;
        }
        else
        {
            mStateTimer = 30 + rand() % 75;
        }
    }
}