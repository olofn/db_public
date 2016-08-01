#pragma once

#include "Entity.hpp"
#include "Animation.hpp"

class Animation;

class Hero : public Entity
{
public:
	enum RopeState {
		RopeState_Retracted,
		RopeState_Moving,
		RopeState_Attached,
		RopeState_Dissapearing,
	};

private:
	bool myIsDead;
	bool mOnGround;
	bool mJumpHeld;
	bool mJumpPrepressed;
	int mRopeDissapearCounter;
	int	 mBlinkingTicksLeft;
	Direction mFacingDirection;

	enum MovementState
	{
		MovementState_Still,
		MovementState_Run,
		MovementState_AirRun,
		MovementState_Jump,
		MovementState_Fall
	} mMovementState;

	RopeState mRopeState;
	float2 mRopePosition;
	float2 mRopeVelocity;
	Entity *mHookedEntity;
	float2 mHookedEntityOffset;

	float2 adjustRopeDirection(float2 direction);
	float getAutoAimScore(float2 direction, float2 autoAimPos);

public:
	Hero();
	~Hero();

	virtual int getLayer(){return 2;}

	bool gotCoin();
	bool gotCore();
	void kill();
	void die();	
	void respawn();
	bool isDead();
	void remove();
	void imortal();

	void setLastSpawnPoint(float2 aPosition);
	void detachHook();
	bool hasHook();
	CollisionRect getHookCollisionRect();
	Entity *getHookedEntity();

	RopeState getRopeState();
	float2 getRopePosition();
	Direction getFacingDirection();

	virtual void setRoom(Room *room);


	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	Animation mAnimationRun;
	Animation mAnimationJump;
	Animation mAnimationFall;
	Animation mAnimationRope;
	Animation mAnimationHook;
	Animation mAnimationHurt;
	Animation *mAnimationHookParticle;

	float2 mSpawnPoint;

private:

	int mFrame;
	int mRopeMaxLenghth;
	bool myImortal;
};