#pragma once
#include "Entity.hpp"
#include "Animation.hpp"

//class Animation;

class EnemyBoss : public Entity{
private:
	int mInitialHp;
	int mCurrentHp;
	Direction mFacingDirection;
	int mGravityHitTimer;
	int mBlinkingTicksLeft;
	int mFrame;
	int mLastTurnTick;
	int mCurrentTick;
	int mDeathFrame;
	Animation mWalkAnimation;
	Animation* mDeathAnimation;
	Animation* mGravityAnimation;
	bool myDrawHurt;
public:
	EnemyBoss();
	~EnemyBoss();

	void update();
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	virtual bool isShootable() { return true; }
	virtual bool isEnemy() { return true;}
	int getHp();
	void hit(int damage);
	int getLayer();
	// returns +/-1
	int getDirection();
	void toggleDirection();
	void toggleGravityDirection(int timer);
	void attack(int shotType);
	Direction getFacingDirection();
};