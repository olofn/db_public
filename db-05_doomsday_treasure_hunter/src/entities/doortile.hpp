#ifndef DB_DOORTILE_HPP
#define DB_DOORTILE_HPP

#include "entity.hpp"
#include "animation.hpp"

class DoorTile: public Entity
{
public:
    DoorTile(int x, int y, bool open);
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
    void logic(Level *level);
    bool drawInLayer(unsigned int layer) { return layer == Entity::BEFORE_TILES_LAYER; }
    void message(const std::string& message, Entity* distributor);
protected:
    Animation mAnimation;
    bool mOpen;
    bool mInitialised;
};
#endif
