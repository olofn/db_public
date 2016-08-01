#ifndef DB_ROLLINGSPIKES_HPP
#define DB_ROLLINGSPIKES_HPP

#include "entity.hpp"
#include "animation.hpp"

class RollingSpikes: public Entity
{
public:
    RollingSpikes(int x, int y);
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
    void logic(Level *level);
    bool drawInLayer(unsigned int layer) { return layer == Entity::PLAYER_LAYER; }
    void handleCollision(Entity *other, Level* level);
protected:
    enum State
    {
        LEFT,
        RIGHT
    };
    Animation mAnimation;
    int mFrameCounter;
    State mState;
};
#endif
