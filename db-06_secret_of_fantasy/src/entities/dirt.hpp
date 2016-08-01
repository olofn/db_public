#ifndef DB_DIRT_HPP
#define DB_DIRT_HPP

#include "tilealignedentity.hpp"
#include "animation.hpp"

class Dirt: public TileAlignedEntity
{
public:
	Dirt(int x, int y);
	~Dirt();
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly);
	void damage(int damage, Entity::Direction direction);
	bool isToBeDeleted();
private:
	std::string buildGameStateVariableString();
	Animation mAnimation;
	int mFrameCounter;
	bool mShoveled;
	bool mInitialized;
};
#endif