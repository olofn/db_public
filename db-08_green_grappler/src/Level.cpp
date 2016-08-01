#include "Level.hpp"

#include "RoomLoader.hpp"
#include "Resource.hpp"
#include "Animation.hpp"
#include "Input.hpp"
#include "Constants.hpp"
#include "Font.hpp"
#include "Sound.hpp"
#include "Util.hpp"
#include "GameState.hpp"
#include "Music.hpp"
#include "PlayerSkill.hpp"
#include "LevelSelect.hpp"

Level::Level(const LevelDesc& aLevelDesc)
: myLevelDesc(aLevelDesc) 
, myExit(false)
, mySelected(0)
{
	myRoom = RoomLoader::LoadRoom(myLevelDesc.myLevelFile);
	myDarken = Resource::getAnimation("data/images/darken.bmp");
	myFont = Resource::getFont("data/images/font.bmp");
	myHand = Resource::getAnimation("data/images/hand.bmp", 1);
	myExitBackground = Resource::getAnimation("data/images/level_exit_background.bmp", 1);
	Music::playSong(myLevelDesc.myMusicFile);
}

void Level::onDraw( BITMAP* aBuffer )
{
	rectfill(aBuffer, 0, 0, 320, 240, makecol(57,56,41));

	myRoom->onDraw(aBuffer);

	std::string coinsString = std::string("[x") + toString(GameState::getInt("coins"));

	rectfill(aBuffer, 0, 0, 320, 10, makecol(57, 56, 41));
	myFont->draw(aBuffer, coinsString, 1, 1);

	if (myExit)
	{
		for (int y = 0; y < 15; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				myDarken->drawFrame(aBuffer, 0, x * 16, y * 16);
			}
		}
	}

	if (myExit)
	{
		myExitBackground->drawFrame(aBuffer, 0, 160 - myExitBackground->getFrameWidth() / 2, 120 - myExitBackground->getFrameHeight() / 2);
		myFont->draw(aBuffer, "CONTINUE", 130, 110);
		myFont->draw(aBuffer, "EXIT LEVEL", 130, 120);
		myHand->drawFrame(aBuffer, 0, 120, 110 + mySelected * 10);
	}
}

void Level::onLogic()
{
	/*if (Input::isPressed(Button_Up)) {
		PlayerSkill::playerDidSomethingClever(1.0f, 0.1f);
	}

	if (Input::isPressed(Button_Down)) {
		PlayerSkill::playerDidSomethingStupid(0.0f, 0.1f);
	}*/

	if (myRoom->isCompleted())
	{
		if (myLevelDesc.myLevelFile == "data/rooms/olof.tmx")
			LevelSelect::myBossLevelCompleted = true;

		GameState::put(myLevelDesc.myLevelFile, 1);
		exit();
	}

	if (!myExit)
		myRoom->onLogic();

	if (Input::isPressed(Button_Exit) && !myExit)
	{
		Sound::playSample("data/sounds/select.wav");
		myExit = true;
	}
	else if (Input::isPressed(Button_Exit) && myExit)
	{
		Sound::playSample("data/sounds/select.wav");
		myExit = false;
	}

	if (!myExit)
		return;

	if (Input::isPressed(Button_Down))
	{
		mySelected++;
		if (mySelected > 1)
			mySelected = 1;
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
		Sound::playSample("data/sounds/select.wav");
		if (mySelected == 0)
		{
			myExit = false;
		}
		else if (mySelected == 1)
		{
			exit();
		}
	}

}

