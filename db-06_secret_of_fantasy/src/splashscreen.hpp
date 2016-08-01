#ifndef DBSH07_SPLASHSCREEN_HPP
#define DBSH07_SPLASHSCREEN_HPP

#include <allegro.h>

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
#endif