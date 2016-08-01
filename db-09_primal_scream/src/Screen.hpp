#pragma once 

#include <allegro.h>

class Screen
{
public:
	virtual ~Screen() {}
	
	virtual bool onEnter(BITMAP* aBuffer) { return true; }
	virtual void onEntered() {}
	virtual bool onExit(BITMAP* aBuffer) { return true; }
	virtual void onExited() {};
	virtual void onDraw(BITMAP* aBuffer) = 0;
	virtual void onLogic() = 0;

	bool isTop() const;
	void exit();
};