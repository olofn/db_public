#ifndef DEBRIS_HPP
#define DEBRIS_HPP

#include "entity.hpp"
#include "animation.hpp"

class Debris : public Entity
{
public:
	Debris(int x, 
           int y, 
           float dx, 
           float dy, 
           const std::string& file, 
           int animSpeed = 5, 
           bool autoRemove = false);
	
	virtual void draw(BITMAP *dest, int scrolly, unsigned int layer);

	virtual void logic(Level *level);

	virtual bool isToBeDeleted();

	virtual unsigned int getType() { return Entity::DECORATION_TYPE; }

	virtual bool drawInLayer(unsigned int layer) { return layer == Entity::EXPLOSION_LAYER; }

protected:
	Animation mAnimation;
	int mAnimSpeed;
	bool mAutoRemove;
	float mX, mY, mDX, mDY;
	bool mToBeDeleted;
	int mFrameCounter;
};

#endif