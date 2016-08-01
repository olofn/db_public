#ifndef DB_ENERGYDRINK_HPP
#define DB_ENERGYDRINK_HPP

#include "item.hpp"

class EnergyDrink: public Item
{
public:
	EnergyDrink();
	void use(Room* room);
};
#endif