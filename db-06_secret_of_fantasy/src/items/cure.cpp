#include "items/cure.hpp"

#include "room.hpp"
Cure::Cure()
:Item("cure", true, Item::CONSUMEABLE, 0, "heal yourself")
{

}

void Cure::use(Room* room)
{
	room->getPlayer()->setHealth(room->getPlayer()->getHealth() + 3);
}