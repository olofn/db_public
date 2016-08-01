#ifndef DB_BOMB_HPP
#define DB_BOMB_HPP

#include "item.hpp"

class Bomb: public Item
{
public:
	Bomb();
	void use(Room* room);
};
#endif