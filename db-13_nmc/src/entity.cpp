#include <allegro.h>

#include "entity.hpp"
#include "tilemap.hpp"
#include "room.hpp"

namespace nmc
{
	Entity::Entity(bool collidable, bool solid)
	: mX(0),
	  mY(0),
	  mW(0),
	  mH(0),
	  mCollidable(collidable),
	  mSolid(solid)
	{
	}

	Entity::Entity(int x, int y, int w, int h, bool collidable, bool solid)
	 : mX(x),
	   mY(y),
	   mW(w),
	   mH(h),
	   mCollidable(collidable),
	   mSolid(solid)
	{
	}

	void Entity::setSize(int w, int h)
	{
		mW = w;
		mH = h;
	}

	void Entity::setPosition(int x, int y)
	{
		mX = x;
		mY = y;
	}

	int Entity::getX()
	{
		return mX;
	}

	int Entity::getY()
	{
		return mY;
	}

	int Entity::getWidth()
	{
		return mW;
	}

	int Entity::getHeight()
	{
		return mH;
	}

	void Entity::setX(int x)
	{
		mX = x;
	}

	void Entity::setY(int y)
	{
		mY = y;
	}

	void Entity::setWidth(int w)
	{
		mW = w;
	}

	void Entity::setHeight(int h)
	{
		mH = h;
	}

	int Entity::getCenterX()
	{
		return mX + mW / 2;
	}

	int Entity::getCenterY()
	{
		return mY + mH / 2;
	}

	bool Entity::collidesWith(Entity *other, bool proximityDetection)
	{
        if (other == this)
        {
            return false;
        }

        int ax1 = mX, ay1 = mY,
			ax2 = mX + mW, ay2 = mY + mH;
		int bx1 = other->mX, by1 = other->mY,
			bx2 = other->mX + other->mW, by2 = other->mY + other->mH;

        if (proximityDetection)
        {
            ay2++;
        }

		return ax1 < bx2 && ay1 < by2 && bx1 < ax2 && by1 < ay2;
	}

	bool Entity::solidAbove(Room* room, int& offset)
	{
		int minX = mX / 16;
		int maxX = (mX + mW - 1) / 16;
		int x;
		int y = mY / 16;
		for (x = minX; x <= maxX; x++)
		{
            if (room->getTileMap()->isSolid(x, y))
			{
                offset = y * 16 + 16 - mY;
	 	        return true;
			}
		}

        std::list<Entity*> entities = room->getEntityList();
        std::list<Entity*>::iterator it;
        for (it = entities.begin(); it != entities.end(); it++)
        {
            Entity* entity = (*it);

            if (entity->isSolid() && collidesWith(entity))
            {
                if (mY < entity->getY() + entity->getHeight())
                {
                    offset = entity->getY() + entity->getHeight() - mY;
                    return true;
                }
            }
        }

		return false;
	}

	bool Entity::solidBelow(Room *room, int& offset)
	{
		int minX = mX / 16;
		int maxX = (mX + mW - 1) / 16;
		int x;
		int y = (mY + mH) / 16;
		for (x = minX; x <= maxX; x++)
		{
			if (room->getTileMap()->isSolid(x, y))
            {
                offset = mY + mH - y * 16;
				return true;
			}
		}

        std::list<Entity*> entities = room->getEntityList();
        std::list<Entity*>::iterator it;
        for (it = entities.begin(); it != entities.end(); it++)
        {
            Entity* entity = (*it);

            if (entity->isSolid() && collidesWith(entity, true))
            {
                if (mY + mH < entity->getY() + entity->getHeight())
                {
                    offset = mY + mH - entity->getY();
                    return true;
                }
            }
        }

		return false;
	}

	bool Entity::platformBelow(Room *room, int& offset)
	{
		if ((mY + mW) % 16 > 8) 
        {
			return false;
		}

		int minX = mX / 16;
		int maxX = (mX + mW - 1) / 16;
		int x;
		int y = (mY + mH) / 16;

		for (x = minX; x <= maxX; x++)
		{
			if (room->getTileMap()->isPlatform(x, y))
			{
                offset = mY + mH - y * 16;
				return true;
			}
		}

		return false;
	}

	bool Entity::solidLeft(Room *room, int& offset)
	{
		int minY = mY / 16;
		int maxY = (mY + mH - 1) / 16;
		int x = mX / 16;
		int y;

		for (y = minY; y <= maxY; y++)
		{
			if (room->getTileMap()->isSolid(x, y))
			{
                offset =  x * 16 + 16 - mX;
				return true;
			}
		}

        std::list<Entity*> entities = room->getEntityList();
        std::list<Entity*>::iterator it;
        for (it = entities.begin(); it != entities.end(); it++)
        {
            Entity* entity = (*it);

            if (entity->isSolid() && collidesWith(entity))
            {
                if (mX < entity->getX() + entity->getWidth())
                {
                    offset = entity->getX() + entity->getWidth() - mX;
                    return true;
                }
            }
        }

		return false;
	}

	bool Entity::solidRight(Room *room, int& offset)
	{
		int minY = mY / 16;
		int maxY = (mY + mH - 1) / 16;
		int x = (mX + mW - 1) / 16;
		int y;
		for (y = minY; y <= maxY; y++)
		{
			if (room->getTileMap()->isSolid(x, y))
			{
                offset = mX + mW - x * 16;
				return true;
			}
		}

        std::list<Entity*> entities = room->getEntityList();
        std::list<Entity*>::iterator it;
        for (it = entities.begin(); it != entities.end(); it++)
        {
            Entity* entity = (*it);

            if (entity->isSolid() && collidesWith(entity))
            {
                if (mX + mW > entity->getX())
                {
                    offset = mX + mW - entity->getX();
                    return true;
                }
            }
        }

		return false;
	}

	bool Entity::isSolid()
	{
		return mSolid;
	}

	bool Entity::isCollidable()
	{
		return mCollidable;
	}

	void Entity::handleCollision(Entity *other, Room *room)
	{
	}
}