#include <cmath>
#include "skybackground.hpp"
#include "resourcehandler.hpp"
#include "level.hpp"
#include "util.hpp"

SkyBackground::SkyBackground() :
	Entity(false),
	mLevelLength(0),
	mFrameCounter(0),
	mBgScroll(0)
{
	mBackgroundColors = ResourceHandler::getInstance()->getBitmap("skybackground.bmp");

    mCloud1 = new Animation("cloud1.bmp", 1);
    mCloud2 = new Animation("cloud2.bmp", 1);
}

SkyBackground::~SkyBackground()
{
    delete mCloud1;
    delete mCloud2;
}

void SkyBackground::logic(Level* level)
{
	mLevelLength = level->getLevelLength();
	mBgScroll = level->getBackgroundScroll();
	mFrameCounter++;
}

void SkyBackground::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	float depth = (scrolly - mBgScroll) / (mLevelLength - 240.0f);

	int c = (int)(depth * 16.0f);
	float t = depth * 16.0f - c;
	int bgColor;

	if (c < 0)
	{
		bgColor = getpixel(mBackgroundColors, 0, 0);
	}
	else if (c >= 15)
	{
		bgColor = getpixel(mBackgroundColors, 0, 15);
	}
	else
	{
		int c1 = getpixel(mBackgroundColors, 0, c);
		int c2 = getpixel(mBackgroundColors, 0, c + 1);
		int r = int(getr(c1) * (1.0f - t) + getr(c2) * t);
		int g = int(getg(c1) * (1.0f - t) + getg(c2) * t);
		int b = int(getb(c1) * (1.0f - t) + getb(c2) * t);
		bgColor = makecol(r, g, b);
	}

	clear_to_color(dest, bgColor);

    mCloud2->drawFrame(dest, 0, 0, - ((scrolly / 3) % 480));
    mCloud2->drawFrame(dest, 0, 0, -((scrolly  / 3) % 480) + 480);

    mCloud1->drawFrame(dest, 0, 0, - ((scrolly * 2) % 480));
    mCloud1->drawFrame(dest, 0, 0, - ((scrolly * 2) % 480) + 480);
}