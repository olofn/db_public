#include "itemfactory.hpp"
#include "item.hpp"
#include "exception.hpp"
#include "items/bomb.hpp"
#include "items/calciumcrystal.hpp"
#include "items/cure.hpp"
#include "items/energydrink.hpp"
#include "items/magicgun.hpp"
#include "items/milk.hpp"
#include "items/shovel.hpp"
#include "items/windsword.hpp"
#include "items/woodensword.hpp"

Item* createItem(const std::string& name)
{
	if (name == "CALCIUM CRYSTAL")
		return new CalciumCrystal();
	if (name == "BOMB")
		return new Bomb();
	if (name == "CURE")
		return new Cure();
	if (name == "ENERGY DRINK")
		return new EnergyDrink();
	if (name == "MAGIC GUN")
		return new MagicGun();
	if (name == "MILK")
		return new Milk();
	if (name == "SHOVEL")
		return new Shovel();
	if (name == "WIND SWORD")
		return new WindSword();
	if (name == "WOODEN SWORD")
		return new WoodenSword();

	throw DB_EXCEPTION("Unknown item!");
	return 0;
}