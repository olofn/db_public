#include "Precompiled.hpp"

#include "Tile.hpp"

Tile::Tile( BITMAP* aTilemap, int aX, int aY, int aH, int aW ) : mTilemap(aTilemap)
, mX(aX)
, mY(aY)
, mW(aW)
, mH(aH)
, mCollide(false)
, mDangerous(false)
{

}

Tile::Tile() : mTilemap(NULL)
, mX(0)
, mY(0)
, mW(0)
, mH(0)
, mCollide(false)
, mDangerous(false)
{

}

void Tile::onDraw( BITMAP* aBuffer, int aX, int aY )
{
	if (!mTilemap)
	{
		return;
	}

	masked_blit(
		mTilemap, 
		aBuffer,
		mX,
		mY,
		aX, 
		aY,
		mW, 
		mH);
}

int Tile::getWidth()
{
	return mW;
}

int Tile::getHeight()
{
	return mH;
}

void Tile::setCollide( bool aCollide )
{
	mCollide = aCollide;
}

bool Tile::getCollide()
{
	return mCollide;
}

void Tile::setDangerous(bool aDangerous)
{
	mDangerous = aDangerous;
}

bool Tile::getDangerous()
{
	return mDangerous;
}