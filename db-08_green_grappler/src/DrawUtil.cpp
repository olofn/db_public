#include "Precompiled.hpp"
#include "DrawUtil.hpp"
#include "Util.hpp"
#include "Resource.hpp"
#include "Animation.hpp"

Animation* DrawUtil::myFadeAnimation = 0;
BITMAP* DrawUtil::myDrawLowResolutionBuffer = 0;

bool DrawUtil::drawDissolveBitmap( BITMAP *aBuffer, BITMAP *src, int x, int y, float amount)
{
	bool result = true;
	int row;
	for (row = 0; row < src->h; row++) {
		float t = amount - ((float)row / (float)src->h);
		if (t <= 0.0f) {
			break;
		}
		if ((row % 2) == 1) {
			continue;
		}
		int offset = (int)(t * t * DissolveHeight * 40);
		if (offset > DissolveHeight) {
			continue;
		}
		masked_blit(src, aBuffer, 0, row, x, y - offset + row, src->w, 1);
		result = false;
	}

	masked_blit(src, aBuffer, 0, row, x, y + row, src->w, src->h - row);
	return result;
}

void DrawUtil::drawGradiant( BITMAP* aBuffer, int x, int y, int width, int height, int startColor, int endColor )
{
	int sr = getr(startColor);
	int sg = getg(startColor);
	int sb = getb(startColor);

	int er = getr(endColor);
	int eg = getg(endColor);
	int eb = getb(endColor);

	int colorHeight = 4;
	int lines = height / colorHeight;

	for (int i = 0; i < lines; i++)
	{
		float t = i / (float)lines;
		int r = clamp(sr * (1.0f - t) - er * t, 0.0f, 255.0);
		int g = clamp(sg * (1.0f - t) - eg * t, 0.0f, 255.0);;
		int b = clamp(sb * (1.0f - t) - eb * t, 0.0f, 255.0);;
		rectfill(aBuffer, 
				 x, 
				 y + i * colorHeight, 
				 x + width, 
				 y + i * colorHeight + colorHeight, 
				 makecol(r, g, b));		
	}
}

bool DrawUtil::drawFadeOut(BITMAP* aBuffer, float aAmount)
{
	if(myFadeAnimation == 0)
	{
		myFadeAnimation = Resource::getAnimation("data/images/fade.bmp");
	}

	aAmount = clamp(aAmount, 0.0f, 1.0f);

	if(aAmount == 0.0f)
	{
		return false;
	}

	int frame = (myFadeAnimation->getFrameCount() - 1) * aAmount;

	for(int y = 0; y < 15; y++)
	{
		for(int x = 0; x < 20; x++)
		{
			myFadeAnimation->drawFrame(aBuffer, frame, x * 16, y * 16);
		}
	}

	return aAmount == 1.0f;
}

bool DrawUtil::drawFadeIn(BITMAP* aBuffer, float aAmount)
{
	if(myFadeAnimation == 0)
	{
		myFadeAnimation = Resource::getAnimation("data/images/fade.bmp");
	}

	aAmount = clamp(aAmount, 0.0f, 1.0f);

	if(aAmount == 1.0f)
	{
		return true;
	}

	int frame = (myFadeAnimation->getFrameCount() - 1) * (1.0f - aAmount);

	for(int y = 0; y < 15; y++)
	{
		for(int x = 0; x < 20; x++)
		{
			myFadeAnimation->drawFrame(aBuffer, frame, x * 16, y * 16);
		}
	}

	return aAmount == 1.0f;
}

void DrawUtil::drawHeatBitmap( BITMAP* aBuffer, BITMAP* aSrc, int aStartY, int aEndY, float aSpeed )
{
	masked_blit(aSrc, aBuffer, 0, 0, 0, 0, aSrc->w, aSrc->h);

	for (int y = aStartY; y < aEndY; y++)
	{
		masked_blit(aSrc, aBuffer, 0, y, sin(aSpeed + y)*2, y, aSrc->w, 1);
	}
}

void DrawUtil::drawLowResolutionFullscreenEffect( BITMAP* aBuffer, BITMAP* aSrc, float aAmount )
{
	if (aBuffer->w != 320 && aBuffer->h != 240)
		throw std::string("Only 320x240 buffers are allowed!");

	if (!myDrawLowResolutionBuffer)
		myDrawLowResolutionBuffer = create_bitmap(320, 240);

	int w = 20 * aAmount + (1.0f - aAmount) * aSrc->w;
	int h = 15 * aAmount + (1.0f - aAmount) * aSrc->h;

	stretch_blit(aSrc, myDrawLowResolutionBuffer, 0, 0, aSrc->w, aSrc->h, 0, 0, w, h);
	stretch_blit(myDrawLowResolutionBuffer, aBuffer, 0, 0, w, h, 0, 0, 320, 240);
}
