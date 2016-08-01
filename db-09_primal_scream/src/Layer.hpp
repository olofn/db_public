#pragma once

#include "Tile.hpp"

class Layer
{
public:
	Layer(
		int aWidth = 0,
		int aHeight = 0,
		int aTileWidth = 10,
		int aTileHeight = 10);

	void setTile(
		int aX,
		int aY,
		Tile aTile);

	Tile &getTile(
		int aX,
		int aY);

	int getWidth();

	int getHeight();

	int getTileWidth();

	int getTileHeight();
private:
	int mWidth;
	int mHeight;
	int mTileWidth;
	int mTileHeight;

	std::vector<Tile> mTiles;
};

