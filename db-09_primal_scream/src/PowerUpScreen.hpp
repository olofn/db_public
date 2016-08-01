#pragma once

#include "Screen.hpp"

#include <string>
class Animation;
class Font;

class PowerUpScreen: public Screen
{
public:
	PowerUpScreen(
		const std::string&	aName,
		const std::string&	aUsage);
	void onDraw(BITMAP* aBuffer);
	void onLogic();
	void onEntered();
	void onExited();
private:
	Font* myFont;
	Font* myFontUsage;
	int myFrameCounter;
	std::string myName;
	std::string myUsage;
};