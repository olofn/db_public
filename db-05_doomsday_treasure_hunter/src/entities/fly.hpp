#ifndef DB_FLY_HPP
#define DB_FLY_HPP

#include "entity.hpp"

class Fly: public Entity
{
public:
    Fly(int x, int y);

    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

    void logic(Level *Level);

    bool drawInLayer(unsigned int layer) { return layer == AFTER_TILES_LAYER; }
protected:
    enum State
    {
        RIGHT = 0,
        LEFT,
        UP,
        DOWN
    };

    int mOriginalX;
    int mOriginalY;
    int mState;
    int mFrameCounter;
};

#endif
