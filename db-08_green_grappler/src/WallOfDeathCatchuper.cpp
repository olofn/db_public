#pragma once

#include "Entity.hpp"

// Sprinkles with tomato sauce
class WallOfDeathCatchuper: public Entity
{
public:
	WallOfDeathCatchuper();
	virtual int getLayer(){return 1;}
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	void update();
};