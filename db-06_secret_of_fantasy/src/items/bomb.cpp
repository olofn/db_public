#include "items/bomb.hpp"
#include "entities/bombentity.hpp"

#include "room.hpp"
Bomb::Bomb()
:Item("bomb", true, Item::USABLE, 0, "blow something up!")
{

}

void Bomb::use(Room* room)
{
	room->addEntity(new BombEntity(room->getPlayer()->getX(), room->getPlayer()->getY() - 5));
}