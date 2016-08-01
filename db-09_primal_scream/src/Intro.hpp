#pragma once

#include "Screen.hpp"
#include <vector>
#include <string>

class Animation;
class Font;

class Intro: public Screen
{
public:
	Intro();
	void onDraw(BITMAP* aBuffer);
	void onLogic();
	void onEntered();
	void onExited();
private:
	Font* myFont;
	int myFrameCounter;
	std::vector<std::string> myTexts;
	int myTextsIndex;
	int myTextsCharecter;
	bool myWait;
};