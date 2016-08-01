#include "splashscreen.hpp"

#include "resourcehandler.hpp"

namespace nmc
{
    SplashScreen::SplashScreen()
        : mDrawingDone(false),
        mFrameCounter(0)
    {
        mDarkbitsLogoBitmap = ResourceHandler::getInstance()->getBitmap("darkbitslogo_by_haiko.bmp");
    }

    void SplashScreen::logic()
    {
        mFrameCounter++;
    }

    void SplashScreen::draw(BITMAP* dest)
    {
        clear_to_color(dest, makecol(255,255,255));
        
        if (mFrameCounter > 50 && mFrameCounter <= 100)
        {
			float l = ((100 - mFrameCounter) * (100 - mFrameCounter)) / (50.0 * 50.0);
			int w = mDarkbitsLogoBitmap->w * (1 + 20 * l);
			int h = (mDarkbitsLogoBitmap->h * mDarkbitsLogoBitmap->w) / w;

            masked_stretch_blit(mDarkbitsLogoBitmap, 
                                dest, 
                                0, 
                                0, 
                                mDarkbitsLogoBitmap->w,
                                mDarkbitsLogoBitmap->h,
                                160 - w / 2, 
                                120 - h / 2,
                                w,
                                h);
        }

		if (mFrameCounter > 100)
        {
			int w = mDarkbitsLogoBitmap->w;
			int h = (mDarkbitsLogoBitmap->h * mDarkbitsLogoBitmap->w) / w;
            masked_stretch_blit(mDarkbitsLogoBitmap, 
                                dest, 
                                0, 
                                0, 
                                mDarkbitsLogoBitmap->w,
                                mDarkbitsLogoBitmap->h,
                                160 - w / 2, 
                                120 - h / 2,
                                w,
                                h);
        }
    }

    bool SplashScreen::isDrawingDone()
    {
        return mFrameCounter > 200;
    }
}