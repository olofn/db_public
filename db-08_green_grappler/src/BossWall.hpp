#pragma once

#include "Entity.hpp"
#include "Constants.hpp"

class Animation;

class BossWall: public Entity
{
public:
	BossWall(Direction aDirection);
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	void update();
	int getLayer();
	void setTilesCollidable( bool aCollidable );
	void setRoom( Room *room );
	void onBossWallActivate();
	void onBossWallDeactivate();
	void onRespawn();
private:
	Direction myDirection;
	int myFrameCounter;
	bool myActive;
	Animation* myWall;
};