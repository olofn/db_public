#include "shopkeeper.hpp"

#include "room.hpp"
#include "tilemap.hpp"

ShopKeeper::ShopKeeper(int x, int y)
:TileAlignedEntity(Entity::OTHER,
				   x,
				   y,
				   true),
mAnimation("graphics/shopkeeper.bmp", 2)
{
	mFrameCounter = 0;
	mInitialized = false;
}

ShopKeeper::~ShopKeeper()
{

}

void ShopKeeper::logic()
{
	mFrameCounter++;

	if (!mInitialized)
	{
		int x = (mX + mW / 2) / TileMap::TILE_SIZE;
		int y = (mY + mH / 2) / TileMap::TILE_SIZE;
		mRoom->getTileMap()->setFlags(x, y, TileMap::FLAG_SOLID);
		mInitialized = true;
	}

	std::vector<Entity*> collisions = mRoom->collidesWith(this, Entity::PLAYER, 2);
	if (collisions.size() > 0 && mRoom->getKeyState()->isActionPressed())
	{
		mRoom->addShopDialogCutScene();
		mRoom->startCutScenes();
	}
}

void ShopKeeper::draw(BITMAP *dest, int scrollx, int scrolly)
{
	mAnimation.drawFrame(dest, mFrameCounter % 20 < 10, mX - scrollx, mY - scrolly - 2);
}