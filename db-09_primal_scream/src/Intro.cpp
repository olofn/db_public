#include "Precompiled.hpp"

#include "Intro.hpp"

#include "Font.hpp"
#include "Resource.hpp"
#include "Constants.hpp"
#include "Sound.hpp"
#include "Music.hpp"
#include "ScreenManager.hpp"
#include "GameState.hpp"
#include "World.hpp"

Intro::Intro()
	: myTextsCharecter(0)
	, myTextsIndex(0)
	, myWait(false)
{
	myFont = Resource::getFont("data/images/font.bmp");	
	myTexts.push_back(" ");
	myTexts.push_back("THE YEAR IS THE FUTURE");
	myTexts.push_back("ROBOTS AND HUMANS ARE AT WAR");
	myTexts.push_back("A NEW TERMINATOR MODEL");
	myTexts.push_back("IS SENT BACK IN TIME");
	myTexts.push_back("TO KILL SARAH CONNOR");
	myTexts.push_back("DESTINATION: YEAR 1984");
	myTexts.push_back("TIME TRAVEL STARTS IN");
	myTexts.push_back("3");
	myTexts.push_back("2");
	myTexts.push_back("1");
	myTexts.push_back(" ");
	myTexts.push_back(" ");
	myTexts.push_back("TIME TRAVEL COMPLETE");
	myTexts.push_back("VERIFYING YEAR");
	myTexts.push_back("YEAR IS");
	myTexts.push_back("UNKNOWN?!");
	myTexts.push_back(" ");
}

void Intro::onDraw( BITMAP* aBuffer )
{
	if (myTextsIndex == 11 && myFrameCounter < 100)
	{
		if (myFrameCounter % 5 == 0)
		{			
			clear_to_color(aBuffer, makecol(rand() % 255, rand() % 255, rand() % 255));
		}
		if (myFrameCounter % 20 == 0)
		{
			Sound::playSample("data/sounds/grenadeexplode.wav");
		}
	}
	else
	{
		clear_to_color(aBuffer, 0);

		if (myTextsIndex < myTexts.size())
		{
			myFont->drawCenter(aBuffer, myTexts[myTextsIndex], 0, 0, 320, 240, myTextsCharecter);
		}
	}
}

void Intro::onLogic()
{
	myFrameCounter++;

	if (myWait)
	{		
		if ((myTextsIndex == (myTexts.size() - 2) && myFrameCounter >= 120)
			|| (myTextsIndex != (myTexts.size() - 2) && myFrameCounter >= 60))
		{
			myWait = false;
			myTextsCharecter = 0;
			myTextsIndex++;

			if (myTextsIndex == 7 || myTextsIndex == 16)
			{
				Music::stop();
			}
			if (myTextsIndex == 12)
			{
				Music::playSong("data/music/title.xm");
			}
			if (myTextsIndex == 16)
			{
				Sound::playSample("data/sounds/unknown.wav");
			}

			myFrameCounter = 0;

			if (myTextsIndex >= myTexts.size())
			{
				ScreenManager::exit(this);
				return;
			}
		}

		return;
	}

	if (myFrameCounter % 5 == 0)
	{
		if (myTextsCharecter >= myTexts[myTextsIndex].size() - 1)
		{
			myWait = true;
			myFrameCounter = 0;
		}

		myTextsCharecter++;
	}


}

void Intro::onEntered()
{
	Music::pushSong();
	Music::playSong("data/music/title.xm");
}	

void Intro::onExited()
{
	Music::popSong();
}