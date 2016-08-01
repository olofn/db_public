#include "Precompiled.hpp"
#include "ScreenManager.hpp"
#include "Screen.hpp"

std::vector<Screen*> ScreenManager::myStack;
Screen* ScreenManager::myScreenToExit = 0;
Screen* ScreenManager::myScreenToEnter = 0;

ScreenManager::ScreenManager()
{
}

void ScreenManager::init()
{
}

void ScreenManager::destroy()
{
	for (unsigned int i = 0; i < myStack.size(); i++)
	{
		delete myStack[i];
	}
}

Screen* ScreenManager::getTop()
{
	if (myStack.size() == 0)
		return 0;
	return myStack[myStack.size() - 1];
}

bool ScreenManager::isEmpty()
{
	return myStack.empty();
}

void ScreenManager::add( Screen* screen )
{
	myStack.push_back(screen);
	myScreenToEnter = screen;
}

void ScreenManager::enter(Screen* screen)
{
	if (getTop() != 0)
	{
		myScreenToExit = getTop();
	}

	myStack.push_back(screen);
}

void ScreenManager::exit(Screen* screen)
{
	if (getTop() != screen)
	{
		throw std::string("A screen cannot exit another screen!");
	}

	if (myScreenToExit != 0)
	{
		throw std::string("Screen to exit is already set!");
	}

	myScreenToExit = screen;
}

void ScreenManager::onLogic()
{
	if (myScreenToExit == 0 && myScreenToEnter == 0)
	{
		Screen* screen = getTop();
		if (screen)
			screen->onLogic();
	}
}

void ScreenManager::draw(BITMAP* aBuffer)
{
	if (myScreenToExit == 0 && myScreenToEnter == 0)
	{
		Screen* screen = getTop();
		if (screen)
			screen->onDraw(aBuffer);
	}

	if (myScreenToExit)
	{
		bool exitDone = myScreenToExit->onExit(aBuffer);

		if (!exitDone)
			return;

		for (unsigned int i = 0; i < myStack.size(); i++)
		{
			if (myStack[i] == myScreenToExit)
			{
				myStack.erase(myStack.begin() + i);
				break;
			}
		}
		myScreenToExit->onExited();
		delete myScreenToExit;
		myScreenToExit = 0;

		if (getTop() != 0)
		{
			myScreenToEnter = getTop();
		}
	}

	if (myScreenToEnter)
	{
		bool enterDone = myScreenToEnter->onEnter(aBuffer);
		if (!enterDone)
			return;

		myScreenToEnter->onEntered();

		myScreenToEnter = 0;
	}
}
