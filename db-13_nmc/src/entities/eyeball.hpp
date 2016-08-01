#ifndef NMC_EYEBALL_HPP
#define NMC_EYEBALL_HPP

#include <allegro.h>

#include "enemy.hpp"
#include "animation.hpp"

namespace nmc
{
	class EyeBall : public Enemy
	{
	public:
		EyeBall(int x, int y);
		
		virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

		virtual void enemyLogic(Room *room);

		virtual bool isToBeDeleted();

		virtual void damage(Shot *s, int amount);

	protected:
		Animation mSprite;
		int mFrame;
		int mHealth;
		bool mFacingRight;
		bool mPursuing;
		float mDX, mDY, mFX, mFY;
	};
}

#endif