#pragma once

#include "Screen.hpp"
#include "LevelDescription.hpp"
class Room;
class Animation;
class Font;

class Level: public Screen
{
public:
	Level(const LevelDesc& aLevelDesc);
	void onDraw(BITMAP* aBuffer);
	void onLogic();
private:
	Room*	  myRoom;
	Animation* myDarken;
	Animation* myHand;
	Animation* myExitBackground;
	bool myExit;
	Font* myFont;
	int mySelected;
	LevelDesc myLevelDesc;
};