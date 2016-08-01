#ifndef NMC_GRADIENTBACKGROUND_HPP
#define NMC_GRADIENTBACKGROUND_HPP

#include "entity.hpp"

namespace nmc
{
    class GradientBackground: public Entity
    {
    public:
        GradientBackground(int r1, int g1, int b1, int r2, int g2, int b2);
        ~GradientBackground();
        void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
        void logic(Room *room) { };
        bool isToBeDeleted() { return false; }
        bool drawInLayer(unsigned int layer) { return layer == Entity::BACKGROUND_LAYER; }

    protected:
        BITMAP* mGradientBitmap;
    };
}
#endif