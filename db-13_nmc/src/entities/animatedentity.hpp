#ifndef NMC_ANIMATEDENTITY_HPP
#define NMC_ANIMATEDENTITY_HPP

#include "animation.hpp"
#include "entity.hpp"

namespace nmc
{
    class AnimatedEntity: public Entity
    {
    public:
		AnimatedEntity(int x, int y, 
                       const std::string& filename, 
                       int speed, 
                       int layer = Entity::PLAYER_LAYER, 
                       bool once = false,
					   Animation::Blending blending = Animation::NONE);

		AnimatedEntity(int x, int y, 
                       const std::string& filename,
					   int framecount,
                       int speed, 
                       int layer = Entity::PLAYER_LAYER, 
                       bool once = false,
					   Animation::Blending blending = Animation::NONE);

		void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
		void logic(Room *room);
        bool isToBeDeleted();

		virtual bool drawInLayer(unsigned int layer);

    protected:
        Animation mAnimation;
		Animation::Blending mBlending;
        int mSpeed;
        int mFrameCounter;
		int mLayer;
		bool mOnce;
    };
}

#endif