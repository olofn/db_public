#pragma once

#include "Constants.hpp"

class Room;

class Entity
{
protected:
	float2 mPosition;
	float2 mVelocity;
	float2 mSize;
	int mGravityDirection;

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

	virtual int getLayer() = 0;
	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	virtual bool isShootable() { return false; }
	virtual bool isSolid() { return false; }
	virtual bool isEnemy() { return false;}

	// returns +1 or -1
	virtual int getGravityDirection();
	virtual void toggleGravityDirection(int timer);

	virtual void hit(int damage);
	virtual void setPosition(float2 position);
	virtual float2 getPosition();
	virtual int getDrawPositionX();
	virtual int getDrawPositionY();
	virtual void setInitialPosition(float2 position);

	virtual bool touchesDangerousTile();

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

	virtual void remove();
	virtual bool isRemoved();
};