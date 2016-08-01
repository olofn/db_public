#ifndef DB_CLOUDSBACKGROUND_HPP
#define DB_CLOUDSBACKGROUND_HPP

#include "entity.hpp"

#include <string>

class CloudsBackground: public Entity
{
public:
    CloudsBackground();
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
    bool drawInLayer(unsigned int layer) { return layer == Entity::BACKGROUND_LAYER; }
    void logic(Level* Level);

protected:
    BITMAP* mCloudsBitmap1;
    BITMAP* mCloudsBitmap2;
    BITMAP* mCloudsBitmap3;
    int mRoomWidth;
    int mRoomHeight;
    int mWind;
};
#endif
