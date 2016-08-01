#include "entities/fly.hpp"
#include <stdlib.h>

#include <iostream>

namespace nmc
{
    Fly::Fly(int x, int y)
        : Entity(x, y),
          mOriginalX(x),
          mOriginalY(y)
    {
        mState = rand() % 4;
    }

    void Fly::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
    {
         putpixel(dest, mX - scrollx, mY - scrolly, makecol(50, 50, 50));
    }

    void Fly::logic(Room *room)
    {
        if (mState == RIGHT)
        {
            mX += rand() % 2;

            if (rand()  % 3 == 0)
            {
                mY--;
            }
            else if (rand()  % 3 == 1)
            {
                mY++;
            }
        }

        if (mState == LEFT)
        {
            mX -= rand() % 2;

            if (rand()  % 3 == 0)
            {
                mY--;
            }
            else if (rand()  % 3 == 1)
            {
                mY++;
            }
        }

        if (mState == UP)
        {
            mY -= rand() % 2;

             if (rand()  % 3 == 0)
            {
                mX--;
            }
            else if (rand()  % 3 == 1)
            {
                mX++;
            }
        }

        if (mState == DOWN)
        {
            mY += rand() % 2;

            
             if (rand()  % 3 == 0)
            {
                mX--;
            }
            else if (rand()  % 3 == 1)
            {
                mX++;
            }
        }   

        if (rand() % 50 == 0)
        {
            mState = rand() % 4;
        }

        if (mY < mOriginalY - 16)
        {
            mState = DOWN;
        }

        if (mY > mOriginalY + 30)
        {
            mState = UP;
        }

        if (mX < mOriginalX - 30)
        {
            mState = RIGHT;
        }

        if (mX > mOriginalX + 30)
        {
            mState = LEFT;
        }
    }

    bool Fly::isToBeDeleted()
    {
        return false;
    }
}