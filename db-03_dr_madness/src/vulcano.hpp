#ifndef VULCANO_HPP
#define VULCANO_HPP

#include "entity.hpp"
#include "animation.hpp"

class Vulcano : public Entity
{
public:
	Vulcano(int x, int y);
	
	virtual void draw(BITMAP *dest, int scrolly, unsigned int layer);

	virtual void logic(Level *level);

	virtual bool isToBeDeleted() { return false; }

	virtual unsigned int getType() { return Entity::DECORATION_TYPE; }

	virtual bool drawInLayer(unsigned int layer) { return layer == Entity::BACKGROUND_LAYER || layer == Entity::FOREGROUND_LAYER; }

protected:
	Animation mAnimation;
};

#endif