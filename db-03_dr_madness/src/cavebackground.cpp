#include <cmath>

#include "cavebackground.hpp"
#include "util.hpp"

CaveBackground::CaveBackground() :
	Entity(false),
	mAnimation("cavebackground.bmp", 1)
{
}

CaveBackground::~CaveBackground()
{
}

void CaveBackground::logic(Level* level)
{
}

void CaveBackground::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	float t = std::sin(scrolly * 0.05f) * 0.5f + 0.5f;
	int c = makecol(t * 100, t * 40, t * 10);
	clear_to_color(dest, c);
	mAnimation.drawFrame(dest, 0, 0, mod(-scrolly * 2, 240));
	mAnimation.drawFrame(dest, 0, 0, mod(-scrolly * 2, 240) - 240);
}