#include "portalhome.hpp"
#include "portal.hpp"

#include "room.hpp"

PortalHome::PortalHome(int x, int y)
:TileAlignedEntity(Entity::OTHER,
				   x,
				   y,
				   true)
{
	mInitialized = false;
	mFrameCounter = 0;
}

PortalHome::~PortalHome()
{

}

void PortalHome::logic()
{
	mFrameCounter++;

	if (!mInitialized && mFrameCounter > 300)
	{
		mRoom->addEntity(new Portal(mX, mY + 16));
		mInitialized = true;
	}

	if (mFrameCounter > 300 
		&& mRoom->collidesWith(this, Entity::PLAYER).size() != 0
		&& mRoom->getPlayer()->getInventory()->getAmountForItem("MILK") == 1)
	{
		mRoom->addZoomCutScene(true);
		mRoom->addChangeRoomCutScene("realworld.txt", 2,true, 0, 0);
		mRoom->startCutScenes();
	}
}