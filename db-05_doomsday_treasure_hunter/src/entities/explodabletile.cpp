#include "entities/explodabletile.hpp"

#include "level.hpp"
#include "tile.hpp"
#include "bomb.hpp"
#include <iostream>

ExplodableTile::ExplodableTile(int x, int y)
:Entity(x, y, 16, 16, false),
mAnimation("explodabletile.bmp")
{
    mHealth = 5; 
    mInitialised = false;
    mToBeDeleted = false;
}

void ExplodableTile::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    mAnimation.drawFrame(dest, mHealth, getX() - scrollx, getY() - scrolly);
}

void ExplodableTile::logic(Level *level)
{
    if (!mInitialised)
    {
        level->getTileMap()->replaceTile(new Tile(getX(), getY(), "", true));
        mInitialised = true;
    }

    if (mHealth < 0 && !mToBeDeleted)
    {
        level->getTileMap()->replaceTile(new Tile(getX(), getY(), "", false));
        mToBeDeleted = true;
    }
}

bool ExplodableTile::isToBeDeleted()
{
    return mToBeDeleted;
}

void ExplodableTile::message(const std::string& message, Entity* distributor)
{
    if (message == "bombexplosion")
    {
        Bomb* bomb = (Bomb*)distributor;
        float impact = bomb->getExplosionImpact(this);
        if (impact > 1.0f)
            mHealth -= impact;
    }
}
