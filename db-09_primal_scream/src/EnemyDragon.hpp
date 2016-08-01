#pragma once
#include "Entity.hpp"
#include "Animation.hpp"

//class Animation;

class EnemyDragon : public Entity{
private:
	int mInitialHp;
	int mCurrentHp;
	int mFacingDirection;
	int mGravityHitTimer;
	int mBlinkingTicksLeft;
	int mFrame;
	int mLastTurnTick;
	int mCurrentTick;
	int mDeathFrame;
	bool mShootable;
	bool mWalking;
	float2 mSpeed;
	Animation mWalkAnimation;
	Animation mFlyAnimation;
	Animation* mDeathAnimation;
	Animation* mGravityAnimation;
	bool myDrawHit;
public:
	EnemyDragon(bool isWalking, float2 speed);
	~EnemyDragon();

	void update();
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	virtual bool isShootable() { return mShootable; }
	virtual bool isEnemy() { return true;}
	int getHp();
	void hit(int damage);
	int getLayer();
	// returns +/-1
	int getDirection();
	void toggleDirection();
	void toggleGravityDirection(int timer);
	void setWalking(bool walks);
};