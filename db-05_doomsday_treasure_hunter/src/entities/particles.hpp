#ifndef DB_PARTICLES_HPP
#define DB_PARTICLES_HPP

#include "entity.hpp"
#include "animation.hpp"

class Particles : public Entity
{
public:
	Particles(int x, 
              int y, 
              float dx, 
              float dy, 
              const std::string& file, 
              int animSpeed = 5, 
              bool autoRemove = false);
	
	virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

	virtual void logic(Level *level);

	virtual bool isToBeDeleted();

    virtual bool drawInLayer(unsigned int layer) { return layer == Entity::AFTER_TILES_LAYER; }

protected:
	Animation mAnimation;
	int mAnimSpeed;
	bool mAutoRemove;
	float mX, mY, mDX, mDY;
	bool mToBeDeleted;
	int mFrameCounter;
};

#endif
