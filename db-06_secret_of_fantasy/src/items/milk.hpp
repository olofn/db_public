#ifndef DB_MILK_HPP
#define DB_MILK_HPP

#include "item.hpp"

class Milk: public Item
{
public:
	Milk();
	void use(Room* room);
};
#endif