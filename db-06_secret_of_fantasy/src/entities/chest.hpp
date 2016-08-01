#ifndef DB_CHEST_HPP
#define DB_CHEST_HPP

#include "tilealignedentity.hpp"
#include "animation.hpp"
#include "item.hpp"
#include "gamestate.hpp"
class Chest: public TileAlignedEntity
{
public:
	Chest(int x, int y, Item* item, bool dropped);
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly);
	bool isToBeDeleted();
	Item* getItem();
	~Chest();

private:
	static const int NO_FRAMES_TO_BE_OPEN = 40;
	std::string buildGameStateVariableString();

	Animation mAnimation;
	bool mInitialized;
	bool mOpen;
	int mOpenFrameCount;
	Item* mItem;
	bool mUsed;
	void setSolid(bool solid);
	bool mDropped;
};

#endif
