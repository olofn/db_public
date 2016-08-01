#ifndef SH09_TILEMAP_HPP
#define SH09_TILEMAP_HPP

#include <allegro.h>
#include <string>

class Animation;

class TileMap
{
public:
	static const int TILE_SIZE = 16;
	static const int FLAG_SOLID = 1;

	TileMap(int w, int h);

	~TileMap();

	int getWidth() const;

	int getHeight() const;

	int getTile(int x, int y) const;

	void setTile(int x, int y, int tile);

	int getFlags(int x, int y) const;

	void setFlags(int x, int y, int flag);

	bool isSolid(int x, int y) const;

	void clear(int tile, int flag);

	void draw(BITMAP *dest, const Animation &tileSet, int tileRow, int scrollX, int scrollY) const;

	std::string toString();

protected:
	int width, height;
	int *tiles;
	int *flags;
};

#endif