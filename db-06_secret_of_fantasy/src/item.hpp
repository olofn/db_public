#ifndef DB_ITEM_HPP
#define DB_ITEM_HPP

#include <string>

class Room;

class Item
{
public:
	enum Type
	{
		ARMOR,
		WEAPON,
		USABLE,
		CONSUMEABLE,
		OTHER
	};
	Item(const std::string& name, 
		 bool stackable, 
		 Type type,
		 int levelRequirement,
		 const std::string& description);
	Type getType() const;
	bool isStackable() const;
	const std::string& getName();
	int getLevelRequirement();
	virtual void use(Room* room) {}
	const std::string& getDescription();
	std::string getHelp();
private:
	int mLevelRequirement;
	Type mType;
	bool mStackable;
	std::string mName;
	std::string mDescription;

};
#endif