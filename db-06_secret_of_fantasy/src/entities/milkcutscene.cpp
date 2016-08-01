#include "entities/milkcutscene.hpp"
#include "entities/portal.hpp"
#include "room.hpp"
#include "tilemap.hpp"

MilkCutScene::MilkCutScene(int x, int y) :
	Entity(OTHER, x, y, 16, 16, true),
	mAnimation("graphics/milk.bmp"),
	mActivated(false),
	mInitialized(false)
{
}

MilkCutScene::~MilkCutScene()
{
}

void MilkCutScene::logic()
{
	if (!mInitialized)
	{
		int x = (mX + mW / 2) / TileMap::TILE_SIZE;
		int y = (mY + mH / 2) / TileMap::TILE_SIZE;
		mRoom->getTileMap()->setFlags(x, y, TileMap::FLAG_SOLID);
		mInitialized = true;
	}

	if (!mActivated && mRoom->getKeyState()->isActionPressed() && mRoom->collidesWith(this, PLAYER, 1).size() != 0)
	{
		Actor *vapor = mRoom->getLordVapor();
		Player *player = mRoom->getPlayer();

		player->setState("standright");
		mRoom->freeze(1);

		mActivated = true;
		//mRoom->freeze(50);
		mRoom->addTextCutScene("RECIEVED MILK", 50);
		mRoom->addDialogCutScene("TED: GOT THE LAST ONE!!", false);
		mRoom->addAddEntityCutScene(new Portal(vapor->getX(), 2 * 16));
		mRoom->addWaitCutScene(40);
		mRoom->addActorStateCutScene(vapor, "walkdown");
		mRoom->addWaitForActorPostitionCutScene(vapor, vapor->getX(), 5 * 16, 4);
		mRoom->addActorStateCutScene(vapor, "pause");
		mRoom->addMusicCutScene("music/olof2.xm", 1.0f);
		mRoom->addDialogCutScene("Stranger: ARE YOU BE TAKING MY MILK, BOY?", false);
		mRoom->addActorStateCutScene(vapor, "walkleft");
		mRoom->addWaitForActorPostitionCutScene(vapor, player->getX() + 20, 5 * 16, 4);
		mRoom->addTextCutScene("MILK STOLEN!!", 30);
		mRoom->addActorStateCutScene(vapor, "walkright");
		mRoom->addWaitForActorPostitionCutScene(vapor, vapor->getX() + 2, 5 * 16, 4);
		mRoom->addActorStateCutScene(vapor, "walkup");
		mRoom->addWaitForActorPostitionCutScene(vapor, vapor->getX(), 0, 4);

		mRoom->addDialogCutScene("TED: HEY, THAT WAS MY MILK!!", false);
		mRoom->addActorStateCutScene(player, "walkright");
		mRoom->addWaitForActorPostitionCutScene(player, vapor->getX(), player->getY() + player->getWidth() - 1, 4);
		mRoom->addActorStateCutScene(player, "walkup");
		mRoom->addWaitForActorPostitionCutScene(player, vapor->getX(), 0, 4);	

		mRoom->addZoomCutScene(true);
		mRoom->addChangeRoomCutScene("vaporandhisplan.txt", 0, true);

		mRoom->startCutScenes();

		int x = (mX + mW / 2) / TileMap::TILE_SIZE;
		int y = (mY + mH / 2) / TileMap::TILE_SIZE;
		mRoom->getTileMap()->setFlags(x, y, 0);
	}
}

void MilkCutScene::draw(BITMAP *dest, int scrollx, int scrolly)
{
	if (!mActivated)
		mAnimation.drawFrame(dest, 0, mX - scrollx, mY - scrolly);
}
