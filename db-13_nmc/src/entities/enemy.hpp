#ifndef NMC_ENEMY_HPP
#define NMC_ENEMY_HPP

#include "entity.hpp"
#include "entities/shootableentity.hpp"
#include "entities/shot.hpp"
#include "animation.hpp"

namespace nmc {
	class Enemy : public ShootableEntity {
	public:
		Enemy(int x, int y, int w, int h, int playerDamage);

		virtual void damage(Shot *s, int amount) = 0;

		virtual void handleCollision(Entity *other, Room *room);

        virtual void freeze();

        virtual void unfreeze();

        virtual bool isFrozen();

        virtual void enemyLogic(Room* room) = 0;

        virtual void logic(Room* room);

        virtual bool isSolid();

		virtual Animation::Blending getBlendMode();

	private:
		int mPlayerDamage;
        int mFreezeCounter;
	};
}

#endif