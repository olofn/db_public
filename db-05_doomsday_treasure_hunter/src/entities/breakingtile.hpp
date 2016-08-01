#ifndef DB_BREAKINGTILE_HPP
#define DB_BREAKINGTILE_HPP

#include "entity.hpp"
#include "animation.hpp"

class BreakingTile: public Entity
{
public:
    BreakingTile(int x, int y);
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
    void logic(Level *level);
    bool drawInLayer(unsigned int layer) { return layer == Entity::BEFORE_TILES_LAYER; }
    void handleCollision(Entity *other, Level* level);
protected:
    Animation mAnimation;
    int mHealth;
    bool mInitialised;
    bool mHibernating;
    bool mBreakDownStarted;
    int mFrameCounter;
};
#endif
