#include "entities/snow.hpp"

#include <allegro.h>
#include "timer.hpp"
#include <cmath>

Snow::Snow()
    :Entity(false),
    mAnimation("snow.bmp"),
    mFrameCounter(0)
{
    unsigned int i;
    for (i = 0; i < 40; i++)
    {
        mSnowParticlesForeground.push_back(SnowParticle(rand() % (320 * 3), 
                                                        rand() % (240 * 3), 
                                                        rand() % 2 + 1,
                                                        rand() % 3 + 1));
    }

    for (i = 0; i < 100; i++)
    {
        mSnowParticlesBackground.push_back(SnowParticle(rand() % (320 * 3), 
                                                        rand() % (240 * 3), 
                                                        rand() % 2 + 1,
                                                        rand() % 3 + 1));
    }
}

void Snow::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    if (layer == Entity::FOREGROUND_LAYER)
    {
        unsigned int i;
        for (i = 0; i < mSnowParticlesForeground.size(); i++)
        {
            int x = mSnowParticlesForeground[i].x - scrollx;
            int y = (mSnowParticlesForeground[i].y - scrolly) / mSnowParticlesForeground[i].dy;

            mAnimation.drawFrame(dest, 
                                 0, 
                                 (1000000 + x) % 330 - 5, 
                                 (1000000 + y) % 250 - 5);
        }
    }
    else if (layer == Entity::BACKGROUND_LAYER)
    {
        unsigned int i;
        for (i = 0; i < mSnowParticlesBackground.size(); i++)
        {
            int x = (mSnowParticlesBackground[i].x - scrollx) / mSnowParticlesBackground[i].z;
            int y = (mSnowParticlesBackground[i].y - scrolly) / (mSnowParticlesBackground[i].dy * mSnowParticlesBackground[i].z);

            mAnimation.drawFrame(dest, 
                                 1, 
                                 (1000000 + x) % 330 - 5, 
                                 (1000000 + y) % 250 - 5);
        }
    }
}

void Snow::logic(Level *Level)
{
    mFrameCounter++;
      
    unsigned int i;
    for (i = 0; i < mSnowParticlesForeground.size(); i++)
    {
        if (mFrameCounter % 8 == 0)
        {
            mSnowParticlesForeground[i].x += rand() % 3 - 1;
        }

        mSnowParticlesForeground[i].y += 1;
    }

    for (i = 0; i < mSnowParticlesBackground.size(); i++)
    {
        if (mFrameCounter % 8 == 0)
        {
            mSnowParticlesBackground[i].x += rand() % 3 - 1;
        }

        mSnowParticlesBackground[i].y += 1;
    }
}

bool Snow::drawInLayer(unsigned int layer)
{
    return layer == Entity::FOREGROUND_LAYER
        || layer == Entity::BACKGROUND_LAYER;
}
