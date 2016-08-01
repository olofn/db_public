#include "items/windsword.hpp"
#include "entities/swoosh.hpp"
#include "resourcehandler.hpp"

#include "room.hpp"

WindSword::WindSword()
:Item("wind sword", false, Item::WEAPON, 0, "the sword of the wind!"),
mSample(ResourceHandler::getInstance()->getSample("sound/swoosh.wav"))
{

}

void WindSword::use(Room* room)
{
	room->addEntity(new Swoosh(room->getPlayer()->getCenterX(), 
							   room->getPlayer()->getCenterY(), 
							   room->getPlayer()->getDirection(),
							   0,
							   0,
							   3,
							   6));
	room->addEntity(new Swoosh(room->getPlayer()->getCenterX(), 
							   room->getPlayer()->getCenterY(), 
							   room->getPlayer()->getDirection(),
							   2,
							   10,
							   3,
							   6));
	room->addEntity(new Swoosh(room->getPlayer()->getCenterX(), 
							   room->getPlayer()->getCenterY(), 
							   room->getPlayer()->getDirection(),
							   4,
							   20,
							   3,
							   6));
	play_sample(mSample, 127, 127, 1000, 0);
}