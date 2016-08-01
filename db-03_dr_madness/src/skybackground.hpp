#ifndef DBSP07_SKYBACKGROUND_HPP
#define DBSP07_SKYBACKGROUND_HPP

#include "entity.hpp"
#include "animation.hpp"

#include <vector>

class SkyBackground: public Entity
{
public:
    SkyBackground();
    ~SkyBackground();
    unsigned int getType() { return Entity::DECORATION_TYPE; }
    void logic(Level* level);
    void draw(BITMAP *dest, int scrolly, unsigned int layer);
    bool drawInLayer(unsigned int layer) { return layer == Entity::BACKGROUND_LAYER; }
    bool isToBeDeleted() { return false; }
protected:
    BITMAP *mBackgroundColors;
	int mLevelLength;
	int mFrameCounter;
	int mBgScroll;

    Animation* mCloud1;
    Animation* mCloud2;
};
#endif