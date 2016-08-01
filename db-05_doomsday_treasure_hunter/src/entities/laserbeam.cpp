#include "entities/laserbeam.hpp"
#include "level.hpp"
#include "blending.hpp"
#include "level.hpp"
#include "resourcehandler.hpp"

LaserBeam::LaserBeam(int x, int y, bool horizontal) 
    : Entity(x + 8, y, 1, 16, true),
	  mFrameCounter(1),
      mLightRayAnimation("lightray2.bmp")
{
     mExplosionSample = ResourceHandler::getInstance()->getSample("explo1.wav");
     mKillPlayer = false;

     if (horizontal)
     {
        setPosition(x, y + 8);
        setWidth(16);
        setHeight(1);
     }
}

LaserBeam::~LaserBeam()
{
}

void LaserBeam::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    setAddBlender();
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    rectfill(dest, 
             mX - scrollx, 
             mY - scrolly, 
             mX - scrollx + mW - 1, 
             mY - scrolly + mH - 1, 
             makecol(70, 0, 0));
    drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
 
   // mLightRayAnimation.drawFrame(dest, 0, mX - 8 - scrollx, mY - scrolly, false, false, Animation::ADD);
}

void LaserBeam::logic(Level *level)
{
	mFrameCounter++;

    if (mKillPlayer && mFrameCounter > 10)
        level->getPlayer()->kill();
}

void LaserBeam::handleCollision(Entity *other, Level* level)
{
    if (other == level->getPlayer())
    {
      
        if (!level->getPlayer()->isLaserShielded() && !mKillPlayer)
        {
            mFrameCounter = 0;
            mKillPlayer = true;
            level->spawnExplosions(10, getX(), getY(), 16, 16);
            play_sample(mExplosionSample, 150, 128, 750, 0);
        }
    }
}
