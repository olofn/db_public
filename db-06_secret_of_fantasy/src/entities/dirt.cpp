#include "dirt.hpp"
#include "room.hpp"
#include "gamestate.hpp"
#include "stringutil.hpp"
#include "game.hpp"

Dirt::Dirt(int x, int y)
:TileAlignedEntity(Entity::DIGABLE,
				   x,
				   y,
				   true),
mAnimation("graphics/dirt.bmp")
{	
	mShoveled = false;
	mH = 1;
	mInitialized = false;
	mLevel = 20;
}

Dirt::~Dirt()
{

}

void Dirt::logic()
{
	if(!mInitialized)
	{
		GameState* gameState = mRoom->getGame()->getGameState();
		if(gameState->getInt(buildGameStateVariableString())==1)
		{
			mShoveled = true;
		}
		mInitialized = true;
	}

}

void Dirt::draw(BITMAP *dest, int scrollx, int scrolly)
{
	if (!mShoveled)
		mAnimation.drawFrame(dest, 0, mX - scrollx, mY - scrolly);
}

bool Dirt::isToBeDeleted()
{
	return mShoveled;
}

void Dirt::damage(int damage, Entity::Direction direction)
{
	mShoveled = true;
	GameState* gameState = mRoom->getGame()->getGameState();
	gameState->put(buildGameStateVariableString(), 1);
	mRoom->spawnDeath(this);
}

std::string Dirt::buildGameStateVariableString()
{
	return "dirt_" + mRoom->getDungeonName() + "_" + toString(mRoom->getDungeonLevel()) + "_" + toString(getX()) + "_" + toString(getY());
}