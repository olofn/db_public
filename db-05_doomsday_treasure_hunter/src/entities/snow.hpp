#ifndef NMC_SNOWENTITY_HPP
#define NMC_SNOWENTITY_HPP

#include "entity.hpp"
#include "animation.hpp"

#include <vector>

class Snow: public Entity
{
public:
    Snow();
    void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
	void logic(Level *Level);
    bool isToBeDeleted() { return false; }
    bool drawInLayer(unsigned int layer);

protected:
    class SnowParticle
    {
    public:
        SnowParticle(int x_, int y_, int z_, int dy_)
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
    std::vector<SnowParticle> mSnowParticlesForeground;
    std::vector<SnowParticle> mSnowParticlesBackground;
    int mFrameCounter;
};

#endif
