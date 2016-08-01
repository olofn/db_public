#include "portal.hpp"
#include "resourcehandler.hpp"
#include "util.hpp"
#include "random.hpp"

Portal::Portal(int x, int y) : 
	Entity(OTHER, x, y, 16, 16, false),
	mSize(0),
	mSamplePortal(ResourceHandler::getInstance()->getSample("sound/portal.wav")),
	mPlayed(false)
{
	
}
		
void Portal::logic()
{
	mSize++;

	if (!mPlayed)
	{
		mPlayed = true;
		play_sample(mSamplePortal, 127, 127, 1000, 0);
	}
}

void Portal::draw(BITMAP *dest, int scrollx, int scrolly)
{
	Random r(5);

	for (int i = 0; i < 50; i++)
	{
		float radius = ((50 - i) * mSize) / 50.0f;
		radius = clamp(radius, 0.0f, 40.0f);
		ellipsefill(dest, getCenterX() - scrollx, getCenterY() + 8 - scrolly - 20, (int)(radius / 1.5f), (int)(radius), r.getInt(0, 0xffffff));
	}
}
