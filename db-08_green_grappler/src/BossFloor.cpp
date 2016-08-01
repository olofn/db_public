#include "BossFloor.hpp"
#include "Room.hpp"
#include "Hero.hpp"

#include <iostream>

BossFloor::BossFloor()
:myActive(false)
{
	setSize(float2(320, 10));
}

void BossFloor::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	//Entity::draw(buffer, offsetX, offsetY, layer);
}

void BossFloor::update()
{
	myFrameCounter++;

	if (!myActive)
		return;

	if (Collides(mRoom->getHero()->getCollisionRect(), getCollisionRect()))
	{
		mRoom->getHero()->kill();
	}

	if (myFrameCounter > 60)
		myActive = false;
}

int BossFloor::getLayer()
{
	return 4;
}

Entity::CollisionRect BossFloor::getCollisionRect()
{
	Entity::CollisionRect rect = Entity::getCollisionRect();
	rect.myTopLeft.y--;
	return rect;
}

void BossFloor::onBossFloorActivate()
{
	myActive = true;
	myFrameCounter = 0;
}

void BossFloor::onRespawn()
{	
	myActive = false;
}
