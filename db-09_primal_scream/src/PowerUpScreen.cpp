#include "Precompiled.hpp"

#include "PowerUpScreen.hpp"

#include "Font.hpp"
#include "Resource.hpp"
#include "Constants.hpp"
#include "Sound.hpp"
#include "Music.hpp"
#include "ScreenManager.hpp"
#include "GameState.hpp"
#include "World.hpp"

PowerUpScreen::PowerUpScreen(const std::string& aName,
	const std::string& aUsage)
	: myName(aName)
	, myUsage(aUsage)
	, myFrameCounter(0)
{
	myFont = Resource::getFont("data/images/font.bmp");	
	myFontUsage = Resource::getFont("data/images/font.bmp", makecol(28, 151, 240));	
}

void PowerUpScreen::onDraw( BITMAP* aBuffer )
{
	rectfill(aBuffer, 60, 100, 260, 140, 0);
	rect(aBuffer, 60, 100, 260, 140, 0xffffff);
	rect(aBuffer, 62, 102, 260 - 2, 140 - 2, 0xffffff);

	myFont->drawCenterX(aBuffer, myName, 0, 120 - myFont->getHeight(), 320);
	myFontUsage->drawCenterX(aBuffer, myUsage, 0, 125, 320);
}

void PowerUpScreen::onLogic()
{
	myFrameCounter++;

	if (myFrameCounter >= 60 * 4)
	{
		ScreenManager::exit(this);
		return;
	}
}

void PowerUpScreen::onEntered()
{
	Music::pushSong();
	Music::playSong("data/music/powerup.xm");
}	

void PowerUpScreen::onExited()
{
	Music::popSong();
}