#include "Precompiled.hpp"

#include "Outro.hpp"

#include "Font.hpp"
#include "Resource.hpp"
#include "Constants.hpp"
#include "Sound.hpp"
#include "Music.hpp"
#include "ScreenManager.hpp"
#include "GameState.hpp"
#include "World.hpp"
#include "End.hpp"

Outro::Outro()
	: myTextsCharecter(0)
	, myTextsIndex(0)
	, myWait(false)
{
	myFont = Resource::getFont("data/images/font.bmp");	
	myTexts.push_back(" ");
	myTexts.push_back("AFTER KILLING THE BIG DRAGON");
	myTexts.push_back("A NEW TIME PORTAL OPENS");
	myTexts.push_back("AND THE TERMINATOR DISAPPEARS");
	myTexts.push_back(" ");
	myTexts.push_back(" ");
	myTexts.push_back(" ");
	myTexts.push_back(" ");
	myTexts.push_back("BUT IS IT REALLY TO 1984?");
	myTexts.push_back("WE ARE NOT TELLING!!");
	myTexts.push_back("END..");
}

void Outro::onDraw( BITMAP* aBuffer )
{
	if (myTextsIndex == 5 && myFrameCounter < 100)
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

void Outro::onLogic()
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

			myFrameCounter = 0;

			if (myTextsIndex >= myTexts.size())
			{
				ScreenManager::exit(this);
				ScreenManager::add(new End());	
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

void Outro::onEntered()
{
	Music::playSong("data/music/title.xm");
}	

void Outro::onExited()
{

}