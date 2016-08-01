#include "Layer.hpp"


Layer::Layer( int aWidth, int aHeight, int aTileWidth, int aTileHeight ) : mWidth(aWidth)
, mHeight(aHeight)
, mTileWidth(aTileWidth)
, mTileHeight(aTileHeight)
{
	mTiles.resize(aWidth*aHeight);
}

void Layer::setTile( int aX, int aY, Tile aTile )
{
	mTiles[aX + mWidth*aY] = aTile;
}

Tile& Layer::getTile( int aX, int aY )
{
	aX = clamp(aX, 0, getWidth() - 1);
	aY = clamp(aY, 0, getHeight() - 1);
	
	return mTiles[aX + mWidth * aY];
}

int Layer::getWidth()
{
	return mWidth;
}

int Layer::getHeight()
{
	return mHeight;
}

int Layer::getTileWidth()
{
	return mTileWidth;
}

int Layer::getTileHeight()
{
	return mTileHeight;
}
