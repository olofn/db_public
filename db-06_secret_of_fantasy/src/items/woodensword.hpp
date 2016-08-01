#ifndef DB_WOODENSWORD_HPP
#define DB_WOODENSWORD_HPP

#include "item.hpp"
#include <allegro.h>

class WoodenSword: public Item
{
public:
	WoodenSword();
	void use(Room* room);
private:
	SAMPLE *mSample;
};
#endif