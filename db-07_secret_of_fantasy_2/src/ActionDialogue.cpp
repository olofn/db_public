#include "Precompiled.hpp"
#include "ActionDialogue.hpp"
#include "Battle.hpp"
#include "Gui.hpp"

void ActionDialogue::onEnter( Battle *battle )
{
	myBattle = battle;
	myBattle->getGui()->showDialogue(myDialogue);
}

void ActionDialogue::onLeave()
{

}

void ActionDialogue::onLogic()
{

}

bool ActionDialogue::isDone()
{
	return myBattle->getGui()->isDialogueDone();
}

void ActionDialogue::addText( const std::string& text )
{
	myDialogue.addText(text);
}
