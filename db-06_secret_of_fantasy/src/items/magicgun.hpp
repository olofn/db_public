#ifndef DB_MAGICGUN_HPP
#define DB_MAGICGUN_HPP

#include "item.hpp"
#include <allegro.h>

class MagicGun: public Item
{
public:
	MagicGun();
	void use(Room* room);
private:
	SAMPLE *mSample;
};
#endif