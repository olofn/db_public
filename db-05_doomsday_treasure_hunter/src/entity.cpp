#include <allegro.h>

#include "entity.hpp"
#include "util.hpp"

Entity::Entity(bool collidable)
: mX(0),
  mY(0),
  mW(0),
  mH(0),
  mCollidable(collidable)
{
}

Entity::Entity(int x, int y, int w, int h, bool collidable)
 : mX(x),
   mY(y),
   mW(w),
   mH(h),
   mCollidable(collidable)
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

bool Entity::collidesWith(Entity *other)
{
    if (other == this || !isCollidable() || !other->isCollidable())
    {
        return false;
    }

    int ax1 = mX, ay1 = mY,
		ax2 = mX + mW, ay2 = mY + mH;
	int bx1 = other->mX, by1 = other->mY,
		bx2 = other->mX + other->mW, by2 = other->mY + other->mH;

	return ax1 < bx2 && ay1 < by2 && bx1 < ax2 && by1 < ay2;
}

bool Entity::isCollidable()
{
	return mCollidable;
}

void Entity::handleCollision(Entity *other, Level *level)
{
}
