#include "entities/parallaxscroll.hpp"
#include "resourcehandler.hpp"
#include "room.hpp"

namespace nmc
{
    ParallaxScroll::ParallaxScroll()
        : mBackgroundFloorBitmap(NULL),
          mForegroundFloorBitmap(NULL),
          mBackgroundCeilingBitmap(NULL),
          mForegroundCeilingBitmap(NULL)
    {

    }

    void ParallaxScroll::setBackgroundFloor(const std::string& filename, int offset)
    {
        mBackgroundFloorBitmap = ResourceHandler::getInstance()->getBitmap(filename);
        mBackgroundFloorOffset = offset;
    }

    void ParallaxScroll::setForegroundFloor(const std::string& filename, int offset)
    {
        mForegroundFloorBitmap = ResourceHandler::getInstance()->getBitmap(filename);
        mForegroundFloorOffset = offset;
    }

    void ParallaxScroll::setBackgroundCeiling(const std::string& filename, int offset)
    {
        mBackgroundCeilingBitmap = ResourceHandler::getInstance()->getBitmap(filename);
        mBackgroundCeilingOffset = offset;
    }

    void ParallaxScroll::setForegroundCeiling(const std::string& filename, int offset)
    {
        mForegroundCeilingBitmap = ResourceHandler::getInstance()->getBitmap(filename);
        mForegroundCeilingOffset = offset;
    }

    void ParallaxScroll::logic(Room *room)
    {
        mTileMapHeight = room->getTileMap()->getHeight() * 16;
    }

    bool ParallaxScroll::drawInLayer(unsigned int layer)
    { 
        return layer == Entity::BACKGROUND_LAYER
            || layer == Entity::FOREGROUND_LAYER;
    }

    void ParallaxScroll::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
    {
        if (layer == Entity::BACKGROUND_LAYER)
        {
            if (mBackgroundFloorBitmap != NULL)
            {
                int backgroundFloorBitmapBlits = 2;
                if (mBackgroundFloorBitmap->w < 320)
                {
                    backgroundFloorBitmapBlits = mBackgroundFloorBitmap->w / 320 + 1;
                }

                int backgroundFloorBitmapX;
                for (backgroundFloorBitmapX = 0; 
                     backgroundFloorBitmapX < backgroundFloorBitmapBlits;
                     backgroundFloorBitmapX++)
                {
                    int screenX = backgroundFloorBitmapX * mBackgroundFloorBitmap->w - ((scrollx / 2) % 320);
                    if (screenX < -mBackgroundFloorBitmap->w)
                    {
                        screenX += 320 + mBackgroundFloorBitmap->w;
                    }

                    masked_blit(mBackgroundFloorBitmap, 
                                dest, 
                                0, 
                                0, 
                                screenX, 
                                - scrolly / 2 
                                + (mTileMapHeight - mBackgroundFloorBitmap->h) / 2 
                                + mBackgroundFloorOffset, 
                                mBackgroundFloorBitmap->w, 
                                mBackgroundFloorBitmap->h);
                }
            }

            if (mBackgroundCeilingBitmap != NULL)
            {
                int backgroundCeilingBitmapBlits = 2;
                if (mBackgroundCeilingBitmap->w < 320)
                {
                    backgroundCeilingBitmapBlits = mBackgroundCeilingBitmap->w / 320 + 2;
                }

                int backgroundCeilingBitmapX;
                for (backgroundCeilingBitmapX = 0; 
                     backgroundCeilingBitmapX < backgroundCeilingBitmapBlits;
                     backgroundCeilingBitmapX++)
                {
                    int screenX = backgroundCeilingBitmapX * mBackgroundCeilingBitmap->w - ((scrollx / 2) % 320);
                    if (screenX < -mBackgroundCeilingBitmap->w)
                    {
                        screenX += 320 + mBackgroundCeilingBitmap->w;
                    }

                    masked_blit(mBackgroundCeilingBitmap, 
                                dest, 
                                0, 
                                0, 
                                screenX, 
                                - scrolly / 2 + mBackgroundCeilingOffset, 
                                mBackgroundCeilingBitmap->w, 
                                mBackgroundCeilingBitmap->h);
                }
            }
     
           return;  
        }

        if (layer == Entity::FOREGROUND_LAYER)
        {
            if (mForegroundCeilingBitmap != NULL)
            {
                int foregroundCeilingBitmapBlits = 2;
                if (mForegroundCeilingBitmap->w < 320)
                {
                    foregroundCeilingBitmapBlits = mForegroundCeilingBitmap->w / 320 + 2;
                }

                int foregroundCeilingBitmapX;
                for (foregroundCeilingBitmapX = 0; 
                     foregroundCeilingBitmapX < foregroundCeilingBitmapBlits;
                     foregroundCeilingBitmapX++)
                {
                    int screenX = foregroundCeilingBitmapX 
                        * mForegroundCeilingBitmap->w 
                        - ((int)(scrollx * 1.5) % 320);
                    if (screenX < -mForegroundCeilingBitmap->w)
                    {
                        screenX += 320 + mForegroundCeilingBitmap->w;
                    }

                    masked_blit(mForegroundCeilingBitmap, 
                                dest, 
                                0, 
                                0, 
                                screenX, 
                                - scrolly * 2 + mForegroundCeilingOffset, 
                                mForegroundCeilingBitmap->w, 
                                mForegroundCeilingBitmap->h);
                }
            }

            if (mForegroundFloorBitmap != NULL)
            {
                int foregroundFloorBitmapBlits = 2;
                if (mForegroundFloorBitmap->w < 320)
                {
                    foregroundFloorBitmapBlits = mForegroundFloorBitmap->w / 320 + 2;
                }

                int foregroundFloorBitmapX;
                for (foregroundFloorBitmapX = 0; 
                     foregroundFloorBitmapX < foregroundFloorBitmapBlits;
                     foregroundFloorBitmapX++)
                {
                    int screenX = foregroundFloorBitmapX 
                        * mForegroundFloorBitmap->w 
                        - ((int)(scrollx * 1.5f) % 320);
                    if (screenX < -mForegroundFloorBitmap->w)
                    {
                        screenX += 320 + mForegroundFloorBitmap->w;
                    }

                    masked_blit(mForegroundFloorBitmap, 
                                dest, 
                                0, 
                                0, 
                                screenX, 
                                - scrolly + mTileMapHeight - mForegroundFloorBitmap->h + mForegroundFloorOffset,
                                mForegroundFloorBitmap->w, 
                                mForegroundFloorBitmap->h);
                }
            }

            return;
        }
    }
}