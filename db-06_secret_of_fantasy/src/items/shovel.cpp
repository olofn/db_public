#include "items/shovel.hpp"
#include "entities/bombentity.hpp"

#include "room.hpp"

Shovel::Shovel()
:Item("shovel", false, Item::USABLE, 0, "dig for cool stuff!")
{

}

void Shovel::use(Room* room)
{
	std::vector<Entity*> digables = room->collidesWith(room->getPlayer(), Entity::DIGABLE, 5);
	for (unsigned int i = 0; i < digables.size(); i++)
	{
		digables[i]->damage(0, Entity::LEFT);
		break;
	}
}