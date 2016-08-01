#pragma once
#include "Entity.hpp"
#include "Animation.hpp"
//#include <vector>

class Animation;

class Shot : public Entity{
public:
	Shot();
	~Shot();

	enum ShotTypes {
		ShotType_Bullet,
		ShotType_GravityGrenade,
		ShotType_Fireball,
		ShotType_Length
	} mShotTypes;

	void update();
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	void attack(Entity*);
	int getLayer();
	// returns +/-1
	int getDirection();
	void toggleDirection();
	void setDirection(int direction);
	void setShotType(int _mShotType);
	int getShotType();
	bool hasCollided();
	void setCollided(bool _mCollided);
	void setCanHurtPlayer(bool hurtPlayer);
	void setInitialVelocity(float2 velocity);
	float2 getInitialVelocity();
private:
	bool mHurtPlayer;
	int mShotType;
	int mDamage[ShotType_Length];
	bool mGravity[ShotType_Length];
	bool mToggleGravity[ShotType_Length];
	int mDuration[ShotType_Length];
	int mGravityDuration[ShotType_Length];
	float2 mSize[ShotType_Length];
	float2 mInitialVelocity[ShotType_Length];
	int mFacingDirection;
	int mFrame;
	int cFrame;
	bool mCollided;
	int mLife;
	int mCollidedTimer;
	float GRAVITY;
	Animation* mShotAnimation[ShotType_Length];
	Animation* mCollisionAnimation[ShotType_Length];
};