#pragma once

class Animation;

class DrawUtil 
{
public:
	static bool drawDissolveBitmap(BITMAP *aBuffer, BITMAP *src, int x, int y, float amount);
	static void drawGradiant(BITMAP* aBuffer, int x, int y, int width, int height, int startColor, int endColor);
	static bool drawFadeIn(BITMAP* aBuffer, float aAmount);
	static bool drawFadeOut(BITMAP* aBuffer, float aAmount);
	static void drawHeatBitmap(BITMAP* aBuffer, BITMAP* aSrc, int aStartY, int aEndY, float aSpeed);
	static void drawLowResolutionFullscreenEffect(BITMAP* aBuffer, BITMAP* aSrc, float aAmount);

private:
	static const int DissolveHeight = 10;
	static Animation* myFadeAnimation;
	static BITMAP* myDrawLowResolutionBuffer;
	DrawUtil() {};
};