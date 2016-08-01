#ifndef NMC_CEILINGDROP_HPP
#define NMC_CEILINGDROP_HPP

#include "entity.hpp"

namespace nmc 
{

	class CeilingDrop : public Entity {
	public:
		CeilingDrop(int x, 
                    int y);
		virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
		virtual void logic(Room *room);
        virtual bool isToBeDeleted() { return false; }

    protected:
        enum State
        {
            NONE,
            CEILING,
            FALLING,
            HIT
        };

        int mFrameCounter;
        int mStateTime;
        State mState;
        int mOriginalX;
        int mOriginalY;
		int mDY;
	};
}

#endif