#ifndef DBSP07_CAVEBACKGROUND_HPP
#define DBSP07_CAVEBACKGROUND_HPP

#include "entity.hpp"
#include "animation.hpp"
#include <vector>

class CaveBackground: public Entity
{
public:
    CaveBackground();
    ~CaveBackground();
    unsigned int getType() { return Entity::DECORATION_TYPE; }
    void logic(Level* level);
    void draw(BITMAP *dest, int scrolly, unsigned int layer);
    bool drawInLayer(unsigned int layer) { return layer == Entity::BACKGROUND_LAYER; }
    bool isToBeDeleted() { return false; }
protected:
	Animation mAnimation;
};
#endif