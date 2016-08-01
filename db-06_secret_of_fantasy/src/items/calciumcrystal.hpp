#ifndef DB_CALCIUMCRYSTAL_HPP
#define DB_CALCIUMCRYSTAL_HPP

#include "item.hpp"

class CalciumCrystal: public Item
{
public:
	CalciumCrystal();
	void use(Room* room);
};
#endif