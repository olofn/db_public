#ifndef DBSH07_MEGABLAST_HPP
#define DBSH07_MEGABLAST_HPP

#include "entity.hpp"

class MegaBlast: public Entity
{
public:
    MegaBlast(int x, int y);
    unsigned int getType() { return Entity::PLAYER_BULLET_TYPE; }
	void logic(Level* level);
	void draw(BITMAP *dest, int scrolly, unsigned int layer);
    bool drawInLayer(unsigned int layer) { return layer == Entity::PLAYER_LAYER; }
	bool isToBeDeleted();
	virtual int getDamage() { return 200; };
private:
    int mFrameCounter;
};
#endif