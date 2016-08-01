#ifndef NMC_SHOT_HPP
#define NMC_SHOT_HPP

#include "entity.hpp"
#include "animation.hpp"
#include "animatedentity.hpp"

namespace nmc {

	class Shot : public Entity {
	public:
		Shot(int x, int y, const std::string &filename, const std::string &hitFilename, int size, int dx, int dy, int ttl, bool friendly);
	
		virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

		virtual void logic(Room *room);

		virtual bool isToBeDeleted();

		virtual void handleCollision(Entity *other, Room *room);

		virtual int getDX();

		virtual int getDY();

	protected:

		virtual AnimatedEntity *createHit();

		int mDX, mDY, mTTL;
		int mTargetDX, mTargetDY;
		bool mFriendly;
		std::string mHitFilename;

		Animation mAnimation;
        int mFrameCounter;
	};
}

#endif