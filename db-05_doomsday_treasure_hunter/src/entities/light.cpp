#include "entities/light.hpp"

#include "blending.hpp"

Light::Light(int x, int y)
:Entity(x, y, 16, 16, true)
{
}

void Light::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
   
    int phase = mFrameCounter % 20;
	
    if (phase > 10) {
		phase = 20 - phase;
	}

	int x = mX - scrollx + getWidth() / 2;
	int y = mY - scrolly + 4;
	int c = makecol(30 + (10 - phase) * 3, 20 + (10 - phase) * 3, 0);
	int r = 4 + phase / 4;

  
    //int c = makecol(20 + (10 - phase) * 3, 30 + (10 - phase) * 3, 0);

   // int x = mX - scrollx + getWidth() / 2;
    //int y = mY - scrolly + getHeight() / 2;
	setAddBlender();
	drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
	circlefill(dest, x, y, getWidth(), c);
    circlefill(dest, x, y, getWidth() / 2, c);
	drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

}

void Light::logic(Level *level)
{
    mFrameCounter++;
}
