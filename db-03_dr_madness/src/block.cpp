#include <iostream>

#include "block.hpp"
#include "level.hpp"
#include "gamestate.hpp"
#include "energyorb.hpp"


Block::Block(int x, int y, int width, int height, const std::string& filename, int hitCount, bool withOrb)
: Entity(x, y, width, height, true),
  mToBeDeleted(false),
  mHitCount(hitCount * 3),
  mFrameCounter(0),
  mWithOrb(withOrb)
{
    mAnimation = new Animation(filename);
	mIsHit = false;
}

Block::~Block()
{
    delete mAnimation;
}

void Block::logic(Level* level)
{
	if((getY() - level->getScrollY()) + getHeight() < 0)
	{
		mToBeDeleted = true;
	}

    mFrameCounter++;
}

void Block::handleCollision(Entity *other, Level *level)
{
    if (other->getType() == Entity::PLAYER_TYPE)
    {
        level->getPlayer()->kill();

        // Only vulnerable block should not be deleted
        // and spawn debri.
        if (mHitCount - 1 >= 0)
        {
            level->spawnDebris(3, mX, mY, mW, mH);

			if (mWithOrb && !mToBeDeleted)
			{
				level->addEntity(new EnergyOrb(mX, mY));
			}

			mToBeDeleted = true;
        }

        return;
    }

    // Invulnerable block should not be effected by other entities
    // then the player
    if (mHitCount - 1 < 0)
    {
        return;
    }

	if(other->getType() == Entity::PLAYER_BULLET_TYPE)
	{
		mHitCount -= other->getDamage();
		mIsHit = true;
		if(mHitCount <= 0)
		{
			GameState::getInstance()->addPoints(20);
			level->addDestroyedBlocks(1);
			level->spawnDebris(3, mX, mY, mW, mH);

			if (mWithOrb && !mToBeDeleted)
			{
				level->addEntity(new EnergyOrb(mX, mY));
			}

			mToBeDeleted = true;
		}
	}
}

void Block::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
	if(mIsHit)
	{
		int x2 = getX() + getWidth() - 1;
		int y2 = getY()-scrolly + getHeight() - 1;
		rectfill(dest, getX(), getY()-scrolly, x2, y2, makecol(255, 255, 255));
		mIsHit = false;
	}
	else
	{
		if (mHitCount < 0)
		{
			mAnimation->drawFrame(dest, mFrameCounter / 5, getX(), getY() - scrolly);
		}
		else
		{
			int frame = ((mHitCount + 2) / 3) - 1;
			if (frame >= mAnimation->getFrameCount())
			{
				frame = mAnimation->getFrameCount() - 1;
			}

			mAnimation->drawFrame(dest, frame, getX(), getY() - scrolly);
		}
	}
}

bool Block::isToBeDeleted()
{
    return mToBeDeleted && !mIsHit;
}