#include "entities/shootabletile.hpp"
#include "room.hpp"

namespace nmc
{
	ShootableTile::ShootableTile(int x, int y) :
		ShootableEntity(x, y, 16, 16, true),
		mShot(false),
		mCounter(-1),
		mSprite("breakingtile.bmp")
	{

	}
		
	ShootableTile::~ShootableTile()
    {
	}

	void ShootableTile::damage(Shot *s, int amount)
	{
		mShot = true;
		mCollidable = false;
	}

	void ShootableTile::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
	{
		if (mCounter > 0) {
			mSprite.drawFrame(dest, (8 - mCounter) / 2, mX - scrollx, mY - scrolly);
		}
	}

	void ShootableTile::logic(Room *room)
	{
		if (mCounter > 0) {
			mCounter--;
		}

		if (mShot && mCounter == -1)
		{
            mTile = room->getTileMap()->getTile(mX / 16, mY / 16);
			room->getTileMap()->setTile(mX / 16, mY / 16, 0);
            mTileFlags = room->getTileMap()->getTileFlags(mX / 16, mY / 16);
			room->getTileMap()->setTileFlags(mX / 16, mY / 16, 0);
			mCounter = 7;
		}
	}

	bool ShootableTile::isToBeDeleted()
	{
		return false;
	}
}