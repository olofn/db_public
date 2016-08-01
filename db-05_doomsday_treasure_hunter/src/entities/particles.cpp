#include "entities/particles.hpp"

#include "level.hpp"

#include <allegro.h>

Particles::Particles(int x, int y, float dx, float dy, const std::string& file, int animSpeed, bool autoRemove) :
	Entity(false),
	mAnimation(file),
	mAnimSpeed(animSpeed),
	mAutoRemove(autoRemove),
	mToBeDeleted(false),
	mFrameCounter(0)
{
	setSize(mAnimation.getFrameWidth() / 2, mAnimation.getFrameHeight() / 2);
	mX = (float)x - mW / 2;
	mY = (float)y - mH / 2;
	mDX = dx;
	mDY = dy;
	setPosition((int)mX, (int)mY);
}

void Particles::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
	if (mToBeDeleted)
	{
		return;
	}

	int x = getX() - scrollx;
	int y = getY() - scrolly;
	mAnimation.drawFrame(dest, mFrameCounter / mAnimSpeed, x, y);
}

void Particles::logic(Level *level)
{
	mFrameCounter++;

	mDX *= 0.9f;
	mDY += (-3.0f - mDY) * 0.05f;

	mX += mDX;
	mY += mDY;

	setPosition((int)mX, (int)mY);


	if (mAutoRemove && mFrameCounter / mAnimSpeed >= mAnimation.getFrameCount())
	{
		mToBeDeleted = true;
	}

    if (mX > level->getTileMap()->getWidth() * 16 ||
		mY > 500 + level->getCamera()->getY() ||
		mX + mW <= 0 ||
		mY + mH <= level->getCamera()->getY())
	{
		mToBeDeleted = true;
	}
}

bool Particles::isToBeDeleted()
{
	return mToBeDeleted;
}
