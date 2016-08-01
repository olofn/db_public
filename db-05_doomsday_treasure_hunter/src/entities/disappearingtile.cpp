#include "entities/disappearingtile.hpp"

#include "level.hpp"
#include "tile.hpp"
#include <iostream>

DisappearingTile::DisappearingTile(int x, int y, int timeOffset)
:Entity(x, y, 16, 16, false),
mAnimation("disappearingtile.bmp")
{
    mInitialised = false;
    mVisible = true;
    mFrameCounter = 0;
    mTimeOffset = timeOffset;
}

void DisappearingTile::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    if (mVisible)
        mAnimation.drawFrame(dest, mFrameCounter / 5, getX() - scrollx, getY() - scrolly);
}

void DisappearingTile::logic(Level *level)
{
    mFrameCounter++;

    if (!mInitialised && mVisible)
    {
        level->getTileMap()->replaceTile(new Tile(getX(), getY(), "", true));
        mInitialised = true;
    }

    if (mFrameCounter > (150 + mTimeOffset) && mVisible && mInitialised)
    {
        mVisible = false;
        mInitialised = false;
        level->getTileMap()->replaceTile(new Tile(getX(), getY(), "", false));
        mFrameCounter = mTimeOffset;
    }

    if (mFrameCounter >  (150 + mTimeOffset) && !mVisible && !mInitialised)
    {
        mVisible = true;
        mFrameCounter = mTimeOffset;
    }
}

