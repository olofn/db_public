#include "entity.hpp"
#include "entities/candelabra.hpp"
#include "blending.hpp"

namespace nmc
{
	Candelabra::Candelabra(int x, int y) : AnimatedEntity(x, y, "candle.bmp", 8)
	{
	}

	bool Candelabra::drawInLayer(unsigned int layer)
	{
		return layer == PLAYER_LAYER || layer == FOREGROUND_LAYER;
	}

	void Candelabra::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
	{
		if (layer == PLAYER_LAYER) 
		{
			AnimatedEntity::draw(dest, scrollx, scrolly, layer);
		} 
		else
		{
			int phase = mFrameCounter % 20;
			if (phase > 10) {
				phase = 20 - phase;
			}
			int x = mX - scrollx + mAnimation.getFrameWidth() / 2;
			int y = mY - scrolly + 4;
			int c = makecol(80 + (10 - phase) * 3, 50 + (10 - phase) * 3, 0);
			int r = 4 + phase / 4;
			setAddBlender();
			drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
			circlefill(dest, x, y-2, r, c);
			circlefill(dest, x-8, y-1, r, c);
			circlefill(dest, x-16, y+1, r, c);
			circlefill(dest, x+7, y-1, r, c);
			circlefill(dest, x+15, y+1, r, c);
			drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
		}
	}
}