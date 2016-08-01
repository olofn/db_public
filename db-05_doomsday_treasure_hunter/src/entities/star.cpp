#include "entities/star.hpp"

#include "level.hpp"
#include "resourcehandler.hpp"
#include "blending.hpp"

Star::Star(int x, int y)
: Entity(x, y, 16, 16, true),
   mAnimation("star.bmp"),
   mTaken(false),
   mFrameCounter(0)
{
   mSample = ResourceHandler::getInstance()->getSample("star.wav");
}
void Star::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    if (mTaken)
        return;

    mAnimation.drawFrame(dest, mFrameCounter / 10, getX() - scrollx, getY() - scrolly);

    int phase = mFrameCounter % 20;
	
    if (phase > 10) {
		phase = 20 - phase;
	}

	int x = mX - scrollx + getWidth() / 2;
	int y = mY - scrolly + 8;
	int c = makecol(35 + (10 - phase) * 3, 0, 5 + (10 - phase) * 3);
	int r = 4 + phase / 4;

  
    //int c = makecol(20 + (10 - phase) * 3, 30 + (10 - phase) * 3, 0);

   // int x = mX - scrollx + getWidth() / 2;
    //int y = mY - scrolly + getHeight() / 2;
	setAddBlender();
	drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
	circlefill(dest, x, y, getWidth() - 4, c);
    circlefill(dest, x, y, getWidth() / 2, c);
	drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
}

void Star::logic(Level *level)
{
    mFrameCounter++;
}

void Star::handleCollision(Entity *other, Level *level)
{
    if (!mTaken && level->getPlayer() == other)
    {
        play_sample(mSample, 100, 128, 1000, 0);
        mTaken = true;
        level->setCollectedStars(level->getCollectedStars() + 1);
    }
}
