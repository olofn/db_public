#include "LevelSelect.hpp"

#include "Font.hpp"
#include "Resource.hpp"
#include "Animation.hpp"
#include "Util.hpp"
#include "Input.hpp"
#include "Constants.hpp"
#include "Sound.hpp"
#include "Music.hpp"
#include "ScreenManager.hpp"
#include "Level.hpp"
#include "GameState.hpp"
#include "End.hpp"
#include "Dialogue.hpp"

bool LevelSelect::myBossLevelCompleted = false;

LevelSelect::LevelSelect()
: mySelectedX(0)
, mySelectedY(0)
, myFrameCounter(0)
, myLevelSelected(false)
, myPlayingBossLevel(false)
, myBossLevelUnlocked(false)
, myRunFirstDialogue(false)
, myRunBossUnlockedDialogue(false)
{
	myFont = Resource::getFont("data/images/font.bmp");
	myBackground = Resource::getAnimation("data/images/level_select.bmp", 1);
	mySelectedLevelBackground = Resource::getAnimation("data/images/selected_level_background.bmp", 6);
	myUnselectedLevelBackground = Resource::getAnimation("data/images/unselected_level_background.bmp", 1);
	myIcons = Resource::getAnimation("data/images/icons.bmp", 9);
	myCompletedIconBackground = Resource::getAnimation("data/images/completed_level.bmp", 1);

	for (int i = 0; i < 200; i++)
	{
		myParticles.push_back(Particle(frand() * 320, frand()* 240, frand()* 3 + 1));
	}

	PrivSetLevelDesc(0, 0, LevelDesc("GRAPPLIN' HEAVEN", "data/rooms/olof2.tmx", 0, "data/music/olof9.xm"));
	PrivSetLevelDesc(1, 0, LevelDesc("CAVERNOUS", "data/rooms/per4.tmx", 1, "data/music/olof8.xm"));
	PrivSetLevelDesc(2, 0, LevelDesc("HARRY U.P.", "data/rooms/level1.tmx", 7, "data/music/olof2-rmx.xm"));
	PrivSetLevelDesc(0, 1, LevelDesc("GLIDER", "data/rooms/per1.tmx", 3, "data/music/olof12.xm"));
	PrivSetLevelDesc(1, 1, LevelDesc("FINAL CORE", "data/rooms/olof.tmx", 5, "data/music/spooky.xm"));
	PrivSetLevelDesc(2, 1, LevelDesc("UNSTABLE", "data/rooms/breaktilelevel.tmx", 4, "data/music/olof8.xm"));
	PrivSetLevelDesc(0, 2, LevelDesc("THE TOWER", "data/rooms/per2.tmx", 2, "data/music/olof12.xm"));
	PrivSetLevelDesc(1, 2, LevelDesc("WALL OF DEATH", "data/rooms/per3.tmx", 6, "data/music/olof2-rmx.xm"));
	PrivSetLevelDesc(2, 2, LevelDesc("LAVA LAND", "data/rooms/levellava.tmx", 8, "data/music/olof2-rmx.xm"));

	myFirstDialogue = new Dialogue("data/dialogues/level_select.txt");
	myFirstDialogue->setRunWithoutHero();

	myBossUnlockedDialogue = new Dialogue("data/dialogues/boss_unlocked.txt");
	myBossUnlockedDialogue->setRunWithoutHero();
}

void LevelSelect::onEntered()
{
	GameState::saveToFile();

	myBossLevelUnlocked = true;
	for (unsigned int i = 0; i < 9; i++)
	{
		if (i == 4)
			continue;
	
		LevelDesc bossLevel = myLevelDescs[i];	
		if (GameState::getInt(bossLevel.myLevelFile) == 0)
		{
			myBossLevelUnlocked = false;
			break;
		}
	}

	LevelDesc bossLevel = myLevelDescs[4];
	if (GameState::getInt(bossLevel.myLevelFile) == 1
		&& myPlayingBossLevel
		&& myBossLevelCompleted)
	{	
		myBossLevelCompleted = false;
		myPlayingBossLevel = false;
		ScreenManager::add(new End());
		return;
	}

	myLevelSelected = false;
	myLevelSelectedCounter = 0;
	Music::playSong("data/music/level_select.xm");

	if (GameState::getInt("level_select_dialogue") == 0)
	{
		myRunFirstDialogue = true;
		GameState::put("level_select_dialogue", 1);
	}

	if (myBossLevelUnlocked && GameState::getInt("level_boss_unlocked_dialogue") == 0)
	{
		myRunBossUnlockedDialogue = true;
		GameState::put("level_boss_unlocked_dialogue", 1);
	}
}

void LevelSelect::onDraw( BITMAP* aBuffer )
{
	rectfill(aBuffer, 0, 0, 320, 240, makecol(57,56,41));

	for (unsigned int i = 0; i < myParticles.size(); i++)
	{
		int color = makecol(181,166,107);
		if (myParticles[i].z <= 2)
			color = makecol(123,113,99);
		line(aBuffer, myParticles[i].x, myParticles[i].y,  myParticles[i].x + 2, myParticles[i].y, color);
	}

	if (!myLevelSelected)
		myBackground->drawFrame(aBuffer, 0, 0, 0);

	if (myLevelSelected && myLevelSelectedCounter % 6 < 3 && myLevelSelectedCounter < 20)
	{
		rectfill(aBuffer, 0, 0, 320, 240, makecol(231,215,156));
	}
	
	if (myLevelSelected && myLevelSelectedCounter < 10)
		return;


	if (!myLevelSelected)
	{
		myFont->drawCenter(aBuffer, "SELECT LEVEL", 0, 30, 320, 20);
	}

	for (unsigned int i = 0; i < 9; i++)
	{
		int x = i % 3;
		int y = i / 3;

		int index = mySelectedY * 3 + mySelectedX;
		LevelDesc levelDesc = myLevelDescs[i];

		Animation* animation;
		if (mySelectedX == x && mySelectedY == y)
			animation = mySelectedLevelBackground;
		else
			animation = myUnselectedLevelBackground;

		int xPos = (x - 1) * (animation->getFrameWidth() + 5) - animation->getFrameWidth() / 2;
		int yPos = (y - 1) * (animation->getFrameHeight() + 5) - animation->getFrameHeight() / 2;
		animation->drawFrame(aBuffer, myFrameCounter / 3, 160 + xPos , 120 + yPos);
		
		if ((!myLevelSelected || index == i))
		{
			if (i == 4 && myBossLevelUnlocked || i != 4)
				myIcons->drawFrame(aBuffer, levelDesc.myFrameIndex, 164 + xPos , 124 + yPos);
		}
		if (!myLevelSelected && GameState::getInt(levelDesc.myLevelFile) == 1)
		{
			myCompletedIconBackground->drawFrame(aBuffer, 0, 164 + xPos , 124 + yPos);
		}

	}

	if (!myLevelSelected)
	{
		int index = mySelectedY * 3 + mySelectedX;
		LevelDesc levelDesc = myLevelDescs[index];
		myFont->draw(aBuffer, levelDesc.myName, 220, 68);
		
		if (GameState::getInt(levelDesc.myLevelFile) == 1)
		{
			myFont->draw(aBuffer, "STATUS:", 220, 88);
			myFont->draw(aBuffer, "   CLEARED", 220, 98);
		}
		else if (index == 4 && !myBossLevelUnlocked)
		{
			myFont->draw(aBuffer, "STATUS:", 220, 88);
			myFont->draw(aBuffer, "   LOCKED", 220, 98);
		}
		else
		{
			myFont->draw(aBuffer, "STATUS:", 220, 88);
			myFont->draw(aBuffer, "   RADIOACTIVE", 220, 98);
		}
	}

	if (myRunFirstDialogue)
		myFirstDialogue->draw(aBuffer, 0, 0, 0);

	if (myRunBossUnlockedDialogue)
		myBossUnlockedDialogue->draw(aBuffer, 0, 0, 0);
}

void LevelSelect::onLogic()
{
	myFrameCounter++;
	for (unsigned int i = 0; i < myParticles.size(); i++)
	{
		myParticles[i].x -= myParticles[i].z / 2.0f;

		if (myParticles[i].x < 0)
		{
			myParticles[i].x = 320;
			myParticles[i].y = frand()* 240;
			myParticles[i].z = frand()* 3 + 1;
		}
	}

	if (myLevelSelected)
	{
		myLevelSelectedCounter++;
		if (myLevelSelectedCounter > 100)
		{
			int index = mySelectedY * 3 + mySelectedX;
			myPlayingBossLevel = index == 4;
			LevelDesc levelDesc = myLevelDescs[index];
			ScreenManager::add(new Level(levelDesc));
		}
		return;
	}

	if (Input::isPressed(Button_Exit))
	{
		exit();
		Sound::playSample("data/sounds/select.wav");		
	}

	if (Input::isPressed(Button_Left))
	{
		mySelectedX--;
		if (mySelectedX < 0)
			mySelectedX = 0;
		else
			Sound::playSample("data/sounds/select.wav");		
	}

	if (Input::isPressed(Button_Right))
	{
		mySelectedX++;
		if (mySelectedX > 2)
			mySelectedX = 2;
		else
			Sound::playSample("data/sounds/select.wav");		
	}

	if (Input::isPressed(Button_Up))
	{
		mySelectedY--;
		if (mySelectedY < 0)
			mySelectedY = 0;
		else
			Sound::playSample("data/sounds/select.wav");		
	}

	if (Input::isPressed(Button_Down))
	{
		mySelectedY++;
		if (mySelectedY > 2)
			mySelectedY = 2;
		else
			Sound::playSample("data/sounds/select.wav");		
	}

	if (Input::isPressed(Button_Fire))
	{
		int index = mySelectedY * 3 + mySelectedX;
		if (index == 4 && myBossLevelUnlocked || index != 4)
		{
			Music::stop();
			Sound::playSample("data/sounds/start.wav");
			myLevelSelected = true;
			myLevelSelectedCounter = 0;
		}
	}

	if (myRunFirstDialogue)
		myFirstDialogue->update();

	if (myRunBossUnlockedDialogue)
		myBossUnlockedDialogue->update();
}

void 
LevelSelect::PrivSetLevelDesc( int aX, int aY, LevelDesc aLevelDesc )
{
	int index = aY * 3 + aX;
	myLevelDescs[index] = aLevelDesc;
}

void LevelSelect::onExited()
{
	GameState::saveToFile();
}

LevelSelect::~LevelSelect()
{
	delete myFirstDialogue;
}
