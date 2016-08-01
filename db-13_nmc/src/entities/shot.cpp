#include "entities/shot.hpp"
#include "room.hpp"
#include "entities/shootableentity.hpp"
#include "entities/enemy.hpp"

namespace nmc
{
	Shot::Shot(int x, int y, const std::string &filename, const std::string &hitFilename, int size, int dx, int dy, int ttl, bool friendly) :
		Entity(x, y, size, size, true),
		mAnimation(filename),
		mHitFilename(hitFilename),
		mTargetDX(dx),
		mTargetDY(dy),
		mTTL(ttl),
		mFriendly(friendly),
		mDX(0),
		mDY(0),
        mFrameCounter(0)
	{
	}
	
	void Shot::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
	{

		int frame = mTTL / 2;
		int x = mX + mW / 2 - mAnimation.getFrameWidth() / 2 - scrollx;
		int y = mY + mH / 2 - mAnimation.getFrameHeight() / 2 - scrolly;
		mAnimation.drawFrame(dest, frame, x, y, mDX < 0);

		//rect(dest, mX -scrollx, mY - scrolly, mX -scrollx + mW - 1, mY - scrolly + mH - 1, makecol(255,100,155));
	}

	AnimatedEntity *Shot::createHit()
	{
		int x = mX + mW / 2 - mAnimation.getFrameWidth() / 2;
		int y = mY + mH / 2 - mAnimation.getFrameHeight() / 2;
		return new AnimatedEntity(x, y, mHitFilename, 2, Entity::FOREGROUND_LAYER, true);
	}

	void Shot::logic(Room *room)
	{
        mFrameCounter++;

        int temp;

		if (mDX < mTargetDX)
		{
			mDX++;
		}

		if (mDX > mTargetDX)
		{
			mDX--;
		}

		if (mDY < mTargetDY)
		{
			mDY++;
		}

		if (mDY > mTargetDY)
		{
			mDY--;
		}

		if ((mDX < 0 && solidLeft(room, temp)) ||
			(mDX > 0 && solidRight(room, temp)) ||
			(mDY < 0 && solidAbove(room, temp)) ||
			(mDY > 0 && solidBelow(room, temp)))
		{
			mTTL = 0;
			room->addEntity(createHit());
		}

		mX += mDX;
		mY += mDY;
		mTTL--;

		int sx = room->getCamera()->getX();
		int sy = room->getCamera()->getY();

		if (mX - sx + mW < 0 ||
			mY - sy + mH < 0 ||
			mX - sx > 320 ||
			mY - sy > 240) {
			mTTL = 0;
		}
	}

	bool Shot::isToBeDeleted()
	{
		return mTTL <= 0;
	}

	int Shot::getDX() {
		return mDX;
	}

	int Shot::getDY() {
		return mDY;
	}

	void Shot::handleCollision(Entity *other, Room *room) {
		if (isToBeDeleted()) {
			return;
		}

		if (mFriendly)
		{
			ShootableEntity *enemy = dynamic_cast<ShootableEntity *>(other);

			if (enemy != NULL) {
				enemy->damage(this, 1);
				room->addEntity(createHit());
				mTTL = 0;
			}
		}
	}
}