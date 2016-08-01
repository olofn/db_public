#include "entities/smoke.hpp"

Smoke::Smoke(int x, int y, bool large)
:Entity(Entity::OTHER, x, y, 1, 1, false),
mSmallAnimation("graphics/smoke.bmp"),
mLargeAnimation("graphics/smoke2.bmp"),
mLarge(large)
{
	mFrameCounter=0;
	mAnimationFrame=5;
}

void Smoke::logic()
{
	mFrameCounter++;

	if (mFrameCounter % 2 == 0)
		mAnimationFrame--;
}

void Smoke::drawForeground(BITMAP *dest, int scrollx, int scrolly)
{
	if (mLarge)
		mLargeAnimation.drawFrame(dest, mAnimationFrame, mX - scrollx, mY - scrolly);
	else
		mSmallAnimation.drawFrame(dest, mAnimationFrame, mX - scrollx, mY - scrolly);
}

bool Smoke::isToBeDeleted()
{
	return mAnimationFrame < 0;
}