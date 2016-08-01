#pragma once

class Screen;

#include <allegro.h>
#include <vector>

class ScreenManager
{
public:
	static void init();
	static void destroy();
	static void onLogic();
	static void draw(BITMAP* buffer);
	static Screen* getTop();
	static bool isEmpty();
	static void add(Screen* screen);
	static void enter(Screen* screen);
	static void exit(Screen* screen);

private:
	ScreenManager();
	static std::vector<Screen*> myStack;
	static Screen* myScreenToExit;
	static Screen* myScreenToEnter;
};
