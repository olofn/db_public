#pragma once

#include "Entity.hpp"

class Animation;

class SpawnPoint : public Entity
{
public:
	SpawnPoint();
	virtual int getLayer(){return 0;}

	virtual void update();
	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);	
private:
	enum State
	{
		State_Unchecked,
		State_SemiChecked,
		State_Checked,
	} mState;

	int			mFrame;
	Animation* mAnimation;
};