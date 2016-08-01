#include "entities/patrol.hpp"

#include "level.hpp"
#include "util.hpp"
#include "blending.hpp"
#include <iostream>

Patrol::Patrol(int x, int y)
:Entity(x + 7, y + 4, 2, 12, true),
mAnimation("patrol.bmp")
{
    mState = LEFT;
    mFacingLeft = true;
    mStateCounter = -200 + (frand() * 100);
    mFrameCounter = 0;
}

void Patrol::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    if (mState == STUNNED)
    {
        mAnimation.drawFrame(dest, 
                             mFrameCounter % 10 < 5, 
                             getX() - scrollx - 7, 
                             getY() -scrolly - 4, 
                             mFacingLeft, false, Animation::FROZEN); 
    }
    else
    {
        mAnimation.drawFrame(dest, 
                             mFrameCounter % 10 < 5, 
                             getX() - scrollx - 7, 
                             getY() -scrolly -4, 
                             mFacingLeft); 

        int phase = mFrameCounter % 20;
	
        if (phase > 10) {
		    phase = 20 - phase;
	    }

	    int x = mX - scrollx + 1;
	    if (mFacingLeft)
            x -= 3;
        else
            x += 3;

        int y = mY - scrolly + 4;
	    int c = makecol(30 + (10 - phase) * 3, 20 + (10 - phase) * 3, 0);
	    int r = 4 + phase / 4;
	    setAddBlender();
	    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
	    circlefill(dest, x, y - 4, 8, c);
        circlefill(dest, x, y - 4, 4, c);
	    drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
    }
}
void Patrol::logic(Level *level)
{
    if (mState != STOP && mState != STUNNED)
        mFrameCounter++;

    mStateCounter++;

    if (mState == STUNNED && mStateCounter > 0)
        mState = mStateBeforeStunned;

    if (mState == LEFT && mStateCounter % 2 == 0)
        mX--;
    else if (mState == RIGHT && mStateCounter % 2 == 0)
        mX++;

    if (mState == LEFT && level->getTileMap()->isLeftSolid(this))
    {
        level->getTileMap()->alignToLeftTile(this);
        mState = RIGHT;
        mFacingLeft = false;
    }

    if (mState == LEFT && !level->getTileMap()->isPeekLeftBelowSolid(this))
    {
        mState = RIGHT;
        mFacingLeft = false;
    }

    if (mState == RIGHT && level->getTileMap()->isRightSolid(this))
    {
        level->getTileMap()->alignToRightTile(this);
        mState = LEFT;
        mFacingLeft = true;
    }

    if (mState == RIGHT && !level->getTileMap()->isPeekRightBelowSolid(this))
    {
        mState = LEFT;
        mFacingLeft = true;
    }

    if (mState != STOP && rand() % 100 == 0 && mStateCounter > 300)
    {
        mState = STOP;
        mStateCounter = -200 + (frand() * 100); 
    }

    if (mState == STOP && mStateCounter > 0)
    {
        if (frand() * 100 < 50)
        {        
            mState = LEFT;
            mFacingLeft = true;
        }
        else
        {
            mState = RIGHT;
            mFacingLeft = false;
        }
    }
}

void Patrol::handleCollision(Entity *other, Level* level)
{
    if (other == level->getPlayer() && mState != STUNNED)
    {
        level->getPlayer()->kill();
    }
}

void Patrol::message(const std::string& message, Entity* distributor)
{
    if (message == "playerelectric")
    {        
        Player* player = (Player*)distributor;
        if (player->isStunnedByElectric(this))
        {
            mStateBeforeStunned = mState;
            mState = STUNNED;
            mStateCounter = -300;
        }
    }
}
