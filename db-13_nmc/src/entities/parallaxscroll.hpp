#ifndef NMC_PARALLAXSCROLL_HPP
#define NMC_PARALLAXSCROLL_HPP

#include "entity.hpp"

#include <string>

namespace nmc
{
    class ParallaxScroll: public Entity
    {
    public:
        ParallaxScroll();
        void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
        void logic(Room *room);
        bool isToBeDeleted() { return false; }
        bool drawInLayer(unsigned int layer);
        void setBackgroundFloor(const std::string& filename, int offset = 0);
        void setForegroundFloor(const std::string& filename, int offset = 0);
        void setBackgroundCeiling(const std::string& filename, int offset = 0);
        void setForegroundCeiling(const std::string& filename, int offset = 0);

    protected:
        BITMAP* mBackgroundFloorBitmap;
        BITMAP* mForegroundFloorBitmap;
        BITMAP* mBackgroundCeilingBitmap;
        BITMAP* mForegroundCeilingBitmap;
        int mBackgroundFloorOffset;
        int mForegroundFloorOffset;
        int mBackgroundCeilingOffset;
        int mForegroundCeilingOffset;
        int mTileMapHeight;
    };
}
#endif