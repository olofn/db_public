#include "Precompiled.hpp"

#include "World.hpp"

#include "Room.hpp"
#include "RoomLoader.hpp"
#include "Hero.hpp"
#include "GameState.hpp"
#include "ScreenManager.hpp"
#include "Outro.hpp"
#include "Input.hpp"
#include "Resource.hpp"
#include "Font.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "Portal.hpp"

World::World()
	: myCurrentRoom(0)
	, pendingRoomLoad(false)
	, ended(false)
	, myExit(false)
	, mySelected(0)
	, myFirstHeroSpawn(true)
{
	myFont = Resource::getFont("data/images/font.bmp");	
	myHand = Resource::getAnimation("data/images/hand2.bmp", 1);
	myFade = Resource::getAnimation("data/images/fade.bmp", 7);
}

World::~World()
{
	delete myCurrentRoom;
}

void World::respawn(bool useSaveFile)
{
	myFirstHeroSpawn = !useSaveFile;

	if (myCurrentRoom)
	{
		delete myCurrentRoom;
		myCurrentRoom = 0;
	}

	// For new game
	GameState::put(GameState::LOCATION_X, 160);
	GameState::put(GameState::LOCATION_Y, 790);
	GameState::put(GameState::POWERUP_GRENADE, 0);
	GameState::put(GameState::POWERUP_GUN, 0);
	GameState::put(GameState::POWERUP_HIJUMP, 0);

	// For continue
	if (useSaveFile && GameState::isSavePresent())
	{
		GameState::loadFromFile();
	}

	GameState::saveToFile();
	
	roomLoadWorldPos.x = GameState::getInt(GameState::LOCATION_X);
	roomLoadWorldPos.y = GameState::getInt(GameState::LOCATION_Y);
	pendingRoomLoad = true;
}

void World::doLoadRoom()
{
	Hero *hero = 0;

	if (myCurrentRoom)
	{
		hero = myCurrentRoom->getHero();
		myCurrentRoom->removeHero();
		delete myCurrentRoom;
		myCurrentRoom = 0;
	}

	int tileX = (int)(roomLoadWorldPos.x / 10);
	int tileY = (int)(roomLoadWorldPos.y / 10);
	myCurrentRoom = RoomLoader::LoadRoom(tileX, tileY);
	myCurrentRoom->setWorld(this);

	Hero *doppelganger = myCurrentRoom->getHero();
	if (doppelganger)
	{
		myCurrentRoom->removeHero();
		delete doppelganger;
	}

	if (!hero)
	{
		hero = new Hero();
		hero->setSpawnPortal(myFirstHeroSpawn);
		myFirstHeroSpawn = false;
	}

	hero->setPosition(float2(roomLoadWorldPos.x - myCurrentRoom->getWorldOffsetX() * myCurrentRoom->getTileWidth(), roomLoadWorldPos.y - myCurrentRoom->getWorldOffsetY() * myCurrentRoom->getTileHeight()));
	
	myCurrentRoom->addEntity(hero);
}

void World::loadRoom(float2 worldPos)
{
	pendingRoomLoad = true;
	roomLoadWorldPos = worldPos;
}

void World::onDraw(BITMAP* aBuffer)
{
	if (myExit)
	{
		onExitDraw(aBuffer);
	}
	else
	{
		onNormalDraw(aBuffer);
	}
	
}

void World::onLogic()
{
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

	if (myExit)
	{
		onExitLogic();
	}
	else
	{
		onNormalLogic();
	}
}

void World::endGame()
{
	ended = true;
}

void World::onNormalLogic()
{
	if (pendingRoomLoad)
	{
		doLoadRoom();
		pendingRoomLoad = false;
	}

	if (myCurrentRoom)
	{
		myCurrentRoom->onLogic();
	}

	if (ended)
	{
		this->exit();
		ScreenManager::add(new Outro());
	}
}

void World::onExitLogic()
{
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

void World::onNormalDraw( BITMAP* aBuffer )
{
	if (myCurrentRoom)
	{
		myCurrentRoom->onDraw(aBuffer);
	}
}

void World::onExitDraw( BITMAP* aBuffer )
{
	if (myCurrentRoom)
	{
		myCurrentRoom->onDraw(aBuffer);
	}

	for (int y = 0; y < 240; y += 16)
	{
		for (int x = 0; x < 320; x+= 16)
		{
			myFade->drawFrame(aBuffer, 2, x, y);
		}
	}

	rectfill(aBuffer, 60, 100, 260, 140, 0);
	rect(aBuffer, 60, 100, 260, 140, 0xffffff);
	rect(aBuffer, 62, 102, 260 - 2, 140 - 2, 0xffffff);

	//rectfill(aBuffer, 110, 100, 220, 140, 0);
	myFont->draw(aBuffer, "CONTINUE", 125, 110);
	myFont->draw(aBuffer, "EXIT LEVEL", 125, 125);
	myHand->drawFrame(aBuffer, 0, 115, 110 + mySelected * 15);
}