#pragma once

#include "Entity.hpp"
#include "Animation.hpp"

class MovingHookTile : public Entity
{
private:
	Animation mSprite;
	bool hasHook;
	float2 mInitialPosition;
	float2 mInitialVelocity;

public:
	MovingHookTile();
	virtual int getLayer(){return 0;}

	virtual void setRoom(Room *room);

	virtual void update();

	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);

	virtual bool isHookable();

	virtual void onRespawn();
};