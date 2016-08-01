#pragma once

#include "Screen.hpp"

class Animation;
class Font;

class Title: public Screen
{
public:
	Title();
	void onDraw(BITMAP* aBuffer);
	void onLogic();
	void onEntered();
private:
	Animation* myTitle;
	Animation* myHand;
	Font* myFont;
	int mySelected;
	bool myGameStart;
	int myFrameCounter;
	bool myContinue;
};