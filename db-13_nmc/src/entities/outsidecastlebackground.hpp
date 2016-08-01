#ifndef NMC_OUTSIDECASTLEBACKGROUND_HPP
#define NMC_OUTSIDECASTLEBACKGROUND_HPP

#include "entity.hpp"

#include <string>

namespace nmc
{
    class OutsideCastleBackground: public Entity
    {
    public:
        OutsideCastleBackground();
        void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
        bool isToBeDeleted() { return false; }
        bool drawInLayer(unsigned int layer) { return layer == Entity::BACKGROUND_LAYER; }
        void logic(Room* room);

    protected:
        BITMAP* mCloudsBitmap1;
        BITMAP* mCloudsBitmap2;
        BITMAP* mCloudsBitmap3;
        BITMAP* mCastleBackgroundBitmap1;
        BITMAP* mCastleBackgroundBitmap2;
        BITMAP* mCastleBackgroundBitmap3;
        BITMAP* mCastleBackgroundBitmap4;
        int mRoomWidth;
        int mRoomHeight;
        int mWind;
    };
}
#endif