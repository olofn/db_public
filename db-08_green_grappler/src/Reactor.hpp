#pragma once

#include "Entity.hpp"

class Animation;

class Reactor
	: public Entity
{
public:
	Reactor();

	virtual int getLayer(){return 1;}

	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	void update();
	bool isDamagable();
	void onDamage();
	virtual CollisionRect getCollisionRect();
	virtual void onRespawn();

	void setTilesCollidable(bool aCollidable);
	virtual void setRoom(Room *room);
private:
	Animation* myShell;
	Animation* myCore;
	int myDamage;
	bool myAboutToBlow;
	int myFrameCounter;
};