#include "vulcano.hpp"
#include "debris.hpp"
#include "util.hpp"
#include "level.hpp"

Vulcano::Vulcano(int x, int y) :
	Entity(x, y, 0, 0, false),
	mAnimation("vulcano.bmp", 2)
{
}
	
void Vulcano::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	mAnimation.drawFrame(dest, layer == BACKGROUND_LAYER ? 0 : 1, mX, mY - scrolly);
}

void Vulcano::logic(Level *level)
{
	Debris *d = new Debris(mX + 74 + rand() % 84,
						   mY + 20 + rand() % 60,
						   (frand() - 0.5f) * 5.0f,
						   (frand() - 0.5f) * 10.0f,
						   rand() & 1 ? "bubble.bmp" : "bubblesmall.bmp", 
						   2);
	level->addEntity(d);
}