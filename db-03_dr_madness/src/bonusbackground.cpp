#include "bonusbackground.hpp"

#include "resourcehandler.hpp"
#include <cmath>
#include "debris.hpp"
#include "level.hpp"
#include "util.hpp"

BonusBackground::BonusBackground()
: Entity(false),
mFrameCounter(0)
{
    mRotoZoom = ResourceHandler::getInstance()->getBitmap("bonus.bmp");
    mRotoZoomDest = create_bitmap(128, 128);
}

BonusBackground::~BonusBackground()
{   
    destroy_bitmap(mRotoZoomDest);
}

void BonusBackground::logic(Level* level)
{
    mFrameCounter++;

    if (mFrameCounter % 5 == 0)
    {
        Debris *d = new Debris(rand() % 240,
                           level->getScrollY() + 250,
				           (frand() - 0.5f) * 5.0f,
				           (frand() - 0.5f) * 10.0f,
				            rand() & 1 ? "bonusdebrismiley.bmp" : "bonusdebriheart.bmp", 
				           2);
        level->addEntity(d);
    }

}

void BonusBackground::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	clear_to_color(dest, makecol(0,0,0));

	float angle = mFrameCounter / 80.0f;
	float scale = 1 / (sin(mFrameCounter / 17.0f) + 2);
	rotoZoom(dest, angle, scale);
}

void BonusBackground::rotoZoom(BITMAP *dest, float angle, float scale)
{
	float co = std::cos(angle) * scale;
	float si = std::sin(angle) * scale;
	int x, y;
	for (y = 0; y < dest->h; y++)
	{
		for (x = 0; x < dest->w; x++)
		{
			float sx = (x - 80) * co - (y - 60) * si;
			float sy = (x - 80) * si + (y - 60) * co;
			int c = getpixel(mRotoZoom, (int)(sx + 100000) & 31, (int)(sy + 100000) & 31);
			putpixel(mRotoZoomDest, x, y, c);
		}
	}

    stretch_blit(mRotoZoomDest, dest, 0, 0, 128, 128, 0, 0, 240, 240);
}