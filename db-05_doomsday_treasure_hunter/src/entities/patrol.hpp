#ifndef DB_PATROL_HPP
#define DB_PATROL_HPP

#include "entity.hpp"
#include "animation.hpp"

class Patrol: public Entity
{
public:
    Patrol(int x, int y);
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
    void logic(Level *level);
    bool drawInLayer(unsigned int layer) { return layer == Entity::PLAYER_LAYER; }
    void handleCollision(Entity *other, Level* level);
    void message(const std::string& message, Entity* distributor);
protected:
    enum State
    {
        LEFT,
        RIGHT,
        STOP,
        STUNNED
    };
    Animation mAnimation;
    int mFrameCounter;
    int mStateCounter;
    State mState;
    State mStateBeforeStunned;
    bool mFacingLeft;
};
#endif
