#pragma once

#include "Screen.hpp"

class Font;

class End: public Screen
{
public:
	End();
	void onDraw(BITMAP* aBuffer);
	void onLogic();
	void onEntered();
private:
	Font* myFont;
	int myFrameCounter;
	int myCreditsOffset;
	bool myPlayEnd;
};