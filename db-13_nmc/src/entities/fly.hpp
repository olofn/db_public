#ifndef NMC_FLIES_HPP
#define NMC_FLIES_HPP

#include "entity.hpp"

#include <vector>

namespace nmc
{
    class Fly: public Entity
    {
    public:
        Fly(int x, int y);

        void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

        void logic(Room *room);

        bool isToBeDeleted();

        bool drawInLayer(unsigned int layer) { return layer == PLAYER_LAYER; }
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
    };
}

#endif