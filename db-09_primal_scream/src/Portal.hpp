#pragma once

#include "Entity.hpp"

class Portal : public Entity
{
public:
	Portal();
		
	void update();

	void draw(BITMAP *dest, int scrollx, int scrolly, int layer);
	int getLayer();

private:
	int mSize;
	bool mPlayed;
	int myFrameCounter;
};
