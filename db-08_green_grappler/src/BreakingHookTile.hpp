#pragma once

#include "Entity.hpp"
#include "Animation.hpp"

class BreakingHookTile : public Entity
{
private:
	Animation mSprite;
	int mBreakCounter;
	bool mBreaking;
	int mTileX;
	int mTileY;
	bool mDestroyed;
public:
	BreakingHookTile();
	virtual int getLayer(){return 0;}

	virtual void setRoom(Room *room);

	virtual void onRespawn();

	virtual void update();

	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
};