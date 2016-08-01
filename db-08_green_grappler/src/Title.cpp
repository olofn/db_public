#include "Title.hpp"

#include "Animation.hpp"
#include "Font.hpp"
#include "Resource.hpp"
#include "Input.hpp"
#include "Constants.hpp"
#include "Sound.hpp"
#include "Music.hpp"
#include "LevelSelect.hpp"
#include "ScreenManager.hpp"
#include "GameState.hpp"
#include "Level.hpp"
#include "LevelDescription.hpp"

Title::Title()
: mySelected(0)
, myGameStart(false)
, myContinue(false)
{
	myTitle = Resource::getAnimation("data/images/title.bmp", 1);
	myHand = Resource::getAnimation("data/images/hand.bmp", 1);
	myFont = Resource::getFont("data/images/font.bmp");	
}

void Title::onDraw( BITMAP* aBuffer )
{
	myTitle->drawFrame(aBuffer, 0, 0, 0);

	if (!myGameStart)
		myHand->drawFrame(aBuffer, 0, 115, 150 + mySelected * 10);

	if (!myGameStart || (mySelected != 0 || myFrameCounter % 10 < 5))
		myFont->draw(aBuffer, "NEW GAME", 126, 150);
	
	if (myContinue)
	{
		if (!myGameStart || (mySelected != 1 || myFrameCounter % 10 < 5))
			myFont->draw(aBuffer, "CONTINUE", 126, 160);
		myFont->draw(aBuffer, "EXIT GAME", 126, 170);
	}
	else
	{
		myFont->draw(aBuffer, "EXIT GAME", 126, 160);
	}

	myFont->draw(aBuffer, "DARKBITS", 130, 215);
	myFont->draw(aBuffer, "SPEEDHACK 2011", 113, 225);
}

void Title::onLogic()
{
	myFrameCounter++;

	if (myGameStart)
	{
		if (myFrameCounter > 100)
		{
			ScreenManager::add(new LevelSelect());
			if (mySelected == 0)
			{
				ScreenManager::add(new Level(LevelDesc("tutorial", "data/rooms/tutorial.tmx", 0, "data/music/olof9.xm")));
			}
		}
		return;
	}

	if (Input::isPressed(Button_Down))
	{
		mySelected++;
		if (mySelected > 1 && !myContinue)
			mySelected = 1;
		else if (mySelected > 2)
			mySelected = 2;
		else
			Sound::playSample("data/sounds/select.wav");
	}

	if (Input::isPressed(Button_Up))
	{
		mySelected--;
		if (mySelected < 0)
			mySelected = 0;
		else
			Sound::playSample("data/sounds/select.wav");
	}

	if (Input::isPressed(Button_Fire))
	{
		if (mySelected == 0)
		{
			myGameStart = true;
			myFrameCounter = 0;
			Music::stop();
			Sound::playSample("data/sounds/start.wav");
			GameState::clear();
		}
		if (mySelected == 1 && myContinue)
		{
			myGameStart = true;
			myFrameCounter = 0;
			Music::stop();
			Sound::playSample("data/sounds/start.wav");
			GameState::loadFromFile();
		}

		if (mySelected == 1 && !myContinue)
			exit();
		if (mySelected == 2 && myContinue)
			exit();
	}
}

void Title::onEntered()
{
	myGameStart = false;
	Music::playSong("data/music/intro2.xm");

	if (GameState::isSavePresent())
		myContinue = true;
	else
		myContinue = false;
	if (myContinue)
		mySelected = 1;
}	
