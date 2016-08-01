#include "entities/iceshot.hpp"
#include "entities/enemy.hpp"
#include "room.hpp"

namespace nmc
{
    IceShot::IceShot(int x, 
                     int y, 
                     const std::string &filename, 
                     const std::string &hitFilename, 
                     int size, 
                     int dx, 
                     int dy, 
                     int ttl, 
                     bool friendly)
                     : Shot(x, y, filename, hitFilename, size, dx, dy, ttl, friendly)
    {}

    void IceShot::handleCollision(Entity *other, Room *room)
    {
        if (isToBeDeleted()) 
        {
			return;
		}

		if (mFriendly)
		{			
			ShootableEntity *entity = dynamic_cast<ShootableEntity *>(other);
			Enemy *enemy = dynamic_cast<Enemy *>(other);

			if (enemy != NULL) 
            {
				enemy->freeze();
				room->addEntity(createHit());
				mTTL = 0;
			}
			else if (entity != NULL) 
			{
				entity->damage(this, 1);

				room->addEntity(createHit());
				mTTL = 0;
			}			
		}
    }
}