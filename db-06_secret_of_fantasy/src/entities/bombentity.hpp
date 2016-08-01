#ifndef DB_BOMBENTITY_HPP
#define DB_BOMBENTITY_HPP

#include "entity.hpp"
#include "animation.hpp"
#include <allegro.h>

class BombEntity: public Entity
{
public:
	BombEntity(int x, int y);
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly);
	bool isToBeDeleted();
private:
	void makeDamageToEntity(Entity* entity, float inpact);
	Animation mAnimation;
	int mFrameCounter;
    bool mExploded;
	SAMPLE* mSample;
};

#endif