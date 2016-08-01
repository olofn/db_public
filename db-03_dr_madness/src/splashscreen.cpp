#include <cmath>
#include <iostream>

#include "splashscreen.hpp"
#include "resourcehandler.hpp"
#include "music.hpp"

SplashScreen::SplashScreen()
    : mDrawingDone(false),
    mFrameCounter(0)
{
    mDarkbitsLogoBitmap = ResourceHandler::getInstance()->getBitmap("darkbitslogo_by_haiko.bmp");
}

void SplashScreen::logic()
{	
	playMusic("splash.xm");
    mFrameCounter++;
}

void SplashScreen::draw(BITMAP* dest)
{
    clear_to_color(dest, makecol(255,255,255));
    
    //if (mFrameCounter > 50 && mFrameCounter <= 100)
    //{
		
		//float l = ((100 - mFrameCounter) * (100 - mFrameCounter)) / (50.0 * 50.0);
		//float l2 = (160 - mFrameCounter) / (160.0);

		//if(mFrameCounter > 100) l = 0;
		//if(mFrameCounter > 160) l2 = 0;
		//std::cout << l << std::endl;
		float stretch = std::cos(mFrameCounter*0.4f) / (mFrameCounter * 0.2f);

		if (mFrameCounter > 150)
		{
			stretch = 0;
		}

		int w = mDarkbitsLogoBitmap->w * std::pow(2.0f, stretch);//(1 + 20 * l);
		//w = mDarkbitsLogoBitmap->w * std::sin(mFrameCounter/1.2)*(40.0*(l2));

		if (w <= 0)
		{
			w = 1;
		}

		int h = (mDarkbitsLogoBitmap->h * mDarkbitsLogoBitmap->w) / w;
		
//		w += std::sin(mFrameCounter/2.0)*(100.0*(l2));

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
    //}
}

bool SplashScreen::isDrawingDone()
{
    return mFrameCounter > 300;
}
