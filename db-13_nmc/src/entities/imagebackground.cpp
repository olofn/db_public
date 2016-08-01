#include "entities/imagebackground.hpp"
#include "resourcehandler.hpp"

namespace nmc
{
    ImageBackground::ImageBackground(const std::string& filename, int speed)
        : mSpeed(speed)
    {
        mBackgroundBitmap = ResourceHandler::getInstance()->getBitmap(filename);
    }

    void ImageBackground::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
    {
        int horizontalBlits = 2;
        if (mBackgroundBitmap->w < 320)
        {   
            horizontalBlits = (320 / mBackgroundBitmap->w) + 1;
        }
 
        int verticalBlits = 2;
        if (mBackgroundBitmap->h < 240)
        {
            verticalBlits = (240 / mBackgroundBitmap->h) + 1;
        }

        int y;
        for (y = 0; y <= verticalBlits; y++)
        {
            int x;
            for (x = 0; x <= horizontalBlits; x++)
            {
                int screenX = x * mBackgroundBitmap->w - ((scrollx / mSpeed) % 320);
                if (screenX < - mBackgroundBitmap->w)
                {
                    screenX += 320 + mBackgroundBitmap->w;
                }

                int screenY = y * mBackgroundBitmap->h - ((scrolly / mSpeed) % 240);
                if (screenY < - mBackgroundBitmap->h)
                {
                    screenY += 240 + mBackgroundBitmap->h;
                }

                masked_blit(mBackgroundBitmap, 
                            dest,
                            0, 
                            0,
                            screenX, 
                            screenY,
                            mBackgroundBitmap->w, 
                            mBackgroundBitmap->h);
            }
        }
    }
}
