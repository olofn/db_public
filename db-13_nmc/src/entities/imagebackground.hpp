#ifndef NMC_IMAGEBACKGROUND_HPP
#define NMC_IMAGEBACKGROUND_HPP

#include "entity.hpp"

#include <string>

namespace nmc
{
    class ImageBackground: public Entity
    {
    public:
        ImageBackground(const std::string& filename, int speed);
        void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
        bool isToBeDeleted() { return false; }
        bool drawInLayer(unsigned int layer) { return layer == Entity::BACKGROUND_LAYER; }
        void logic(Room* room) { };

    protected:
        BITMAP* mBackgroundBitmap;
        int mSpeed;
    };
}
#endif