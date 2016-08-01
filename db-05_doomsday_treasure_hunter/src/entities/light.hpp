#ifndef DB_LIGHT_HPP
#define DB_LIGHT_HPP

#include "entity.hpp"

class Light: public Entity
{
public:
    Light(int x, int y);
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
	void logic(Level *level);
    bool drawInLayer(unsigned int layer) { return layer == Entity::AFTER_TILES_LAYER; }
protected:
    int mFrameCounter;
};

#endif
