#ifndef DB_BOMB_HPP
#define DB_BOMB_HPP

#include "entity.hpp"
#include "animation.hpp"

class Bomb: public Entity
{
public:
    Bomb(int x, int y);
    
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
    void logic(Level *level);
    bool drawInLayer(unsigned int layer) { return layer == Entity::AFTER_TILES_LAYER; }
    bool isToBeDeleted();
    float getExplosionImpact(Entity* entity);

protected:
    Animation mAnimation;
    int mFrameCounter;
    bool mExploded;
    SAMPLE* mExplosionSample;

};

#endif
