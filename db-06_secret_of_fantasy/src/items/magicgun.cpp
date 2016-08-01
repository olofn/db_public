#include "items/magicgun.hpp"
#include "resourcehandler.hpp"
#include "entities/shot.hpp"

#include "room.hpp"

MagicGun::MagicGun()
:Item("magic gun", false, Item::WEAPON, 0, "a gun of true magic!"),
mSample(ResourceHandler::getInstance()->getSample("sound/swoosh.wav"))
{

}

void MagicGun::use(Room* room)
{
	int speed = 4;
	int x = 0;
	int y = 0;
	switch(room->getPlayer()->getDirection())
	{
	case Actor::LEFT:
		x = -speed;
		break;
	case Actor::RIGHT:
		x = speed;
		break;
	case Actor::UP:
		y = -speed;
		break;
	case Actor::DOWN:
		y = speed;
		break;
	}

	room->addEntity(new Shot(Entity::OTHER, 
							 Entity::ENEMY, 
							 room->getPlayer()->getCenterX(), 
							 room->getPlayer()->getCenterY(), 
							 x,
							 y, 
							 100, 
							 "graphics/vaporshot.bmp", 
							 3, 
							 15,
							 room->getPlayer()->getDirection()));
	play_sample(mSample, 127, 127, 1000, 0);
}