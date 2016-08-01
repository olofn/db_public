#include "paintingcutscene.hpp"

#include "room.hpp"
#include "tilemap.hpp"

PaintingCutScene::PaintingCutScene(int x, int y)
:TileAlignedEntity(Entity::OTHER,
				   x,
				   y,
				   true)
{

}

void PaintingCutScene::logic()
{
	std::vector<Entity*> collisions = mRoom->collidesWith(this, Entity::PLAYER, 2);
	if (collisions.size() > 0 && mRoom->getKeyState()->isActionPressed())
	{
		mRoom->addActorStateCutScene(mRoom->getPlayer(), "standup");
		mRoom->addDialogCutScene("Ted: it is my mom's favourite painting.", false);
		mRoom->addActorStateCutScene(mRoom->getPlayer(), "standdown");
		mRoom->addDialogCutScene("Ted: I really hate it.", false);
		mRoom->startCutScenes();
	}
}

void PaintingCutScene::drawForeground(BITMAP *dest, int scrollx, int scrolly)
{
#ifdef _DEBUG
	if (key[KEY_B])
	{
		rect(dest, mX - scrollx, mY - scrolly - 2, mX - scrollx + 16, mY - scrolly + 16, 128);
	}
#endif
}
