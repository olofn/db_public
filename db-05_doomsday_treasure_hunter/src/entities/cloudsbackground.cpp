#include "entities/cloudsbackground.hpp"
#include "resourcehandler.hpp"
#include "level.hpp"

CloudsBackground::CloudsBackground()
    :Entity(false),
     mRoomWidth(240),
     mRoomHeight(240),
    mWind(0)
{
    mCloudsBitmap1 = ResourceHandler::getInstance()->getBitmap("clouds1.bmp");
    mCloudsBitmap2 = ResourceHandler::getInstance()->getBitmap("clouds2.bmp");
    mCloudsBitmap3 = ResourceHandler::getInstance()->getBitmap("clouds3.bmp");
}

void CloudsBackground::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
     masked_blit(mCloudsBitmap3, 
               dest,
                ((mWind / 6)% 320), 
                0,
                0,
                0,
                mCloudsBitmap3->w,
                mCloudsBitmap3->h);
    masked_blit(mCloudsBitmap3, 
                dest,
               ((mWind / 6)% 320) - 320, 
                0,
                0,
                0,
                mCloudsBitmap3->w,
                mCloudsBitmap3->h);
    masked_blit(mCloudsBitmap2, 
               dest,
               ((mWind / 4) % 320),
                0,
                0,
                0,
                mCloudsBitmap2->w,
                mCloudsBitmap2->h);
    masked_blit(mCloudsBitmap2, 
                dest,
               ((mWind / 4) % 320) - 320, 
                0,
                0,
                0,
                mCloudsBitmap2->w,
                mCloudsBitmap2->h);
    masked_blit(mCloudsBitmap1, 
               dest,
               ((mWind / 2) % 320), 
                0,
                0,
                0,
                mCloudsBitmap1->w,
                mCloudsBitmap1->h);
    masked_blit(mCloudsBitmap1, 
                dest,
               ((mWind / 2) % 320) - 320,
                0,
                0,
                0,
                mCloudsBitmap1->w,
                mCloudsBitmap1->h);
}

void CloudsBackground::logic(Level* level)
{
    mRoomWidth = level->getTileMap()->getWidth() * 16;    
    mRoomHeight = level->getTileMap()->getHeight() * 16;

    mWind++;
}
