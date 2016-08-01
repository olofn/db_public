#ifndef DB_STAR_HPP
#define DB_STAR_HPP

#include "entity.hpp"
#include "animation.hpp"

class Star: public Entity
{
public:
    Star(int x, int y);
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
    void logic(Level *level);
    bool drawInLayer(unsigned int layer) { return layer == Entity::AFTER_TILES_LAYER; }
    void handleCollision(Entity *other, Level *level);
protected:
    bool mTaken;
    Animation mAnimation;
    int mFrameCounter;
    SAMPLE* mSample;
};

#endif
