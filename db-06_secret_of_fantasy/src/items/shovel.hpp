#ifndef DB_SHOVEL_HPP
#define DB_SHOVEL_HPP

#include "item.hpp"

class Shovel: public Item
{
public:
	Shovel();
	void use(Room* room);
};
#endif