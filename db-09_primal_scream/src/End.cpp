#include "Precompiled.hpp"
#include "End.hpp"
#include "Resource.hpp"
#include "Font.hpp"
#include "Music.hpp"
#include "Input.hpp"
#include "Constants.hpp"
#include "Sound.hpp"

End::End()
: myFrameCounter(0)
, myCreditsOffset(240)
, myPlayEnd(false)
{
	myFont = Resource::getFont("data/images/font.bmp");
}

void End::onDraw( BITMAP* aBuffer )
{
	rectfill(aBuffer, 0, 0, 320, 240, 0);

	if (myFrameCounter < 0)
		return;

	myFont->draw(aBuffer, "CREDITS", 40, myCreditsOffset);
	myFont->draw(aBuffer, "PROGRAMMING AND GRAPHICS", 40, 30 + myCreditsOffset);
	myFont->draw(aBuffer, "   PER SVANBERG", 40, 40 + myCreditsOffset);
	myFont->draw(aBuffer, "   DANIEL JOHANSSON", 40, 50 + myCreditsOffset);
	myFont->draw(aBuffer, "   OLOF NAESSEN", 40, 60 + myCreditsOffset);

	myFont->draw(aBuffer, "MUSIC", 40, 90 + myCreditsOffset);
	myFont->draw(aBuffer, "   PER SVANBERG", 40, 100 + myCreditsOffset);
	myFont->draw(aBuffer, "   OLOF NAESSEN", 40, 110 + myCreditsOffset);

	myFont->draw(aBuffer, "THIS GAME WAS CREATED IN 72 HOURS", 40, 140 + myCreditsOffset);
	myFont->draw(aBuffer, "FOR THE TINS 12 COMPETITION", 40, 150 + myCreditsOffset);
	
	myFont->draw(aBuffer, "THANK YOU AMARILLION", 40, 170 + myCreditsOffset);
	myFont->draw(aBuffer, "FOR A GREAT COMPETITION!", 40, 180 + myCreditsOffset);

	myFont->draw(aBuffer, "THANK YOU THORBJORN LINDEIJER", 40, 210 + myCreditsOffset);
	myFont->draw(aBuffer, "FOR THE TILED EDITOR!", 40, 220 + myCreditsOffset);

	myFont->draw(aBuffer, "AND THANKS FOR PLAYING", 40, 250 + myCreditsOffset);
	myFont->draw(aBuffer, "OUR GAME!", 40, 260 + myCreditsOffset);

	if (myCreditsOffset < -280)
	{
		
		myFont->drawCenter(aBuffer, "GAME OVER", 0, 0, 320, 240);
	}

}

void End::onLogic()
{
	myFrameCounter++;

	if (myFrameCounter % 4 == 0)
	{
		myCreditsOffset--;
	}
	
	if (Input::isPressed(Button_Exit))
		exit();
	
}

void End::onEntered()
{
	Music::playSong("data/music/title.xm");
}