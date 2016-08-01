#ifndef NMC_RAT_HPP
#define NMC_RAT_HPP

#include "enemy.hpp"
#include "animation.hpp"

namespace nmc
{
    class Rat: public Enemy
    {
    public:
        Rat(int x, int y);
        void damage(Shot *s, int amount);
        void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
        void enemyLogic(Room *room);
        bool isToBeDeleted();

    protected:
        void changeState();

        enum State
        {
            RUNNING,
            SNIFFING,
            HURT,
            DYING,
            DEAD
        };

        enum Direction
        {
            LEFT,
            RIGHT
        };

        Animation mRunningAnimation;
        Animation mSniffingAnimation;
        Animation mHurtAnimation;
        int mFrameCounter;
        int mStateTimer;
        int mHealth;
        int mState;
        int mDirection;
    };
}
#endif