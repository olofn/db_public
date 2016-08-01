#include "towerdoor.hpp"
#include "room.hpp"
#include "tilemap.hpp"
#include "gamestate.hpp"
#include "game.hpp"
#include "stringutil.hpp"

TowerDoor::TowerDoor(int x, 
					 int y, 
					 const std::string& targetDungeon, 
					 int targetLevel) :
	Entity(OTHER, x, y, 16, 7, true),
	targetDungeon(targetDungeon),
	targetLevel(targetLevel),
	animation("graphics/door.bmp", 4)
{
	open = false;
	mInitialized = false;
}

void TowerDoor::logic()
{
	std::string var = buildGameStateVariableString();
	GameState* gameState = mRoom->getGame()->getGameState();

	if (!mInitialized)
	{
		if (gameState->getInt(var) != 0)
		{
			mCheckForCrystals = false;
			open = true;
		}
		else
		{
			mCheckForCrystals = true;
			int x = (mX + mW / 2) / TileMap::TILE_SIZE;
			int y = (mY + mH / 2) / TileMap::TILE_SIZE;
			mRoom->getTileMap()->setFlags(x, y, TileMap::FLAG_SOLID);
		}
		mInitialized = true;
	}

	if (mCheckForCrystals)
	{
		if (mRoom->collidesWith(this, PLAYER, 10).size() != 0 && mRoom->getKeyState()->isActionPressed())
		{
			int amount = mRoom->getPlayer()->getInventory()->getAmountForItem("CALCIUM CRYSTAL");
			if (amount == 0)
			{
				mRoom->addDialogCutScene("Door: You need 5 calcium crystals to enter lord vapors tower!");
			}
			else if (amount < 5)
			{
				mRoom->addDialogCutScene("Door: You need 5 calcium crystals.");
				mRoom->addDialogCutScene("Door: To enter mighty lord vapors tower!");
				mRoom->addDialogCutScene("Ted: But I have " + toString(amount) + ". Come on!");
				mRoom->addDialogCutScene("Door: It is not good enough.");
				mRoom->addDialogCutScene("Ted: Jeez... I just want to go home and continue playing my video game...");
			}
			else if (amount >= 5)
			{
				mRoom->addDialogCutScene("Door: Ah, you have 5 calcium crystals, you may enter!");
				int x = (mX + mW / 2) / TileMap::TILE_SIZE;
				int y = (mY + mH / 2) / TileMap::TILE_SIZE;
				mRoom->getTileMap()->setFlags(x, y, 0);
				open = true;
				mCheckForCrystals = false;
				gameState->put(var, 1);
			}
			mRoom->startCutScenes();
		}
	}
	else
	{
		if (mRoom->collidesWith(this, PLAYER, 0).size() != 0)
		{
			mRoom->getGame()->getGameState()->put("playerpositionx", mRoom->getPlayer()->getX()); 
			mRoom->getGame()->getGameState()->put("playerpositiony", mRoom->getPlayer()->getY() + 2); 
			mRoom->addZoomCutScene(true);
			mRoom->addChangeRoomCutScene("tower.txt", 0, true);
			mRoom->startCutScenes();
		}
	}
}

void TowerDoor::draw(BITMAP *dest, int scrollx, int scrolly)
{
	animation.drawFrame(dest, open ? 0 : 2, getX() - scrollx, getY() - scrolly - 16);
}

std::string TowerDoor::buildGameStateVariableString()
{
	return "towerdoor_" + mRoom->getDungeonName() + "_" + toString(mRoom->getDungeonLevel()) + "_" + toString(getX()) + "_" + toString(getY());
}
