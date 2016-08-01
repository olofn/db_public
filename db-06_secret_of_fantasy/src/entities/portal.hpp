#ifndef DB_PORTAL_HPP
#define DB_PORTAL_HPP

#include "entity.hpp"

class Portal : public Entity
{
public:
	Portal(int x, int y);
		
	void logic();

	void draw(BITMAP *dest, int scrollx, int scrolly);

private:
	SAMPLE *mSamplePortal;
	int mSize;
	bool mPlayed;
};

#endif