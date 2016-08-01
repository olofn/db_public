#ifndef DB_EXPLODABLETILE_HPP
#define DB_EXPLODABLETILE_HPP

#include "entity.hpp"
#include "animation.hpp"

class ExplodableTile: public Entity
{
public:
    ExplodableTile(int x, int y);
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
    void logic(Level *level);
    bool drawInLayer(unsigned int layer) { return layer == Entity::BEFORE_TILES_LAYER; }
    bool isToBeDeleted();
    void message(const std::string& message, Entity* distributor);
protected:
    Animation mAnimation;
    float mHealth;
    bool mInitialised;
    bool mToBeDeleted;
};
#endif
