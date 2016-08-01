#ifndef DB_TILE_HPP
#define DB_TILE_HPP

#include "animation.hpp"
#include "entity.hpp"

class Tile
{
public:
    Tile(int x, int y, const std::string& filename, bool solid = true);
    ~Tile();
    void draw(BITMAP *dest, int scrollx, int scrolly);
    void logic();
    bool isSolid() { return mSolid; }
    int getX() { return mX; }
    int getY() { return mY; }
protected:
    Animation* mAnimation;
    int mX;
    int mY;
    bool mSolid;
};
#endif
