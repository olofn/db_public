#include "chest.hpp"
#include "room.hpp"
#include "tilemap.hpp"
#include "item.hpp"
#include "gamestate.hpp"
#include "stringutil.hpp"
#include "game.hpp"

#include "items/bomb.hpp"

Chest::Chest(int x, int y, Item* item, bool dropped)
:TileAlignedEntity(Entity::OTHER, x, y, true),
mAnimation("graphics/chest.bmp", 2), mItem(item),
mDropped(dropped)
{
	mInitialized = false;
	mOpen = false;
	mOpenFrameCount = 0;
	mUsed = false;
}

void Chest::logic()
{
	if (!mInitialized)
	{
		mInitialized = true;

		if (!mDropped)
		{
			GameState* gameState = mRoom->getGame()->getGameState();
			if(gameState->getInt(buildGameStateVariableString()) == 1)
			{
				mUsed = true;
				setSolid(false);
				return;
			}
		}

		setSolid(true);
	}

	if (mOpen)
	{
		mOpenFrameCount++;
		return;
	}

	std::vector<Entity*> collisions = mRoom->collidesWith(this, Entity::PLAYER, 2);
	if (collisions.size() > 0 && mRoom->getKeyState()->isActionPressed())
	{
		mOpen = true;
		setSolid(false);
		mRoom->freeze(100);
		mRoom->addTextCutScene("Received " + mItem->getName(), 100);
		mRoom->startCutScenes();
		
		if (!mDropped)
		{
			GameState* gameState = mRoom->getGame()->getGameState();
			gameState->put(buildGameStateVariableString(), 1);
		}

		mRoom->getPlayer()->getInventory()->add(mItem);
		mItem = 0;
	}
}

std::string Chest::buildGameStateVariableString()
{
	return "chest_" + mRoom->getDungeonName() + "_" + toString(mRoom->getDungeonLevel()) + "_" + toString(getX()) + "_" + toString(getY());
}

Chest::~Chest()
{
	if(mItem != 0)
	{
		delete(mItem);
	}
}
Item* Chest::getItem()
{
	return mItem;
}

void Chest::draw(BITMAP *dest, int scrollx, int scrolly)
{
	if (!mOpen || mOpenFrameCount % 4 < 2)
	{
		mAnimation.drawFrame(dest, mOpen, mX - scrollx, mY - scrolly);
	}
}

bool Chest::isToBeDeleted()
{
	return mOpen && mOpenFrameCount >= NO_FRAMES_TO_BE_OPEN || mUsed;
}

void Chest::setSolid(bool solid)
{
	int x = (mX + mW / 2) / TileMap::TILE_SIZE;
	int y = (mY + mH / 2) / TileMap::TILE_SIZE;
	
	mRoom->getTileMap()->setFlags(x, y, (solid? TileMap::FLAG_SOLID : 0));
}