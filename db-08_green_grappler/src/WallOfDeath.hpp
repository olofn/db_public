#pragma once

#include "Entity.hpp"

class Animation;

class WallOfDeath
	: public Entity
{
public:
	WallOfDeath();
	virtual int getLayer(){return 1;}
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	void update();
	void onRespawn();
	void onStartWallOfDeath();

private:
	bool myInited;
	float mySoundCountdown;
	float2 myOriginalPosition;
	bool myBoost;
	float mySpeed;
	Animation* mySaw;
	int myFrameCounter;
	bool myRunning;
};