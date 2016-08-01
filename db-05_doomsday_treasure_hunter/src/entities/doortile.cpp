#include "entities/doortile.hpp"

#include "level.hpp"
#include "tile.hpp"
#include <iostream>

DoorTile::DoorTile(int x, int y, bool open)
:Entity(x, y, 16, 16, false),
mAnimation("doortile.bmp"),
mOpen(open)
{
    mInitialised = false;
}

void DoorTile::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    if (mOpen)
        mAnimation.drawFrame(dest, 1, getX() - scrollx, getY() - scrolly);
    else
        mAnimation.drawFrame(dest, 0, getX() - scrollx, getY() - scrolly);
}

void DoorTile::logic(Level *level)
{
    if (!mInitialised && !mOpen)
    {
        level->getTileMap()->replaceTile(new Tile(getX(), getY(), "", true));
        mInitialised = true;
    }

    if (!mInitialised && mOpen)
    {
        level->getTileMap()->replaceTile(new Tile(getX(), getY(), "", false));
        mInitialised = true;
    }
}

void DoorTile::message(const std::string& message, Entity* distributor)
{
    if (message == "buttonpushed")
    {
        mOpen = !mOpen;
        mInitialised = false;
    }
}
