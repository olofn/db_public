#include "End.hpp"
#include "Resource.hpp"
#include "Font.hpp"
#include "Music.hpp"
#include "Input.hpp"
#include "Constants.hpp"
#include "Sound.hpp"

#define GREEN_PEACE_DURATION 60 * 7
End::End()
: myFrameCounter(-60)
, myCreditsOffset(240)
{
	myFont = Resource::getFont("data/images/font.bmp");
}

void End::onDraw( BITMAP* aBuffer )
{
	rectfill(aBuffer, 0, 0, 320, 240, makecol(57,56,41));

	if (myFrameCounter < 0)
		return;

	if (myFrameCounter < GREEN_PEACE_DURATION)
	{
		myFont->draw(aBuffer, "THE LAST REACTOR IS IN CAPTIVITY", 50, 110);
		myFont->draw(aBuffer, "THE GALAXY IS AT GREEN PEACE", 60, 120);
	}
	else
	{
		myFont->draw(aBuffer, "CREDITS", 50, myCreditsOffset);
		myFont->draw(aBuffer, "PROGRAMMING", 50, 30 + myCreditsOffset);
		myFont->draw(aBuffer, "   OLOF NAESSEN", 50, 40 + myCreditsOffset);
		myFont->draw(aBuffer, "   PER LARSSON", 50, 50 + myCreditsOffset);
		myFont->draw(aBuffer, "   ALEXANDER SCHRAB ", 50, 60 + myCreditsOffset);

		myFont->draw(aBuffer, "GRAPHICS", 50, 90 + myCreditsOffset);
		myFont->draw(aBuffer, "   OLOF NAESSEN", 50, 100 + myCreditsOffset);
		myFont->draw(aBuffer, "   TIMUR KONDRAKOV", 50, 110 + myCreditsOffset);
		myFont->draw(aBuffer, "   PER LARSSON", 50, 120 + myCreditsOffset);

		myFont->draw(aBuffer, "MUSIC", 50, 150 + myCreditsOffset);
		myFont->draw(aBuffer, "   OLOF NAESSEN", 50, 160 + myCreditsOffset);

		myFont->draw(aBuffer, "VOICE ACTING", 50, 190 + myCreditsOffset);
		myFont->draw(aBuffer, "   PER LARSSON", 50, 200 + myCreditsOffset);

		myFont->draw(aBuffer, "NOT SHOWING UP FOR THE COMPO", 50, 230 + myCreditsOffset);
		myFont->draw(aBuffer, "   TED STEEN", 50, 240 + myCreditsOffset);

		myFont->draw(aBuffer, "THIS GAME WAS DONE", 50, 270 + myCreditsOffset);
		myFont->draw(aBuffer, "FOR THE SPEEDHACK 11", 50, 280 + myCreditsOffset);
		myFont->draw(aBuffer, "COMPETITION", 50, 290 + myCreditsOffset);
		myFont->draw(aBuffer, "THANK YOU ALLEGRO.CC", 50, 300 + myCreditsOffset);
		myFont->draw(aBuffer, "FOR A GREAT COMPETITION!", 50, 310 + myCreditsOffset);

		myFont->draw(aBuffer, "THANK YOU THORBJORN LINDEIJER", 50, 340 + myCreditsOffset);
		myFont->draw(aBuffer, "FOR THE TILED EDITOR!", 50, 350 + myCreditsOffset);

		myFont->draw(aBuffer, "THANK YOU ANDERS STENBERG", 50, 380 + myCreditsOffset);
		myFont->draw(aBuffer, "FOR YOUR TILE RAYCASTING ALGORITHM!", 50, 390 + myCreditsOffset);

		myFont->draw(aBuffer, "AND THANKS FOR PLAYING", 50, 420 + myCreditsOffset);
		myFont->draw(aBuffer, "OUR GAME!", 50, 430 + myCreditsOffset);

		if (myCreditsOffset < -450)
		{
			myFont->drawCenter(aBuffer, "THE END", 0, 0, 320, 240);
		}
	}
}

void End::onLogic()
{
	myFrameCounter++;

	if (myFrameCounter == 0)
	{
		Sound::playSample("data/sounds/green_peace.wav");
	}
	if (myFrameCounter == GREEN_PEACE_DURATION)
	{
		Music::playSong("data/music/intro2.xm");
	}
	else if (myFrameCounter > GREEN_PEACE_DURATION && myFrameCounter % 4 == 0)
	{
		myCreditsOffset--;
	}
	
	if (Input::isPressed(Button_Exit))
		exit();
	
}
