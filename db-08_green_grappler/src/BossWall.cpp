#include "BossWall.hpp"

#include "Room.hpp"
#include "BossSaw.hpp"
#include "Animation.hpp"
#include "Resource.hpp"
#include "Hero.hpp"

BossWall::BossWall(Direction aDirection)
: myDirection(aDirection)
, myActive(false)
{
	setSize(float2(10, 100));
	myWall = Resource::getAnimation("data/images/wall.bmp", 1);
}

void BossWall::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	int x = getDrawPositionX() + offsetX - getHalfSize().x;
	int y = getDrawPositionY() + offsetY - getHalfSize().y;

	myWall->drawFrame(buffer, 0, x, y, myDirection == Direction_Left);
	//Entity::draw(buffer, offsetX, offsetY, layer);
}

void BossWall::update()
{
	myFrameCounter++;

	if (Collides(mRoom->getHero()->getCollisionRect(), getCollisionRect()))
	{
		mRoom->getHero()->kill();
	}

	if (!myActive)
		return;

	if (myDirection == Direction_Right && myFrameCounter % 200 == 0)
	{
		BossSaw* saw = new BossSaw(myDirection);
		saw->setPosition(float2(getPosition().x, getPosition().y + getHalfSize().y - 10));
		mRoom->addEntity(saw);
	}

	if (myDirection == Direction_Right && (100 + myFrameCounter) % 200 == 0)
	{
		BossSaw* saw = new BossSaw(myDirection);
		saw->setPosition(float2(getPosition().x, getPosition().y + getHalfSize().y - 30));
		mRoom->addEntity(saw);
	}

	if (myDirection == Direction_Right && (180 + myFrameCounter) % 200 == 0)
	{
		BossSaw* saw = new BossSaw(myDirection);
		saw->setPosition(float2(getPosition().x, getPosition().y  + getHalfSize().y - 50));
		mRoom->addEntity(saw);
	}

	if (myDirection == Direction_Left && myFrameCounter % 350 == 0)
	{
		BossSaw* saw = new BossSaw(myDirection);
		saw->setPosition(float2(getPosition().x, getPosition().y + getHalfSize().y - 10));
		mRoom->addEntity(saw);
	}

	if (myDirection == Direction_Left && (100 + myFrameCounter) % 350 == 0)
	{
		BossSaw* saw = new BossSaw(myDirection);
		saw->setPosition(float2(getPosition().x, getPosition().y + getHalfSize().y - 30));
		mRoom->addEntity(saw);
	}

	if (myDirection == Direction_Left && (300 + myFrameCounter) % 350 == 0)
	{
		BossSaw* saw = new BossSaw(myDirection);
		saw->setPosition(float2(getPosition().x, getPosition().y + getHalfSize().y - 50));
		mRoom->addEntity(saw);
	}

}

int BossWall::getLayer()
{
	return 3;
}

void 
BossWall::setTilesCollidable( 
	bool aCollidable )
{
	int sx = (getPosition().x-getHalfSize().x)/10;
	int sy = (getPosition().y-getHalfSize().y)/10;
	int height = (getSize().y) / 10;

	for (int y = sy; y < sy + height; y++)
		mRoom->setCollidable(sx, y, aCollidable);
}

void BossWall::setRoom( Room *room )
{
	Entity::setRoom(room);
	setTilesCollidable(true);
}

void BossWall::onBossWallActivate()
{
	myActive = true;
	myFrameCounter = 0;
}

void BossWall::onRespawn()
{
	myActive = false;
}

void BossWall::onBossWallDeactivate()
{
	myActive = false;
}

