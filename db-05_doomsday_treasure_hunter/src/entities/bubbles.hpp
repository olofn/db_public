#ifndef DB_BUBBLES_HPP
#define DB_BUBBLES_HPP

#include "entity.hpp"
#include "animation.hpp"

#include <vector>

class Bubbles: public Entity
{
public:
    Bubbles();
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
	void logic(Level *Level);
    bool drawInLayer(unsigned int layer);

protected:
    class BubbleParticle
    {
    public:
        BubbleParticle(int x_, int y_, int z_, int dy_)
            : x(x_),
              y(y_),
              z(z_),
              dy(dy_)
        {}
        int x;
        int y;
        int z;
        int dy;
    };

    Animation mAnimation;
    std::vector<BubbleParticle> mBubbleParticlesForeground;
    std::vector<BubbleParticle> mBubbleParticlesBackground;
    int mFrameCounter;
};

#endif
