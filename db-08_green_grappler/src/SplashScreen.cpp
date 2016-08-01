#include "SplashScreen.hpp"
#include "Resource.hpp"
#include "Sound.hpp"
#include "Animation.hpp"

SplashScreen::SplashScreen()
    : mFrameCounter(0)
{
    mLogo = Resource::getAnimation("data/images/logo.bmp", 1);
}

void SplashScreen::onLogic()
{	
	if (mFrameCounter > 250)
	{
		exit();
		return;
	}

    mFrameCounter++;
}

void SplashScreen::onDraw(BITMAP* aBuffer)
{
	int yOffset = - 160 + mFrameCounter;

	if (yOffset == 0)
		Sound::playSample("data/sounds/boot.wav");
	if (yOffset > 0)
		yOffset = 0;
	rectfill(aBuffer, 0, 0, 320, 240, makecol(231,215,156));
    mLogo->drawFrame(aBuffer, 0, 160 - mLogo->getFrameWidth() / 2, 120 - mLogo->getFrameHeight() / 2 + yOffset);
}
