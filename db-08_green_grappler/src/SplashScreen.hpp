#pragma once

#include "Screen.hpp"

class Animation;

class SplashScreen: public Screen
{
public:
	SplashScreen();
    void onLogic();
    void onDraw(BITMAP* aBuffer);

protected:
	Animation* mLogo;
    int mFrameCounter;
};