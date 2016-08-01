#include "WallOfDeathStarter.hpp"

#include "Room.hpp"
#include "Hero.hpp"

WallOfDeathStarter::WallOfDeathStarter()
	: myUsed(false)
{
	setSize(float2(10, 10 * 100));
}

void WallOfDeathStarter::onRespawn()
{
	myUsed = false;
}

void WallOfDeathStarter::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	//Entity::draw(buffer, offsetX, offsetY, layer);
}

void WallOfDeathStarter::update()
{
	if (!myUsed && Collides(mRoom->getHero()->getCollisionRect(), getCollisionRect()))
	{
		mRoom->broadcastStartWallOfDeath();
		myUsed = true;
	}
}
