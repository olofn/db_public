#include "Screen.hpp"
#include "ScreenManager.hpp"

bool Screen::isTop() const
{ 
	return  ScreenManager::getTop() == this;
}

void Screen::exit()
{
     ScreenManager::exit(this);
}