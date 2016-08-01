#ifndef NMC_SPIDER_HPP
#define NMC_SPIDER_HPP

#include "entities\enemy.hpp"

namespace nmc
{
	class Spider : public Enemy
	{
	public:
        Spider(int x, int y);
        void damage(Shot *s, int amount);
        void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
        void enemyLogic(Room *room);
        bool isToBeDeleted();

    protected:
        Animation mAnimation;
        int mFrameCounter;
        int mStateCounter;
		int mDY;
		int mStartY;
		int mHealth;
		int mHurtTimer;
	};
}

#endif