#ifndef DB_PORTALHOME_HPP
#define DB_PORTALHOME_HPP

#include "tilealignedentity.hpp"

class PortalHome: public TileAlignedEntity
{
public:
	PortalHome(int x, int y);
	~PortalHome();
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly) {}
private:
	bool mInitialized;
	int mFrameCounter;
};
#endif