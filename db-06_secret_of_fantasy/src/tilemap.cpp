#include <allegro.h>
#include <iostream>

#include "tilemap.hpp"
#include "util.hpp"
#include "exception.hpp"
#include "animation.hpp"

TileMap::TileMap(int w, int h)
{
	width = w;
	height = h;
	tiles = new int[w * h];
	flags = new int[w * h];
}

TileMap::~TileMap()
{
	delete[] tiles;
	delete[] flags;
}

int TileMap::getWidth() const
{
	return width;
}

int TileMap::getHeight() const
{
	return height;
}

int TileMap::getTile(int x, int y) const
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return -1;

	return tiles[x + y * width];
}

void TileMap::setTile(int x, int y, int tile)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
	{
		throw DB_EXCEPTION("Out of bounds");
	}

	tiles[x + y * width] = tile;
}

int TileMap::getFlags(int x, int y) const
{
	if (x < 0 || y < 0 || x >= width || y >= height)
	{
		return -1;
	}
	
	return flags[x + y * width];
}

void TileMap::setFlags(int x, int y, int flag)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
	{
		throw DB_EXCEPTION("Out of bounds");
	}

	flags[x + y * width] = flag;
}

bool TileMap::isSolid(int x, int y) const
{
	return (getFlags(x, y) & FLAG_SOLID) != 0;
}

void TileMap::clear(int tile, int flag)
{
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			setTile(x, y, tile);
			setFlags(x, y, flag);
		}
	}
}

void TileMap::draw(BITMAP *dest, const Animation &tileSet, int tileRow, int scrollX, int scrollY) const
{
	int xStart = scrollX / TILE_SIZE - 1;
	int xEnd = (scrollX + dest->w) / TILE_SIZE + 1;

	for (int tx = xStart; tx <= xEnd; tx++)
	{
		int sx = tx * TILE_SIZE - scrollX;
		int sy = tileRow * TILE_SIZE - scrollY - tileSet.getFrameHeight() + TILE_SIZE;
		int tile = getTile(tx, tileRow);

		if (tile == -1)
			rectfill(dest, sx, sy, sx + 16, sy + 16,makecol(255, 0, 0));
		else
			tileSet.drawFrame(dest, tile, sx, sy);
	}
}

std::string TileMap::toString()
{
	std::string result;

	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			if (isSolid(x, y))
			{
				result += "#";
			}
			else
			{
				result += " ";
			}
		}
		result += "\n";
	}

	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			result += (char)(getTile(x, y) + '0');
		}
		result += "\n";
	}

	return result;
}