#include "endingcutscene.hpp"
#include "room.hpp"
#include "tilemap.hpp"
#include "game.hpp"
#include "gamestate.hpp"
#include "stringutil.hpp"

EndingCutScene::EndingCutScene()
:Entity(Entity::OTHER, 0, 0, 0, 0, false)
{
	mHasRun = false;

}
void EndingCutScene::logic()
{
	if (mHasRun)
		return;

	mRoom->getPlayer()->setPosition(220, 0);
	mRoom->addActorStateCutScene(mRoom->getPlayer(), "walkdown");
	mRoom->addWaitForActorPostitionCutScene(mRoom->getPlayer(), 220, 112);
	mRoom->addActorStateCutScene(mRoom->getPlayer(), "standdown");
	mRoom->addDialogCutScene("Mom: Ted are you back with the milk?", false);
	mRoom->addDialogCutScene("Ted: Yes mom...", false);
	mRoom->addDialogCutScene("Mom: Good boy.", false);
	mRoom->addWaitCutScene(20);
	mRoom->addActorStateCutScene(mRoom->getPlayer(), "walkleft");
	mRoom->addWaitForActorPostitionCutScene(mRoom->getPlayer(), 147, 112);
	mRoom->addActorStateCutScene(mRoom->getPlayer(), "standdown");
	mRoom->addDialogCutScene("Ted: Now where were I...", false);
	mRoom->addDialogCutScene("Ted: YES! I was about to battle lord vapor!!", false);
	mRoom->addWaitCutScene(20);
	mRoom->addMusicCutScene("music/olof.xm", 1.0f);
	mRoom->addWaitCutScene(20);
	mRoom->addActorStateCutScene(mRoom->getPlayer(), "walkup");
	mRoom->addWaitForActorPostitionCutScene(mRoom->getPlayer(), 147, 90);
	mRoom->addActorStateCutScene(mRoom->getPlayer(), "standdown");
	mRoom->addWaitCutScene(50);
	mRoom->addDialogCutScene("Ted: I hope i dont get interputed with stupid tasks again.", false);
	mRoom->addWaitCutScene(200);
	mRoom->addTextCutScene("Thank you for playing the game!", 200);

	// Post mortem
	GameState *s = mRoom->getGame()->getGameState();
	mRoom->addWaitCutScene(100);
	mRoom->addTextCutScene("During your adventure you have...", 200);
	mRoom->addWaitCutScene(50);
	mRoom->addTextCutScene("...swung your sword " + toString(s->getInt("attacks")) + " times...", 200);
	mRoom->addWaitCutScene(50);
	mRoom->addTextCutScene("...slain " + toString(s->getInt("kills")) + " foes...", 200);
	mRoom->addWaitCutScene(50);
	mRoom->addTextCutScene("...taken " + toString(s->getInt("damagetaken")) + " hearts of damage...", 200);
	mRoom->addWaitCutScene(50);
	mRoom->addTextCutScene("...travelled " + toString(s->getInt("walkdistance")) + " pixels...", 200);
	mRoom->addWaitCutScene(50);
	mRoom->addTextCutScene("...and aquired 1 package of milk!!", 200);

	mRoom->addWaitCutScene(100);
	mRoom->addTextCutScene("See you next Speedhack!!", 200);
	mRoom->addWaitCutScene(100);
	mRoom->addTextCutScene("Over and out from Darkbits.", 200);
	mRoom->addWaitCutScene(100);
	mRoom->addTextCutScene("the end", 200);

	if (mRoom->getGame()->unlockHeroicMode()) {
		mRoom->addWaitCutScene(50);
		mRoom->addTextCutScene("heroic mode unlocked!!", 200);
	}

	mRoom->addGameOverCutScene();
	mRoom->startCutScenes();


	mHasRun = true;
}
