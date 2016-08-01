#include "items/milk.hpp"
#include "entities/bombentity.hpp"

#include "room.hpp"

Milk::Milk()
:Item("milk", false, Item::USABLE, 0, "milk for mom!")
{

}

void Milk::use(Room* room)
{
	room->addDialogCutScene("ted: no I should not use it. mom will get angry.");
	room->startCutScenes();
}