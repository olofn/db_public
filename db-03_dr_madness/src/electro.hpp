#ifndef ELECTRO_HPP
#define ELECTRO_HPP

#include "entity.hpp"
#include "animation.hpp"

class Electro : public Entity
{
public:
	Electro(int x, int y);

	void logic(Level *level);

	void draw(BITMAP *dest, int scrolly, unsigned int layer);

	bool isToBeDeleted() { return false; }

	unsigned int getType() { return Entity::BLOCK_TYPE; }

	bool drawInLayer(unsigned int layer) { return layer == Entity::ENEMY_LAYER; }

	virtual bool stopsBullets() { return false; };

	bool killsPlayer();

	bool isCollidable();

protected:
	bool isOn();

	int mFrameCounter;

	Animation mAnimation;
    Animation mAnimation2;
};

#endif