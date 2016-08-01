#ifndef DBSP07_BONUSBACKGROUND_HPP
#define DBSP07_BONUSBACKGROUND_HPP

#include "entity.hpp"

#include <vector>

class BonusBackground: public Entity
{
public:
    BonusBackground();
    ~BonusBackground();
    unsigned int getType() { return Entity::DECORATION_TYPE; }
    void logic(Level* level);
    void draw(BITMAP *dest, int scrolly, unsigned int layer);
    bool drawInLayer(unsigned int layer) { return layer == Entity::BACKGROUND_LAYER; }
    bool isToBeDeleted() { return false; }
protected:
      void rotoZoom(BITMAP *dest, float angle, float scale);
      BITMAP* mRotoZoom;
      BITMAP* mRotoZoomDest;
      int mFrameCounter;
};
#endif