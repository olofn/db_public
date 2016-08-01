#include "tile.hpp"

Tile::Tile(int x, int y, const std::string& filename, bool solid)
:mX(x), mY(y), mSolid(solid)
{
    if (filename == "")
        mAnimation = NULL;
    else
        mAnimation = new Animation(filename);
}

Tile::~Tile()
{
    delete mAnimation;
}
   
void Tile::draw(BITMAP *dest, int scrollx, int scrolly)
{
    if (mAnimation != NULL)
        mAnimation->drawFrame(dest, 0, mX - scrollx, mY - scrolly);
}
    
void Tile::logic()
{

}

