#pragma once

#include "Entity.hpp"
class BossFloor: public Entity
{
public:
	BossFloor();
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	void update();
	int getLayer();
	Entity::CollisionRect getCollisionRect();
	void onBossFloorActivate();
	void onRespawn();
private:
	bool myActive;
	int myFrameCounter;
};