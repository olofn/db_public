#ifndef NMC_SAVEPOINT_HPP
#define NMC_SAVEPOINT_HPP

#include "entity.hpp"
#include "animation.hpp"

#include <list>

namespace nmc
{
	class SavePoint : public Entity
	{
	public:
		SavePoint(int x, int y);

		virtual ~SavePoint();

		virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

		virtual void logic(Room *room);

		virtual bool isToBeDeleted();

		virtual void handleCollision(Entity *other, Room* room);
    protected:
        bool mTriggered;
        bool mDialogShown;
		bool mKeysDisabled;

		int mFrame;

		class Particle {
		public:
			Particle(float x_, float speed_) : x(x_), y(16), time(0), speed(speed_) { }
			float x, y, speed;
			int time;
		};

		std::list<Particle> mParticles;
		Animation mSprite;
	};
}

#endif