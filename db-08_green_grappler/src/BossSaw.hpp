#pragma once

#include "Entity.hpp"
#include "Constants.hpp"

class Animation;

class BossSaw: public Entity
{
public:
	BossSaw(Direction aDirection);
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	void update();
	int getLayer();
	void onRespawn();
private:
	Animation* mySaw;
	float2 mySpeed;
	int myLifeTime;
	int myFrameCounter;
};