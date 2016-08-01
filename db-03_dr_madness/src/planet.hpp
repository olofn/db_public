#ifndef PLANET_HPP
#define PLANET_HPP

#include "entity.hpp"
#include "animation.hpp"

class Planet : public Entity
{
public:
	Planet(const std::string &file);
	
	virtual void draw(BITMAP *dest, int scrolly, unsigned int layer);

	virtual void logic(Level *level);

	virtual bool isToBeDeleted() { return false; }

	virtual unsigned int getType() { return Entity::DECORATION_TYPE; }

	virtual bool drawInLayer(unsigned int layer) { return layer == Entity::BACKGROUND_LAYER; }

protected:
	Animation mAnimation;
	int mLevelLength;
};

#endif