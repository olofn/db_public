#pragma once

#include "Entity.hpp"
#include "Animation.hpp"

class Animation;

class Hero : public Entity
{
private:
	bool myIsDead;
	bool mOnGround;
	bool mJumpHeld;
	bool mJumpPrepressed;
	int	mBlinkingTicksLeft;
	int mFramesSinceLandPlayed;

	Direction mFacingDirection;
	Animation mAnimationRun;
	Animation mAnimationJump;
	Animation mAnimationFall;
	Animation mAnimationHurt;
	
	float2 mSpawnPoint;

	enum MovementState
	{
		MovementState_Still,
		MovementState_Run,
		MovementState_Jump,
		MovementState_Fall
	} mMovementState;

	enum Weapon
	{
		Weapon_None,
		Weapon_Gun,
		Weapon_Gravity_Grenade,
		Weapon_Length
	} mWeapon;
	int mWeaponSelected;
	int mFrame;
	bool myImortal;
	int mGravityHitTimer;
	bool mySpawnPortal;
	int mySpawnPortalFrameCounter;

public:
	Hero();
	~Hero();

	virtual int getLayer() { return 1; }

	void kill();
	void die();	
	void respawn();
	bool isDead();
	void remove();
	void imortal();
	void toggleWeapon();
	void fireWeapon();
	void checkEnemies();
	bool moveOutOfSolidEntities();
	float2 getSeparationVector(CollisionRect r1, CollisionRect r2);
	void setLastSpawnPoint(float2 aPosition);

	Direction getFacingDirection();
	void toggleGravityDirection(int timer);
	virtual void setRoom(Room *room);
	void setSpawnPortal(bool aSpawn);
	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
};