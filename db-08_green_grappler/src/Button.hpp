#pragma once

#include "Entity.hpp"

class Animation;

class Button: public Entity
{
public:
	Button(int aId);
	virtual int getLayer(){return 0;}

	void update();

	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	 void onRespawn();
private:
	Animation* myButton;
	bool mCollisionThisFrame;
	bool mTriggered;
	int myTime;
	int myCounter;
	int myId;
};