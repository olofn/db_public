#include "entities/breakingtile.hpp"

#include "level.hpp"
#include "tile.hpp"
#include <iostream>

BreakingTile::BreakingTile(int x, int y)
:Entity(x, y - 1, 16, 16, true),
mAnimation("breakingtile.bmp")
{
    mHealth = 3; 
    mInitialised = false;
    mHibernating = false;
    mBreakDownStarted = false;
    mFrameCounter = 0;
}

void BreakingTile::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    if (!mHibernating)
     mAnimation.drawFrame(dest, mHealth, getX() - scrollx, getY() + 1 - scrolly);
}

void BreakingTile::logic(Level *level)
{
    mFrameCounter++;

    if (!mInitialised)
    {
        level->getTileMap()->replaceTile(new Tile(getX(), getY() + 1, "", true));
        mInitialised = true;
    }

    if (mBreakDownStarted && mFrameCounter % 4 == 0)
    {
        mHealth--;
    }

    if (mHealth < 0 && !mHibernating)
    {
        level->getTileMap()->replaceTile(new Tile(getX(), getY() + 1, "", false));
        mHibernating = true;
        mFrameCounter = 0;
    }

    if (mHibernating && mFrameCounter > 400)
    {
        mHibernating = false;
        mFrameCounter = 0;
        mHealth = 3;
        mBreakDownStarted = false;
        mInitialised = false;
    }
}

void BreakingTile::handleCollision(Entity *other, Level* level)
{
    if (other == level->getPlayer())
    {
        mBreakDownStarted = true;
    }
}
