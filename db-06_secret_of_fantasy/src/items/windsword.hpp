#ifndef DB_WINDSWORD_HPP
#define DB_WINDSWORD_HPP

#include "item.hpp"
#include <allegro.h>

class WindSword: public Item
{
public:
	WindSword();
	void use(Room* room);
private:
	SAMPLE *mSample;

};
#endif