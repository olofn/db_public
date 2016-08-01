#include "dialogtile.hpp"

#include "room.hpp"
#include "tilemap.hpp"

DialogTile::DialogTile(int x, int y, bool solid, const std::string& stateBeforeDialog, bool atTop)
:TileAlignedEntity(Entity::OTHER,
				   x,
				   y,
				   true)
{
	mInitialized = false;
	mSolid = solid;
	mAtTop = atTop;
	mStateBeforeDialog = stateBeforeDialog;
}

void DialogTile::logic()
{
	if (!mInitialized && mSolid)
	{
		int x = (mX + mW / 2) / TileMap::TILE_SIZE;
		int y = (mY + mH / 2) / TileMap::TILE_SIZE;
		mRoom->getTileMap()->setFlags(x, y, TileMap::FLAG_SOLID);
		mInitialized = true;
	}

	std::vector<Entity*> collisions = mRoom->collidesWith(this, Entity::PLAYER, 2);
	if (collisions.size() > 0 && mRoom->getKeyState()->isActionPressed())
	{
		mRoom->addActorStateCutScene(mRoom->getPlayer(), mStateBeforeDialog);
		for (unsigned int i = 0; i < mDialogs.size(); i++)
		{
			mRoom->addDialogCutScene(mDialogs[i], mAtTop);
		}
		mRoom->startCutScenes();
	}
}

void DialogTile::drawForeground(BITMAP *dest, int scrollx, int scrolly)
{
#ifdef _DEBUG
	if (key[KEY_B])
	{
		rect(dest, mX - scrollx, mY - scrolly - 2, mX - scrollx + 16, mY - scrolly + 16, 128);
	}
#endif
}

void DialogTile::addDialog(const std::string& text)
{
	mDialogs.push_back(text);
}