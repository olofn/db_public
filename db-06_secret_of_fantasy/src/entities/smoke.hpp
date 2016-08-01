#ifndef DB_SMOKE_HPP
#define DB_SMOKE_HPP

#include "entity.hpp"
#include "animation.hpp"

class Smoke : public Entity
{
public:
	Smoke(int x, int y, bool large = false);

	void logic();

	void draw(BITMAP *dest, int scrollx, int scrolly) {}

	void drawForeground(BITMAP *dest, int scrollx, int scrolly);

	bool isToBeDeleted();

private:
	Animation mSmallAnimation;
	Animation mLargeAnimation;
	int mFrameCounter;
	int mAnimationFrame;
	bool mLarge;
};

#endif