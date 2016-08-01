#include <cmath>
#include "waterbackground.hpp"
#include "resourcehandler.hpp"
#include "level.hpp"
#include "util.hpp"

WaterBackground::WaterBackground() :
	Entity(false),
	mLevelLength(0),
	mFrameCounter(0),
	mBgScroll(0)
{
	mBackgroundColors = ResourceHandler::getInstance()->getBitmap("waterbackground.bmp");

	for (int i = 0; i < 200; i++)
	{
		float x = frand() * 240 * 20;
		float y = frand() * 240 * 20;
		float z = frand() * 15 + 5;
		mParticles.push_back(Particle(x, y, z));
	}	
}

WaterBackground::~WaterBackground()
{
}

void WaterBackground::logic(Level* level)
{
	mLevelLength = level->getLevelLength();

	for (unsigned int i = 0; i < mParticles.size(); i++) {
		mParticles[i].dx += std::sin(mFrameCounter / 50.0) * 3 + std::sin(mFrameCounter / 7.0 + i) * 2 + frand() - 0.5;
		mParticles[i].dy += std::cos(mFrameCounter / 50.0) + std::sin(mFrameCounter / 8.0 + i) * 2 + frand() - 1.5;
		mParticles[i].dx *= 0.95;
		mParticles[i].dy *= 0.95;
		mParticles[i].x += mParticles[i].dx;
		mParticles[i].y += mParticles[i].dy;
	}

	mBgScroll = level->getBackgroundScroll();

	mFrameCounter++;
}

void WaterBackground::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	if (layer == Entity::BACKGROUND_LAYER)
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

		for (unsigned int i = 0; i < mParticles.size(); i++)
		{
			if (mParticles[i].z < 11) {
				continue;
			}

			int x = mod(int(mParticles[i].x / mParticles[i].z), 240);
			int y = mod(int((mParticles[i].y - scrolly) / mParticles[i].z), 240);

			int c = (i * 100) / mParticles.size();

			putpixel(dest, x, y, makecol(100 + c, 120 + c, 150 + c));
		}
	}
	else
	{
		for (unsigned int i = 0; i < mParticles.size(); i++)
		{
			if (mParticles[i].z >= 11) {
				continue;
			}

			int x = mod(int(mParticles[i].x / mParticles[i].z), 240);
			int y = mod(int((mParticles[i].y - scrolly) / mParticles[i].z), 240);

			int c = (i * 100) / mParticles.size();

			putpixel(dest, x, y, makecol(100 + c, 120 + c, 150 + c));
		}
	}
}