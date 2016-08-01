#include "plancutscene.hpp"
#include "room.hpp"
#include "tilemap.hpp"
#include "entities/portal.hpp"

PlanCutScene::PlanCutScene()
:Entity(Entity::OTHER, 0, 0, 0, 0, false)
{
	mHasRun = false;

}

void PlanCutScene::logic()
{
	if (mHasRun)
		return;

	Actor *vapor = mRoom->getLordVapor();
	Player* player = mRoom->getPlayer();
	player->setPosition(vapor->getX() + 16, 0);
	mRoom->addActorStateCutScene(vapor, "standdown");
	
	mRoom->addDialogCutScene("Stranger: Now lets see. How does this milk work...", false);
	mRoom->addWaitCutScene(50);
	mRoom->addAddEntityCutScene(new Portal(vapor->getX() + 16, 32));
	mRoom->addWaitCutScene(50);
	mRoom->addActorStateCutScene(player, "walkdown");
	mRoom->addWaitForActorPostitionCutScene(player, player->getX(), 100);
	mRoom->addActorStateCutScene(player, "standdown");
	mRoom->addWaitCutScene(50);
	mRoom->addDialogCutScene("Stranger: Milk is the last ingredient in my WORLD domination device!", false);
	mRoom->addDialogCutScene("Stranger: Milk is so powerful, and now it is mine!", false);
	mRoom->addDialogCutScene("Stranger: Hahahaha!", false);
	mRoom->addWaitCutScene(50);
	mRoom->addDialogCutScene("Ted: Hey you, my milk!", false);
	mRoom->addActorStateCutScene(vapor, "standup");
	mRoom->addWaitCutScene(50);
	mRoom->addDialogCutScene("Stranger: You!!?", false);
	mRoom->addDialogCutScene("Stranger: I will easily get rid of you with this milk!", false);
	mRoom->addZoomCutScene(true);
	mRoom->addChangeRoomCutScene("overworld.txt", 0, true, 307, 142);
	mRoom->startCutScenes();
	mHasRun = true;
}
