#ifndef NMC_SPLASHSCREEN_HPP
#define NMC_SPLASHSCREEN_HPP

#include <allegro.h>

namespace nmc
{
    class SplashScreen
    {
    public:
        SplashScreen();
        void logic();
        void draw(BITMAP* dest);
        bool isDrawingDone();
    protected:
        bool mDrawingDone;
        BITMAP* mDarkbitsLogoBitmap;
        int mFrameCounter;
    };
}
#endif