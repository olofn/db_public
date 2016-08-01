#ifndef NMC_TELEPORT_HPP
#define NMC_TELEPORT_HPP

#include "entity.hpp"

namespace nmc
{
	class Teleport : public Entity
	{
	public:
		Teleport(int targetRoom, int targetX, int targetY, int x = 0, int y = 0);

		virtual ~Teleport();

		virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

		virtual void logic(Room *room);

		virtual bool isToBeDeleted();

		virtual void handleCollision(Entity *other);
	private:
		int mTargetRoom, mTargetX, mTargetY;

	};
}

#endif