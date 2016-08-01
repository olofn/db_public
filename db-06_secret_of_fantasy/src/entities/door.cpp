#include "door.hpp"
#include "room.hpp"
#include "tilemap.hpp"
#include "game.hpp"

Door::Door(int x, int y, bool down, const std::string& targetDungeon, int targetLevel, bool realWorld) :
	Entity(OTHER, x, y, 16, 7, true),
	targetDungeon(targetDungeon),
	targetLevel(targetLevel),
	open(true),
	down(down),
	animation(realWorld ? "graphics/readoor.bmp" : "graphics/door.bmp", realWorld ? 1 : 4)
{

}

void Door::logic()
{
	// Super ugly hack to prevent ted from going from store back to room
	if (mRoom->getDungeonName() == "realworld.txt" && down == false)
	{
		int x = (mX + mW / 2) / TileMap::TILE_SIZE;
		int y = (mY + mH / 2) / TileMap::TILE_SIZE;

		mRoom->getTileMap()->setFlags(x, y, TileMap::FLAG_SOLID);
	}

	if (mRoom->collidesWith(this, PLAYER, 0).size() != 0)
	{
		if (mRoom->getDungeonName() == "overworld.txt")
		{
			mRoom->getGame()->getGameState()->put("playerpositionx", mRoom->getPlayer()->getX()); 
			mRoom->getGame()->getGameState()->put("playerpositiony", mRoom->getPlayer()->getY() + 2); 
			mRoom->getGame()->save();
		}

		mRoom->addZoomCutScene(true);
		mRoom->addChangeRoomCutScene(targetDungeon, targetLevel, true);
		mRoom->startCutScenes();
	}
}

void Door::draw(BITMAP *dest, int scrollx, int scrolly)
{
	animation.drawFrame(dest, open ? (down ? 0 : 1) : 2, getX() - scrollx, getY() - scrolly - 16);
}
