#include "entities/bubbles.hpp"

#include <allegro.h>
#include "timer.hpp"
#include <cmath>

Bubbles::Bubbles()
    :Entity(false),
     mAnimation("bubbles.bmp"),
     mFrameCounter(0)
{
    unsigned int i;
    for (i = 0; i < 40; i++)
    {
        mBubbleParticlesForeground.push_back(BubbleParticle(rand() % (320 * 3), 
                                                        rand() % (240 * 3), 
                                                        rand() % 2 + 1,
                                                        rand() % 3 + 1));
    }

    for (i = 0; i < 100; i++)
    {
        mBubbleParticlesBackground.push_back(BubbleParticle(rand() % (320 * 3), 
                                                        rand() % (240 * 3), 
                                                        rand() % 2 + 1,
                                                        rand() % 3 + 1));
    }
}

void Bubbles::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    if (layer == Entity::FOREGROUND_LAYER)
    {
        unsigned int i;
        for (i = 0; i < mBubbleParticlesForeground.size(); i++)
        {
            int x = mBubbleParticlesForeground[i].x - scrollx;
            int y = (mBubbleParticlesForeground[i].y - scrolly) / mBubbleParticlesForeground[i].dy;

            mAnimation.drawFrame(dest, 
                                 0, 
                                 (1000000 + x) % 330 - 5, 
                                 (1000000 + y) % 250 - 5);
        }
    }
    else if (layer == Entity::BACKGROUND_LAYER)
    {
        unsigned int i;
        for (i = 0; i < mBubbleParticlesBackground.size(); i++)
        {
            int x = (mBubbleParticlesBackground[i].x - scrollx) 
                / mBubbleParticlesBackground[i].z;
            int y = (mBubbleParticlesBackground[i].y - scrolly) 
                / (mBubbleParticlesBackground[i].dy 
                * mBubbleParticlesBackground[i].z);

            mAnimation.drawFrame(dest, 
                                 1, 
                                 (1000000 + x) % 330 - 5, 
                                 (1000000 + y) % 250 - 5);
        }
    }
}

void Bubbles::logic(Level *level)
{
    mFrameCounter++;
      
    unsigned int i;
    for (i = 0; i < mBubbleParticlesForeground.size(); i++)
    {
        if (mFrameCounter % 8 == 0)
        {
            mBubbleParticlesForeground[i].x += rand() % 3 - 1;
        }

        if (mFrameCounter % 4 <= 1)
        {
            mBubbleParticlesForeground[i].y -= 1;
        }
    }

    for (i = 0; i < mBubbleParticlesBackground.size(); i++)
    {
        if (mFrameCounter % 8 == 0)
        {
            mBubbleParticlesBackground[i].x += rand() % 3 - 1;
        }

        if (mFrameCounter % 4 <= 1)
        {
            mBubbleParticlesBackground[i].y -= 1;
        }
    }
}

bool Bubbles::drawInLayer(unsigned int layer)
{
    return layer == Entity::FOREGROUND_LAYER
        || layer == Entity::BACKGROUND_LAYER;
}
