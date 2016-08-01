#ifndef DB_SHOPKEEPER_HPP
#define DB_SHOPKEEPER_HPP

#include "tilealignedentity.hpp"
#include "animation.hpp"
#include <vector>
#include <string>

class ShopKeeper: public TileAlignedEntity
{
public:
	ShopKeeper(int x, int y);
	~ShopKeeper();
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly);
private:
	Animation mAnimation;
	int mFrameCounter;
	bool mInitialized;
};
#endif