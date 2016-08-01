#include "entities/gradientbackground.hpp"

GradientBackground::GradientBackground(int r1, int g1, int b1, int r2, int g2, int b2)
: Entity(false)
{
    mGradientBitmap = create_bitmap(320, 240);

    int y;

    for (y = 0; y < 240; y += 16)
    {
        int r = (r1 * (240 - y) + r2 * y) / 240;
        int g = (g1 * (240 - y) + g2 * y) / 240;
        int b = (b1 * (240 - y) + b2 * y) / 240;
        
        int pixel = makecol(r, g, b);

        rectfill(mGradientBitmap, 0, y, 320, y + 15, pixel); 
    }
}

GradientBackground::~GradientBackground()
{
    destroy_bitmap(mGradientBitmap);
}

void GradientBackground::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    if (layer == Entity::BACKGROUND_LAYER)
    {
        blit(mGradientBitmap, dest, 0, 0, 0, 0, 320, 240);
    }
}
