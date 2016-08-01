#pragma once

#include "Entity.hpp"

class WallOfDeathStarter: public Entity
{
	bool myUsed;
public:
	WallOfDeathStarter();
	virtual int getLayer(){return 1;}
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	void update();
	void onRespawn();
};