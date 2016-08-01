#pragma once

#include "Constants.hpp"

class Room;




class Entity
{
protected:
	float2 mPosition;
	float2 mVelocity;
	float2 mSize;
	bool mRemoved;
	int mFrameCounter;
	Room *mRoom;

public:
	Entity();
	virtual ~Entity();

	struct  CollisionRect
	{
		float2 myTopLeft;
		float2 myBottomRight;
	};
	static bool Collides(const CollisionRect& aRect1, CollisionRect& aRect2);

	virtual void setPosition(float2 position);
	virtual float2 getPosition();
	virtual int getDrawPositionX();
	virtual int getDrawPositionY();

	virtual int getLayer() = 0;

	virtual void setVelocity(float2 velocity);
	virtual float2 getVelocity();

	virtual void setSize(float2 size);
	virtual float2 getSize();
	virtual float2 getHalfSize();

	virtual CollisionRect getCollisionRect();

	virtual void setRoom(Room *room);
	virtual Room *getRoom();

	virtual unsigned int moveWithCollision(float2 delta);
	virtual unsigned int moveWithCollision();

	virtual void update();

	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);

	virtual void remove();
	virtual bool isRemoved();
	virtual bool isDamagable();
	virtual bool isHookable();
	virtual void onDamage();
	virtual void onButtonUp(int aId);
	virtual void onButtonDown(int aId);
	virtual void onRespawn();
	virtual void onLevelComplete();
	virtual void onStartWallOfDeath();
	virtual void onBossFloorActivate();
	virtual void onBossWallActivate();
	virtual void onBossWallDeactivate();
};