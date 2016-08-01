#include "entities/movingspikes.hpp"

#include "level.hpp"

MovingSpikes::MovingSpikes(int x, int y, unsigned int orientation)
:Entity(x, y, 16, 32, true),
mAnimation("movingspikes.bmp"),
mLightAnimation("lightray.bmp")
{
    mFrameCounter = -1;
    mHostile = false;
    mFrame = 0;
    mState = DOWN;
    mOrientation = orientation;
}

void MovingSpikes::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    bool vflip;
    bool hflip;

    if (mOrientation == CEILING)
    {
        vflip = true;
        hflip = false;
    }
    else if (mOrientation == FLOOR)
    {
        vflip = false;
        hflip = false;
    }

    mAnimation.drawFrame(dest, mFrame, mX - scrollx, mY - scrolly, hflip, vflip);
    mLightAnimation.drawFrame(dest, 0, mX - scrollx, mY - scrolly, hflip, vflip, Animation::ADD);
}

void MovingSpikes::logic(Level *Level)
{
    mFrameCounter++;

    if (mState == DOWN)
    {
        if (mFrameCounter >= 203)
        {
            mFrame = 0;
            mFrameCounter = 0;
        }

        if (mFrameCounter == 100)
        {
            mState = MOVING_UP;
            mFrame = 1;
        }

        return;
    }

    if (mState == MOVING_UP)
    {
        if (mFrameCounter == 101)
        {
            mFrame = 2;
        }
        if (mFrameCounter == 102)
        {
            mState = UP;
            mFrame = 3;  
             mHostile = true;
        }

          return;
    }

    if (mState == UP)
    {
        if (mFrameCounter == 202)
        {
            mState = MOVING_DOWN;
            mFrame = 2;
        }

          return;
    }

    if (mState == MOVING_DOWN)
    {
        if (mFrameCounter == 203)
        {
            mFrame = 1;
        }

        if (mFrameCounter == 204)
        {
            mState = DOWN;
            mFrame = 0;
            mFrameCounter = -1;
            mHostile = false;
        }
    }
}

void MovingSpikes::handleCollision(Entity *other, Level* level)
{
    if (other == level->getPlayer() && mHostile)
        level->getPlayer()->kill();
}
