#ifndef DBSP07_STARSBACKGROUND_HPP
#define DBSP07_STARSBACKGROUND_HPP

#include "entity.hpp"

#include <vector>

class StarsBackground: public Entity
{
public:
    StarsBackground();
    ~StarsBackground();
    unsigned int getType() { return Entity::DECORATION_TYPE; }
    void logic(Level* level);
    void draw(BITMAP *dest, int scrolly, unsigned int layer);
    bool drawInLayer(unsigned int layer) { return layer == Entity::BACKGROUND_LAYER; }
    bool isToBeDeleted() { return false; }
protected:
    class Star
    {
    public:
        Star(int x_, int y_, int dy_)
            : x(x_), y(y_), dy(dy_)
        {}
        int x;
        int y;
        int dy;
    };

    std::vector<Star> mStars;
};
#endif