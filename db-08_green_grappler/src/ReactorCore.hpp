#pragma once

#include "Entity.hpp"

class Animation;

class ReactorCore: public Entity
{
public:
	ReactorCore();
	virtual int getLayer(){return 1;}

	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);

private:

	Animation* mAnimation;
	int mFrame;	
};