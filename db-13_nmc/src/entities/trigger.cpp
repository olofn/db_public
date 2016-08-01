#include "entities/trigger.hpp"
#include "room.hpp"

namespace nmc
{
    Trigger::Trigger(Entity* entity, int x, int y, int width, int height, bool freezePlayer)
        :Entity(x, y, width, height, true),
         mEntity(entity),
         mTriggered(false),
         mToBeDeleted(false),
         mFreezePlayer(freezePlayer)
    {

    }
    
    void Trigger::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
    {
		//rect(dest, mX -scrollx, mY - scrolly, mX -scrollx + mW - 1, mY - scrolly + mH - 1, makecol(255,100,155));
    }

	void Trigger::initialize(Room *room)
	{			
		while (!room->getTileMap()->isSolid(mX/16, (mY - 16)/16) && mY > 0)
		{
			mY -= 16;
		}

		while (!room->getTileMap()->isSolid(mX / 16, (mY + mH + 15) / 16) &&
			   (mY + mH - 1) / 16 < room->getTileMap()->getHeight())
		{
			mH += 16;
		}
	}

    void Trigger::logic(Room *room)
    {
        if (mTriggered 
            && !mToBeDeleted
            && room->getPlayer()->getState() == Player::GROUND)
        {
            room->addEntity(mEntity);
            mToBeDeleted = true;
        }
    }

    bool Trigger::isToBeDeleted()
    {
        return mToBeDeleted;
    }

    void Trigger::handleCollision(Entity *other, Room *room)
    {
		if (other == room->getPlayer())
        {
            if (mFreezePlayer)
            {
                room->setKeysDisabled(true);
            }
            mTriggered = true;
        }
    }
}