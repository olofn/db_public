#ifndef DBSH07_ENERGYORB_HPP
#define DBSH07_ENERGYORB_HPP

#include "animation.hpp"
#include "entity.hpp"

class EnergyOrb: public Entity
{
public:
    EnergyOrb(int x, int y);
    ~EnergyOrb();
    void logic(Level* level);
    void draw(BITMAP *dest, int scrolly, unsigned int layer);
    bool isToBeDeleted();
	void handleCollision(Entity *other, Level *level);
    unsigned int getType() { return Entity::POWER_UP_TYPE; }
    bool drawInLayer(unsigned int layer) { return layer == Entity::ENEMY_LAYER; }
protected:
    Animation* mAnimation;
    int mFrameCount;
    SAMPLE* mSample;
};

#endif