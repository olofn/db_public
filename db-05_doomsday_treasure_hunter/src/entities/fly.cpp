#include "entities/fly.hpp"
#include <stdlib.h>

#include "blending.hpp"

Fly::Fly(int x, int y)
    : Entity(x, y, 16, 16, true),
      mOriginalX(x),
      mOriginalY(y)
{
    mState = rand() % 4;
    mFrameCounter = 0;
}

void Fly::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    int phase = mFrameCounter % 20;
	if (phase > 10) 
    {
		phase = 20 - phase;
	}

    setAddBlender();
	drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    int w = getWidth() * 2 / 4;
    circlefill(dest, mX + 8 - scrollx, mY + 8 - scrolly, w, makecol(30 - (7 - phase), 30, 0));
    circlefill(dest, mX + 8 - scrollx, mY + 8 - scrolly, w / 2, makecol(30, (10 - phase) + 30, 0));
	drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

    putpixel(dest, mX + 8 - scrollx, mY + 8- scrolly, makecol(0, 0, 0));
}

void Fly::logic(Level *Level)
{
    mFrameCounter++;
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
