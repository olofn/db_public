#ifndef DBSP07_WATERBACKGROUND_HPP
#define DBSP07_WATERBACKGROUND_HPP

#include "entity.hpp"

#include <vector>

class WaterBackground: public Entity
{
public:
    WaterBackground();
    ~WaterBackground();
    unsigned int getType() { return Entity::DECORATION_TYPE; }
    void logic(Level* level);
    void draw(BITMAP *dest, int scrolly, unsigned int layer);
    bool drawInLayer(unsigned int layer) { return layer == Entity::BACKGROUND_LAYER || layer == Entity::FOREGROUND_LAYER; }
    bool isToBeDeleted() { return false; }
protected:
    BITMAP *mBackgroundColors;
	int mLevelLength;
	int mFrameCounter;
	int mBgScroll;

	class Particle {
	public:
		Particle(float _x, float _y, float _z) :
		  x(_x), y(_y), z(_z), dx(0.0f), dy(0.0f) {}
		float x, y, z, dx, dy;
	};

	std::vector<Particle> mParticles;
};
#endif