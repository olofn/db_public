#include "Button.hpp"

#include "Animation.hpp"
#include "Resource.hpp"
#include "Room.hpp"
#include "Hero.hpp"
#include "Sound.hpp"

Button::Button(int aId)
: mCollisionThisFrame(false)
, mTriggered(false)
, myTime(60 * 5)
, myCounter(myTime + 1)
, myId(aId)
{
	myButton = Resource::getAnimation("data/images/button.bmp");
	setSize(float2(10, 10));
}

void Button::update()
{
	myCounter++;

	if (myCounter == myTime)
	{
		Sound::playSample("data/sounds/timeout.wav");
		mRoom->broadcastButtonUp(myId);
		return;
	}

	if (myCounter < myTime)
	{	
		if (myCounter % 60 == 0)
			Sound::playSample("data/sounds/time.wav");
		return;
	}

	if (Entity::Collides(mRoom->getHero()->getCollisionRect(), getCollisionRect()))
	{
		mCollisionThisFrame = true;		
		if (!mTriggered)
		{
			mTriggered = true;
			myCounter = 0;
			Sound::playSample("data/sounds/time.wav");
			mRoom->broadcastButtonDown(myId);
		}
	}
	else
	{
		mCollisionThisFrame = false;
		mTriggered = false;
	}
}

void Button::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	int x = getDrawPositionX() + offsetX;
	int y = getDrawPositionY() + offsetY;

	int frame = 1;
	if (myCounter > myTime)
	{
		frame = 0;
	}
	myButton->drawFrame(buffer, frame, x - (int)getSize().x / 2, y - (int)getSize().y / 2);

	//Entity::draw(buffer, offsetX, offsetY, layer);
}

void Button::onRespawn()
{
	mCollisionThisFrame = false;
	mTriggered = false;
	myCounter = myTime + 1;
}
