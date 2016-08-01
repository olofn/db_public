#include "inventory.hpp"
#include "resourcehandler.hpp"
#include "exception.hpp"
#include "stringutil.hpp"
#include "fileutil.hpp"
#include <iostream>
#include <fstream>
#include "itemfactory.hpp"
#include "resourcehandler.hpp"

Inventory::Inventory()
{
	mEquipedUsable = 0;
	mEquipedWeapon = 0;
	mEquipedArmor = 0;
	mUseItemSample = ResourceHandler::getInstance()->getSample("sound/useitem.wav");
}

Inventory::~Inventory()
{	
	clear();
}

int Inventory::getAmountForItem(const std::string& name)
{
	for (unsigned int i = 0; i < mItems.size(); i++)
	{
		if (mItems[i].item->getName() == name)
			return mItems[i].amount;
	}

	return 0;
}

Item* Inventory::find(const std::string& name)
{
	for (unsigned int i = 0; i < mItems.size(); i++)
	{
		if (mItems[i].item->getName() == name)
			return mItems[i].item;
	}

	return 0;
}

bool Inventory::isSavePresent(const std::string& filename)
{
	try
	{
		std::string data = loadFile(filename);
	}
	catch (Exception e)
	{
		return false;
	}

	return true;
}

void Inventory::clear()
{
	for (unsigned int i = 0; i < mItems.size(); i++)
		delete mItems[i].item;

	mItems.clear();
	mEquipedUsable = 0;
	mEquipedWeapon = 0;
	mEquipedArmor = 0;
}

bool Inventory::add(Item* item)
{
	if (item->isStackable())
	{
		for (unsigned int i = 0; i < mItems.size(); i++)
		{
			if (mItems[i].item->getName() == item->getName())
			{
				mItems[i].amount += 1;
				int a = mItems[i].amount;
				delete item;
				return false;
			}
		}
	}

	Entry entry;
	entry.item = item;
	entry.amount = 1;
	mItems.push_back(entry);
	return true;
}

Inventory::Entry Inventory::getEntry(int i)
{
	return mItems[i];
}

unsigned int Inventory::getNumberOfItems()
{
	return mItems.size();
}

void Inventory::useOrEquipe(Item* item, bool sound)
{
	Item* foundItem;
	int index = -1;
	// Search for item.
	for (unsigned int i = 0; i < mItems.size(); i++)
	{
		if (mItems[i].item->getName() == item->getName())
		{
			foundItem = mItems[i].item;
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		throw DB_EXCEPTION("Item not found in inventory!");
	}

	// Do something with the item.
	if (foundItem->isStackable() 
		&& foundItem->getType() == Item::CONSUMEABLE)
	{
		useConsumableItem(index);
	}
	else if (foundItem->getType() == Item::ARMOR)
	{
		equipArmor(index);
	}
	else if (foundItem->getType() == Item::WEAPON)
	{
		equipWeapon(index);
	}
	else if (foundItem->getType() == Item::USABLE)
	{
		equipUsable(index);
	}

	if (sound)
		play_sample(mUseItemSample, 127, 127, 1000, 0);
}

void Inventory::setRoom(Room* room)
{
	mRoom = room;
}

void Inventory::useUsable()
{
	if (mEquipedUsable == 0)
		return;

	mEquipedUsable->use(mRoom);

	for (unsigned int i = 0; i < mItems.size(); i++)
	{
		if (mItems[i].item->getName() == mEquipedUsable->getName()
			&& mItems[i].item->isStackable())
		{
			mItems[i].amount--;
			if (mItems[i].amount <= 0)
			{
				delete mItems[i].item;
				mItems.erase(mItems.begin() + i);
				mEquipedUsable = 0;
			}
			return;
		}
	}
}

void Inventory::useConsumableItem(int index)
{
	mItems[index].item->use(mRoom);
	mItems[index].amount--;

	if (mItems[index].amount <= 0)
	{
		delete mItems[index].item;
		mItems.erase(mItems.begin() + index);
	}
}

void Inventory::equipUsable(int index)
{
	if (mEquipedUsable != 0)
	{
		for (unsigned int i = 0; i < mItems.size(); i++)
		{
			if (mItems[i].item->getName() == mEquipedUsable->getName())
			{
				mItems[i].equiped = false;
				break;
			}
		}
	}

	mItems[index].equiped = true;
	mEquipedUsable = mItems[index].item;
}

void Inventory::equipArmor(int index)
{
	
}

void Inventory::equipWeapon(int index)
{
	if (mEquipedWeapon != 0)
	{
		for (unsigned int i = 0; i < mItems.size(); i++)
		{
			if (mItems[i].item->getName() == mEquipedWeapon->getName())
			{
				mItems[i].equiped = false;
				break;
			}
		}
	}

	mItems[index].equiped = true;
	mEquipedWeapon = mItems[index].item;
}

void Inventory::useEquipedWeapon(Room* room)
{
	if (mEquipedWeapon == 0)
		return;
	mEquipedWeapon->use(room);
}

void Inventory::save(const std::string& filename)
{
	std::cout << "Saving inventory..." << std::endl;

	std::ofstream file;

    file.open( ResourceHandler::getInstance()->getRealFilename(filename).c_str(), std::ios::out);
        
    if (!file.is_open())
    {
        throw DB_EXCEPTION("Saves file for inventory could not be opened for save! " + filename);
    }
	
	int size = 0;
	for (unsigned int i = 0; i < mItems.size(); i++)
	{
		size += mItems[i].amount;
	}

	file << size << std::endl;

	for (unsigned int i = 0; i < mItems.size(); i++)
	{
		for (unsigned int j = 0; j < mItems[i].amount; j++)
		{
			file << mItems[i].item->getName() << std::endl;
			file << mItems[i].equiped << std::endl;
		}
	}

    file.close();
	std::cout << "Saving done" << std::endl;
}

void Inventory::load(const std::string& filename)
{
	try
    {
		std::cout << "Loading inventory..." << std::endl;
        std::vector<std::string> data = tokenize(loadFile(filename), "\n"); 
		
		int numberOfItems = fromString<int>(data[0]);
		int row = 1;
        for (unsigned int i = 0; i < numberOfItems; i++)
        {
            if (data[row].size() == 0)
			{
				throw DB_EXCEPTION("error in inventory file!");
			}
			Item* item = createItem(data[row]);
			row++;
			bool added = add(item);
			bool equiped = fromString<bool>(data[row]);
			row++;
			if (equiped & added)
			{
				useOrEquipe(item, false);
			}
        }
		std::cout << "Loading done..." << std::endl;
    }
    catch (Exception e)
    {
       throw DB_EXCEPTION("Unable to load inventory save " + filename);
    }
}