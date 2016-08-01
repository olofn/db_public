#include "entities/rollingspikes.hpp"

#include "level.hpp"
#include "util.hpp"
#include "blending.hpp"
#include <iostream>

RollingSpikes::RollingSpikes(int x, int y)
:Entity(x, y, 16, 16, true),
mAnimation("rollingspikes.bmp")
{
    mState = LEFT;
}

void RollingSpikes::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    mAnimation.drawFrame(dest, mFrameCounter / 5, getX() - scrollx, getY() -scrolly); 
}

void RollingSpikes::logic(Level *level)
{
    if (mState == LEFT)
    {
        mX--;
        mFrameCounter--;
    }
    else if (mState == RIGHT)
    {
        mX++;
        mFrameCounter++;
    }
    if (mState == LEFT && level->getTileMap()->isLeftSolid(this))
    {
        level->getTileMap()->alignToLeftTile(this);
        mState = RIGHT;
    }

    if (mState == LEFT && !level->getTileMap()->isPeekLeftBelowSolid(this))
    {
        mState = RIGHT;
    }

    if (mState == RIGHT && level->getTileMap()->isRightSolid(this))
    {
        level->getTileMap()->alignToRightTile(this);
        mState = LEFT;
    }

    if (mState == RIGHT && !level->getTileMap()->isPeekRightBelowSolid(this))
    {
        mState = LEFT;
    }
}

void RollingSpikes::handleCollision(Entity *other, Level* level)
{
    if (other == level->getPlayer())
    {
        level->getPlayer()->kill();
    }
}
