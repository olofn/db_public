#include "Door.hpp"

#include "Animation.hpp"
#include "Resource.hpp"

#include "Room.hpp"

Door::Door(int aId)
: myId(aId)
, myOpening(false)
, myClosing(false)
, myInited(false)
, myDoorHeight(40)
{
	setSize(float2(10, 40));
	myDoor = Resource::getBitmap("data/images/door.bmp");
}

void Door::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	int x = getDrawPositionX() + offsetX - getSize().x / 2;
	int y = getDrawPositionY() + offsetY - getSize().y / 2;

	masked_blit(myDoor, buffer, 0, 0, x, y, 10, myDoorHeight);

	//Entity::draw(buffer, offsetX, offsetY, layer);
}

void Door::update()
{

	myFrameCounter++;

	if (myOpening && myDoorHeight != 4)
	{
		myDoorHeight-=2;
	}
	else if (myOpening)
	{
		myFrameCounter = 0;
		myClosing;
	}

	if (myClosing && myFrameCounter % 5 == 0 &&  myDoorHeight != 40)
	{
		myDoorHeight++;
	}

	int tileX = (int)(getPosition().x - getSize().x / 2) / 10;
	int tileY = (int)(getPosition().y - getSize().y / 2) / 10;

	for (int i = 0; i < 4; i++)
	{
		if (i > myDoorHeight / 10)
		{
			mRoom->setCollidable(tileX, tileY + i, false);
		}
		else
		{
			mRoom->setCollidable(tileX, tileY + i, true);
		}
	}
}

void Door::onButtonDown( int aId )
{
	if (myId != aId)
		return;

	myFrameCounter = 0;
	myOpening = true;
	myClosing = false;
}

void Door::onButtonUp( int aId )
{
	if (myId != aId)
		return;

	myClosing = true;
	myOpening = false;
	myFrameCounter = 0;
}

void Door::onRespawn()
{
	myOpening = false;
	myClosing = false;
	myInited = false;
	myDoorHeight = 40;
}
