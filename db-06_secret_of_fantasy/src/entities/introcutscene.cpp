#include "introcutscene.hpp"
#include "room.hpp"
#include "tilemap.hpp"

IntroCutScene::IntroCutScene()
:Entity(Entity::OTHER, 0, 0, 0, 0, false)
{
	mHasRun = false;

}
void IntroCutScene::logic()
{
	if (mHasRun)
		return;

	mRoom->getPlayer()->setPosition(getXInTile(9), getYInTile(5));
	mRoom->addMusicCutScene("music/olof.xm", 1.0f);
	mRoom->addWaitCutScene(100);
	mRoom->addDialogCutScene("Mom: Ted you need to go and buy milk!", false);
	mRoom->addWaitCutScene(100);
	mRoom->addDialogCutScene("Mom: Ted are you even listening to me?", false);
	mRoom->addWaitCutScene(50);
	mRoom->addDialogCutScene("Ted: But mom I am playing Secret of Fantasy!!", false);
	mRoom->addDialogCutScene("Mom: Turn off that video game right now young man!", false);
	mRoom->addDialogCutScene("Mom: And go and buy milk!", false);
	mRoom->addDialogCutScene("Ted: Okay mom.", false);
	mRoom->addActorStateCutScene(mRoom->getPlayer(), "walkdown");
	mRoom->addWaitForActorPostitionCutScene(mRoom->getPlayer(), 
											mRoom->getPlayer()->getX(),
											110);
	mRoom->addActorStateCutScene(mRoom->getPlayer(), "standdown");
	mRoom->addStopMusicCutScene();
	mRoom->addWaitCutScene(50);
	mRoom->addDialogCutScene("Ted: Stupid milk.", false);
	mRoom->addActorStateCutScene(mRoom->getPlayer(), "walkright");
	mRoom->addWaitForActorPostitionCutScene(mRoom->getPlayer(), 
										    250,
											110);
	mRoom->addActorStateCutScene(mRoom->getPlayer(), "standdown");
	mRoom->addDialogCutScene("Ted: And I was just about to battle Lord Vapor...", false);
	mRoom->addDialogCutScene("Ted: I better bring my wooden sword with me.", false);
	mRoom->addTextCutScene("WOODEN SWORD RECEIVED", 100);

	mRoom->startCutScenes();
	mHasRun = true;
}
