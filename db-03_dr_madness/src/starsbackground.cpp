#include "starsbackground.hpp"

StarsBackground::StarsBackground()
: Entity(false)
{
    for (unsigned int i = 0; i < 100; i++)
    {
        int dy = rand() % 10 + 7;
        mStars.push_back(Star(rand() % 240, 
                              (rand() % 240) * dy,
                              dy));
    }
}

StarsBackground::~StarsBackground()
{

}

void StarsBackground::logic(Level* level)
{

}

void StarsBackground::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	clear_to_color(dest, makecol(30, 0, 40));

    for (unsigned int i = 0; i < mStars.size(); i++)
    {
        int x = mStars[i].x;
        int y = (mStars[i].y - scrolly) / mStars[i].dy;

        if (y < 0)
        {
            mStars[i].x = rand() % 240;
            mStars[i].y += 240 * mStars[i].dy;
        }

        int color = 1000 / mStars[i].dy ;
        putpixel(dest, 
                 x,
                 y,
                 makecol(color, color, color));
    }
}