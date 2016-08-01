#include "items/calciumcrystal.hpp"

#include "room.hpp"
CalciumCrystal::CalciumCrystal()
:Item("Calcium Crystal", true, Item::OTHER, 0, "Shines with mystical light!")
{

}

void CalciumCrystal::use(Room* room)
{
	//room->getPlayer()->setHealth(room->getPlayer()->getMaxHealth());
}