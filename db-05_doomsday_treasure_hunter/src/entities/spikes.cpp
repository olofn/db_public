#include "entities/spikes.hpp"

#include "level.hpp"

Spikes::Spikes(int x, int y)
:Entity(x, y, 16, 16, true),
mAnimation("spikes.bmp"),
mLightRayAnimation("lightray.bmp")
{

}
void Spikes::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    mAnimation.drawFrame(dest, 0, getX() - scrollx, getY() - scrolly);
    mLightRayAnimation.drawFrame(dest, 0, getX() - scrollx, getY() - scrolly, false, false, Animation::ADD);
}

void Spikes::logic(Level *level)
{

}

void Spikes::handleCollision(Entity *other, Level* level)
{
    if (other == level->getPlayer())
    {
        level->getPlayer()->kill();
    }
}
