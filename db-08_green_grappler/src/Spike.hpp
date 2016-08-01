#pragma once

#include "Entity.hpp"
#include "Tile.hpp"

class Animation;

class Spike : public Entity
{
public:
	Spike();

	virtual int getLayer(){return 1;}

	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	virtual CollisionRect getCollisionRect();

private:

	Tile mSpikeTile;
};