#pragma once

#include "Screen.hpp"

class SplashScreen: public Screen
{
public:
	SplashScreen();
    void onLogic();
    void onDraw(BITMAP* aBuffer);

protected:
	int myFrameCounter;
    BITMAP* myDarkbitsLogo;
	BITMAP* myDarkbitsLogoBlackAndWhite;
	BITMAP* myDarkbitsLogoGlow;
	BITMAP* mySoftware2010;
	BITMAP* myDarkbitsLogoBlink;
};