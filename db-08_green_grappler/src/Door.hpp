#pragma once

#include "Entity.hpp"

class Animation;

class Door: public Entity
{
public:
	Door(int aId);
	virtual int getLayer(){return 0;}
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	void update();
	void onButtonDown(int aId);
	void onButtonUp(int aId);
	void onRespawn();
private:
	BITMAP* myDoor;
	int myId;
	bool myOpening;
	bool myClosing;
	int myFrameCounter;
	bool myInited;
	int myDoorHeight;
};