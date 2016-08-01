#ifndef DBSH07_ENEMY_HPP
#define DBSH07_ENEMY_HPP

#include "entity.hpp"

class Enemy: public Entity
{
public:
    Enemy(int x, int y, int width, int height, int hitCount);
    unsigned int getType() { return Entity::ENEMY_TYPE; }
	bool drawInLayer(unsigned int layer) { return layer == Entity::ENEMY_LAYER; }

protected:
	int mHitCount;
};

#endif