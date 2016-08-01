#include <cmath>

#include "ending.hpp"
#include "util.hpp"
#include "resourcehandler.hpp"

Ending::Ending() :
	mFrameCounter(0),
	mPlanet("planetoid.bmp"),
	mExplosion("explosion.bmp")
{
	mS1 = ResourceHandler::getInstance()->getSample("explo1.wav");
	mS2 = ResourceHandler::getInstance()->getSample("explo2.wav");
}

void Ending::reset()
{
	mFrameCounter = 0;
}

void Ending::logic()
{
	if (mFrameCounter == 20)
	{
		play_sample(mS1, 255, 108, 200, 0);
		play_sample(mS1, 255, 148, 205, 0);
	}

	if (mFrameCounter == 90)
	{
		play_sample(mS2, 255, 128, 1000, 0);
		play_sample(mS2, 255, 108, 400, 0);
		play_sample(mS2, 255, 148, 405, 0);
		play_sample(mS2, 255, 0, 200, 0);
		play_sample(mS2, 255, 255, 205, 0);
	}

	if (mFrameCounter > 100 && mFrameCounter % 15 == 1)
	{
		play_sample(mS2, 255 / (mFrameCounter * 0.02), 128 + std::sin(mFrameCounter * 0.05) * 100, 500, 0);
		play_sample(mS1, 255 / (mFrameCounter * 0.02), 128 + std::sin(mFrameCounter * 0.06) * 100, 200, 0);
	}

	mFrameCounter++;
}

void Ending::draw(BITMAP* dest)
{
	clear_to_color(dest, makecol(30, 0, 40));

	if (mFrameCounter < 100)
	{
		int xoff = (frand() - 0.5f) * (mFrameCounter / 10.0f);
		int yoff = (frand() - 0.5f) * (mFrameCounter / 10.0f);
		
		int x = 160 - mPlanet.getFrameWidth() / 2 + xoff;
		int y = 120 - mPlanet.getFrameHeight() / 2 + yoff;

		mPlanet.drawFrame(dest, 0, x, y);
	}
	else
	{
		int x = 160 - mPlanet.getFrameWidth() / 2;
		int y = 120 - mPlanet.getFrameHeight() / 2;
	}

	if (mFrameCounter >= 90)
	{
		int f = std::max(0, 200-mFrameCounter);
		circlefill(dest, 160, 120, mFrameCounter, makecol(f, f, f));
		for (int i = 0; i < 8; i++)
		{
			int t = mFrameCounter - 90 + i * 10;

			int h = 130 * std::pow(2.0, -t * 0.02);
			int w = t * 2;

			int c = makecol(255-(8-i), 255-(8-i)*2, 255-(8-i)*6);

			ellipsefill(dest, 160, 120, w, h, c);
		}
	}
}

bool Ending::isDone()
{
	return mFrameCounter > 500;
}