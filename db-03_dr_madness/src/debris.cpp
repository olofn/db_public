#include <allegro.h>

#include "debris.hpp"
#include "level.hpp"

Debris::Debris(int x, int y, float dx, float dy, const std::string& file, int animSpeed, bool autoRemove) :
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

void Debris::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	if (mToBeDeleted)
	{
		return;
	}

	int x = getX();
	int y = getY() - scrolly;
	mAnimation.drawFrame(dest, mFrameCounter / mAnimSpeed, x, y);
}

void Debris::logic(Level *level)
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

	if (mX > Level::LEVEL_WIDTH ||
		mY > 500 + level->getScrollY() ||
		mX + mW <= 0 ||
		mY + mH <= level->getScrollY())
	{
		mToBeDeleted = true;
	}
}

bool Debris::isToBeDeleted()
{
	return mToBeDeleted;
}