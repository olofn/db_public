#ifndef DB_DISAPPEARINGTILE_HPP
#define DB_DISAPPEARINGTILE_HPP

#include "entity.hpp"
#include "animation.hpp"

class DisappearingTile: public Entity
{
public:
    DisappearingTile(int x, int y, int timeOffset);
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
    void logic(Level *level);
    bool drawInLayer(unsigned int layer) { return layer == Entity::BEFORE_TILES_LAYER; }
protected:
    Animation mAnimation;
    bool mInitialised;
    bool mVisible;
    int mFrameCounter;
    int mTimeOffset;
};
#endif
