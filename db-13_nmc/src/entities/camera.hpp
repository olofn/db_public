#ifndef NMC_CAMERA_HPP
#define NMC_CAMERA_HPP

#include "entity.hpp"
#include "player.hpp"

namespace nmc
{
	class Camera : public Entity
	{
	public:
		Camera();

		~Camera();

		virtual void setTarget(Player *player);

		virtual void moveToTarget(TileMap *tileMap);

		virtual void logic(Room *room);

		virtual void draw(BITMAP *dest, int scrollX, int scrollY, unsigned int layer);

		virtual bool isToBeDeleted();

	protected:
		virtual void clampToMapEdges(TileMap *tileMap);

		Player *mPlayer;
	};
}

#endif