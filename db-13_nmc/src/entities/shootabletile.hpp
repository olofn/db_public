#ifndef NMC_SHOOTABLETILE_HPP
#define NMC_SHOOTABLETILE_HPP

#include "entities/shootableentity.hpp"
#include "entities/shot.hpp"
#include "animation.hpp"

namespace nmc
{
	class ShootableTile : public ShootableEntity
	{
	public:		
		ShootableTile(int x, int y);
		
		virtual ~ShootableTile();

		virtual void damage(Shot *s, int amount);

		virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

		virtual void logic(Room *room);

		virtual bool isToBeDeleted();

	protected:
		Animation mSprite;
		bool mShot;
		int mCounter;
        int mTile;
        int mTileFlags;
	};
}

#endif