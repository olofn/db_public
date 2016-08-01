#include "megablast.hpp"
#include "level.hpp"

#include <iostream>

MegaBlast::MegaBlast(int x, int y)
: Entity(x, y, 240, 340, true),
mFrameCounter(0)
{

}

void MegaBlast::logic(Level* level)
{
    mFrameCounter++;

    level->addShakeAmount(100);
}

void MegaBlast::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
    rectfill(dest, 0, 0, 240, 240, makecol(255, 255, 255));
}

bool MegaBlast::isToBeDeleted()
{
    return mFrameCounter > 10;
}