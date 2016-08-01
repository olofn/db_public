#ifndef DB_PAINTINGCUTSCENE_HPP
#define DB_PAINTINGCUTSCENE_HPP

#include "tilealignedentity.hpp"
#include <string>
#include <vector>

class PaintingCutScene: public TileAlignedEntity
{
public:
	PaintingCutScene(int x, int y);
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly) {}
	void drawForeground(BITMAP *dest, int scrollx, int scrolly);
};
#endif