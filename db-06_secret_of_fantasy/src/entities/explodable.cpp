#include "entities/explodable.hpp"
#include "room.hpp"
#include "tilemap.hpp"
#include "stringutil.hpp"
#include "gamestate.hpp"
#include "game.hpp"

Explodable::Explodable(int x, int y)
:TileAlignedEntity(Entity::EXPLODABLE,x, y, true),
mAnimation("graphics/explodable.bmp")
{
    mHealth = 6; 
    mInitialized = false;
    mToBeDeleted = false;
}

void Explodable::draw(BITMAP *dest, int scrollx, int scrolly)
{
	if (mHealth  > 0)
		mAnimation.drawFrame(dest, mHealth - 1, getX() - scrollx, getY() - scrolly);
}

void Explodable::logic()
{
    if (!mInitialized)
    {
		int x = (mX + mW / 2) / TileMap::TILE_SIZE;
		int y = (mY + mH / 2) / TileMap::TILE_SIZE;
		mRoom->getTileMap()->setFlags(x, y, TileMap::FLAG_SOLID);
		mInitialized = true;
		GameState* gameState = mRoom->getGame()->getGameState();
		if(gameState->getInt(buildGameStateVariableString())==1)
		{
			mToBeDeleted = true;
			int x = (mX + mW / 2) / TileMap::TILE_SIZE;
			int y = (mY + mH / 2) / TileMap::TILE_SIZE;
			mRoom->getTileMap()->setFlags(x, y, 0);
		}
	}
}

bool Explodable::isToBeDeleted()
{
    return mToBeDeleted;
}

void Explodable::damage(int damage, Entity::Direction direction)
{
	mHealth -= damage;

	if (mHealth <= 0)
	{
		mToBeDeleted = true;
		GameState* gameState = mRoom->getGame()->getGameState();
		gameState->put(buildGameStateVariableString(), 1);
		int x = (mX + mW / 2) / TileMap::TILE_SIZE;
		int y = (mY + mH / 2) / TileMap::TILE_SIZE;
		mRoom->getTileMap()->setFlags(x, y, 0);
		mRoom->spawnSmallSmokeAtEntity(this);
	}
}
 
std::string Explodable::buildGameStateVariableString()
{
	return "explodable_" + mRoom->getDungeonName() + "_" + toString(mRoom->getDungeonLevel()) + "_" + toString(getX()) + "_" + toString(getY());
}