#ifndef DB_LASERBEAM_HPP
#define DB_LASERBEAM_HPP

#include "entity.hpp"
#include "animation.hpp"

class LaserBeam : public Entity
{
public:
	LaserBeam(int x, int y, bool horizontal);

	virtual ~LaserBeam();

	void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

	 void logic(Level *Level);

	 void handleCollision(Entity *other, Level* level);
    
     bool drawInLayer(unsigned int layer) { return layer == Entity::AFTER_TILES_LAYER; }

protected:
	int mFrameCounter;
    SAMPLE* mExplosionSample;
    Animation mLightRayAnimation;
    bool mKillPlayer;
};

#endif
