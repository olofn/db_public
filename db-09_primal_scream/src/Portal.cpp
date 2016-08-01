#include "Precompiled.hpp"

#include "Portal.hpp"
#include "Resource.hpp"
#include "Sound.hpp"

Portal::Portal() : 
	mSize(0),
	mPlayed(false)
	, myFrameCounter(0)
{
	
}
		
void Portal::update()
{
	mSize++;
	myFrameCounter++;

	if (!mPlayed)
	{
		mPlayed = true;
		Sound::playSample("data/sounds/portal.wav");
	}

	if (myFrameCounter >= 60 * 10)
	{
		remove();
	}
}

void Portal::draw(BITMAP *dest, int scrollx, int scrolly, int layer)
{
	Random r(5);

	for (int i = 0; i < 50; i++)
	{
		float radius = ((50 - i) * mSize) / 50.0f;
		radius = clamp(radius, 0.0f, 40.0f);
		ellipsefill(dest, getDrawPositionX() + scrollx, getDrawPositionY() + 8 + scrolly - 20, (int)(radius / 1.5f), (int)(radius), r.getInt(0, 0xffffff));
	}
}

int Portal::getLayer()
{
	return 0;
}