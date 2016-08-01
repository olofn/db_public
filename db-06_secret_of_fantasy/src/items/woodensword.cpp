#include "items/woodensword.hpp"
#include "entities/swoosh.hpp"
#include "resourcehandler.hpp"
#include "room.hpp"

WoodenSword::WoodenSword()
:Item("wooden sword", false, Item::WEAPON, 0, "a plain toy sword!"),
mSample(ResourceHandler::getInstance()->getSample("sound/swoosh.wav"))
{

}

void WoodenSword::use(Room* room)
{
	room->addEntity(new Swoosh(room->getPlayer()->getCenterX(), 
							   room->getPlayer()->getCenterY(), 
							   room->getPlayer()->getDirection(),
							   0,
							   0,
							   8,
							   12));
	play_sample(mSample, 127, 127, 1000, 0);
}