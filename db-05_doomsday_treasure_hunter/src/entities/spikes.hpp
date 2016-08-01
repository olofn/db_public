#ifndef DB_SPIKES_HPP
#define DB_SPIKES_HPP

#include "entity.hpp"
#include "animation.hpp"

class Spikes: public Entity
{
public:
    Spikes(int x, int y);
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
    void logic(Level *level);
    bool drawInLayer(unsigned int layer) { return layer == Entity::PLAYER_LAYER; }
    void handleCollision(Entity *other, Level* level);

protected:
    Animation mAnimation;
    Animation mLightRayAnimation;
};
#endif
