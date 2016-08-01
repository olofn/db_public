#ifndef DB_INVENTORY_HPP
#define DB_INVENTORY_HPP

#include <vector>
#include "item.hpp"
#include <allegro.h>

class Room;
class Inventory
{
public:
	Inventory();
	~Inventory();

	class Entry
	{
	public:
		Entry():equiped(false),amount(0){}
		Item* item;
		int amount;
		bool equiped;
	};

	bool add(Item* item);
	Item* find(const std::string& name);
	Entry getEntry(int i);
	unsigned int getNumberOfItems();
	void useOrEquipe(Item* item, bool sound = true);
	void useEquipedWeapon(Room* room);
	void setRoom(Room* room);
	void useUsable();
	int getAmountForItem(const std::string& name);

	void save(const std::string& filename = "inventory.sav");
	void load(const std::string& filename = "inventory.sav");
	static bool isSavePresent(const std::string& filename = "inventory.sav");
	void clear();

private:
	void useConsumableItem(int index);
	void equipUsable(int index);
	void equipArmor(int index);
	void equipWeapon(int index);
	std::vector<Entry> mItems;
	Room* mRoom;
	Item* mEquipedUsable;
	Item* mEquipedWeapon;
	Item* mEquipedArmor;

	SAMPLE* mUseItemSample;
};
#endif