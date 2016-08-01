#ifndef DB_CURE_HPP
#define DB_CURE_HPP

#include "item.hpp"

class Cure: public Item
{
public:
	Cure();
	void use(Room* room);
};
#endif