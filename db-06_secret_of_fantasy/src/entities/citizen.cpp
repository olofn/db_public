#include "citizen.hpp"

#include "room.hpp"
#include "tilemap.hpp"

Citizen::Citizen(int x, int y, bool dialogAtTop)
:TileAlignedEntity(Entity::OTHER,
				   x,
				   y,
				   true),
mAnimation("graphics/citizen.bmp", 2)
{
	mFrameCounter = 0;
	mInitialized = false;
	mDialogAtTop = dialogAtTop;
}

Citizen::~Citizen()
{

}

void Citizen::logic()
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
		for (unsigned int i = 0; i < mDialogs.size(); i++)
		{
			mRoom->addDialogCutScene(mDialogs[i], mDialogAtTop);
		}
		mRoom->startCutScenes();
	}
}

void Citizen::draw(BITMAP *dest, int scrollx, int scrolly)
{
	mAnimation.drawFrame(dest, mFrameCounter % 20 < 10, mX - scrollx, mY - scrolly - 2);
}

void Citizen::addDialog(const std::string& text)
{
	mDialogs.push_back(text);
}