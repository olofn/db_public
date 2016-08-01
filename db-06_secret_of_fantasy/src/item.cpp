#include "item.hpp"
#include "stringutil.hpp"
#include "exception.hpp"

Item::Item(const std::string& name, 
	 bool stackable, 
	 Item::Type type,
	 int levelRequirement,
	 const std::string& description)
{
	mName = toUpperCase(name);
	mStackable = stackable;
	mType = type;
	mLevelRequirement = levelRequirement;
	mDescription = toUpperCase(description);
}

Item::Type Item::getType() const
{
	return mType;
}
bool Item::isStackable() const
{
	return mStackable;
}
const std::string& Item::getName()
{
	return mName;
}
int Item::getLevelRequirement()
{
	return mLevelRequirement;
}
const std::string& Item::getDescription()
{
	return mDescription;
}

std::string Item::getHelp()
{
	switch (mType)
	{
	case ARMOR:
		return std::string("USE ALT TO EQUIP");
	case WEAPON:
		return std::string("USE ALT TO EQUIP");
	case USABLE:
		return std::string("USE ALT TO EQUIP AS A USEABLE TOOL");
	case CONSUMEABLE:
		return std::string("USE ALT TO CONSUME");
	case OTHER:
		return std::string("");
	default:
		throw DB_EXCEPTION("Unknown type!");
	}
}
