#pragma once

#include "Entity.hpp"

class Animation;

class LavaSea : public Entity
{
public:
	LavaSea();
	virtual int getLayer(){return 4;}

	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	virtual void onRespawn();
	virtual CollisionRect getCollisionRect();
	virtual int getCurrentY();
	virtual void onLevelComplete();


private:
	int mFrame;
	bool mSafeMode;
	int mSafeLevel;

	Animation* mTopAnimation;
	Animation* mFillAnimation;

	Random mRandom;
};