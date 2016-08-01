#include "Precompiled.hpp"

#include "Title.hpp"

#include "Animation.hpp"
#include "Font.hpp"
#include "Resource.hpp"
#include "Input.hpp"
#include "Constants.hpp"
#include "Sound.hpp"
#include "Music.hpp"
#include "ScreenManager.hpp"
#include "GameState.hpp"
#include "Level.hpp"
#include "LevelDescription.hpp"
#include "Room.hpp"
#include "World.hpp"
#include "Intro.hpp"

Title::Title()
: mySelected(0)
, myGameStart(false)
, myContinue(false)
, myContinueSelected(false)
{
	myTitle = Resource::getAnimation("data/images/title.bmp", 1);
	myHand = Resource::getAnimation("data/images/hand.bmp", 1);
	myFont = Resource::getFont("data/images/font.bmp");	
}

void Title::onDraw( BITMAP* aBuffer )
{
	myTitle->drawFrame(aBuffer, 0, 0, 0);

	if (!myGameStart)
		myHand->drawFrame(aBuffer, 0, 115, 150 + mySelected * 15);

	if (!myGameStart || (mySelected != 0 || myFrameCounter % 10 < 5))
		myFont->draw(aBuffer, "NEW", 136, 150);
	
	if (myContinue)
	{
		if (!myGameStart || (mySelected != 1 || myFrameCounter % 10 < 5))
			myFont->draw(aBuffer, "CONTINUE", 136, 165);
		myFont->draw(aBuffer, "EXIT", 136, 180);
	}
	else
	{
		myFont->draw(aBuffer, "EXIT", 136, 165);
	}

	myFont->draw(aBuffer, "\" DARKBITS 2012", 100, 110);
	myFont->draw(aBuffer, "  PLAY SELECT", 100, 125);

	myFont->draw(aBuffer, "TINS IS NOT SPEEDHACK", 80, 205);
	myFont->draw(aBuffer, "COMPETITION 2012", 100, 220);
}

void Title::onLogic()
{
	myFrameCounter++;

	if (myGameStart)
	{
		if (myFrameCounter > 100)
		{
			if (myContinueSelected)
			{
				World *world = new World();
				world->respawn(true);
				ScreenManager::add(world);
			}
			else
			{
				World *world = new World();
				world->respawn(false);
				ScreenManager::add(world);

 				Intro* intro = new Intro();
 				ScreenManager::add(intro);
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

	if (Input::isPressed(Button_Fire) || Input::isPressed(Button_ToggleWeapon))
	{
		if (mySelected == 0)
		{
			myGameStart = true;
			myFrameCounter = 0;
			Music::stop();
			Sound::playSample("data/sounds/start.wav");
			GameState::clear();
			myContinueSelected = false;
		}
		if (mySelected == 1 && myContinue)
		{
			myGameStart = true;
			myFrameCounter = 0;
			Music::stop();
			Sound::playSample("data/sounds/start.wav");
			GameState::loadFromFile();
			myContinueSelected = true;
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
	Music::playSong("data/music/title.xm");

	if (GameState::isSavePresent())
		myContinue = true;
	else
		myContinue = false;
	if (myContinue)
		mySelected = 1;
}	
