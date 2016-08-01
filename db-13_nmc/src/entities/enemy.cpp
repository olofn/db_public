#include "entities/enemy.hpp"
#include "entities/player.hpp"

namespace nmc {
	Enemy::Enemy(int x, int y, int w, int h, int playerDamage) : 
		ShootableEntity(x, y, w, h, true),
		mPlayerDamage(playerDamage),
        mFreezeCounter(0)
	{ }

	void Enemy::handleCollision(Entity *other, Room *room)
	{
		Player *player = dynamic_cast<Player *>(other);

		if (player != NULL && !isFrozen())
		{
			player->damage(this, mPlayerDamage);
		}
	}

    void Enemy::freeze()
    {
        mFreezeCounter = 250;
    }

    void Enemy::unfreeze()
    {
        mFreezeCounter = 0;
    }

    bool Enemy::isFrozen()
    {
        return mFreezeCounter > 0;
    }

    void Enemy::logic(Room* room)
    {
        if (isFrozen())
        {
            mFreezeCounter--;
        }
        else
        {
            enemyLogic(room);
        }
    }

    bool Enemy::isSolid()
    {
        return isFrozen();
    }

	Animation::Blending Enemy::getBlendMode()
	{
		if (mFreezeCounter > 25)
		{
			return Animation::FROZEN;
		}
		if (mFreezeCounter <= 0)
		{
			return Animation::NONE;
		}

		return mFreezeCounter & 2 ? Animation::FROZEN : Animation::NONE;
	}
}