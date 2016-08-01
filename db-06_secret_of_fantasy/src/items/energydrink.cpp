#include "items/energydrink.hpp"
#include "entities/bombentity.hpp"

#include "room.hpp"

EnergyDrink::EnergyDrink()
:Item("energy drink", true, Item::CONSUMEABLE, 0, "a drink that smells funny...")
{

}

void EnergyDrink::use(Room* room)
{
	room->getPlayer()->setMaxHealth(room->getPlayer()->getMaxHealth() + 1);
	room->getPlayer()->setHealth(room->getPlayer()->getMaxHealth());
}