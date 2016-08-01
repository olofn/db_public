#pragma once

#include "Entity.hpp"

class Animation;

class SimpleWalkingMonster : public Entity
{
public:

	SimpleWalkingMonster();

	virtual int getLayer(){return 1;}

	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	virtual bool isDamagable();
	virtual void onDamage();

	void die();

private:

	enum State
	{
		State_Walking,
		State_Idling,
	} mState;

	enum Facing
	{
		Facing_Left,
		Facing_Right
	} mFacing;

	float2 mVelocity;
	Random mRand;

	Animation* mAnimation;
	int mFrame;

};