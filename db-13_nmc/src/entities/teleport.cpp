#include <allegro.h>
#include "entities/teleport.hpp"
#include "entity.hpp"
#include "entities/player.hpp"
#include "room.hpp"
#include "world.hpp"
#include "gamestatemanager.hpp"

namespace nmc
{
	Teleport::Teleport(int targetRoom, int targetX, int targetY, int x, int y) :
		Entity(x, y, 16, 16, true),
		mTargetRoom(targetRoom),
		mTargetX(targetX),
		mTargetY(targetY)
	{
	}

	Teleport::~Teleport()
	{
	}

	void Teleport::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
	{
		rect(dest, mX - scrollx, mY - scrolly, mX - scrollx + mW - 1, mY - scrolly + mH -1, rand());
	}

	void Teleport::logic(Room *room)
	{
	}

	bool Teleport::isToBeDeleted()
	{
		return false;
	}

	void Teleport::handleCollision(Entity *other)
	{
		Player *player = dynamic_cast<Player *>(other);
		if (player != NULL) {
			int currentRoom = GameStateManager::getInstance()->getCurrent()->getInt("roomNumber");
			World *w = World::getInstance();
			int ox = w->getRoomPosition(mTargetRoom).x - w->getRoomPosition(currentRoom).x;
			int oy = w->getRoomPosition(mTargetRoom).y - w->getRoomPosition(currentRoom).y;
			player->setPosition(ox * 16 + mTargetX, oy * 16 + mTargetY);
		}
	}
}