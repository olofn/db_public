#pragma once

#include <string>
#include <allegro.h>

class Game
{
public:
	Game(const std::string& title, bool windowed = false);
    virtual ~Game();
    void run();
protected:
	virtual void onLogic() = 0;
	
	void halt();
	void setTitle(const char* format, ...);
	void toggleSlowMotion();
	void toggleFullscreen();
	void toggleVSync();
	void toggleWideScreen();

private:
	void initGraphics(bool windowed);
	void privChangeResolution(bool aWindowed);

	bool myRunning;
	bool mySlowMotion;
	bool myVSync;
	bool myWindowed;
	bool myWideScreen;
	std::string myTitle;
	int myResolutionWidth;
	int myResolutionHeight;

	BITMAP* myScreenBuffer;
};
