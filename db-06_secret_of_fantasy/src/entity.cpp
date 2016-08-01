#include <allegro.h>
#include <cmath>
#include "entity.hpp"
#include "util.hpp"
#include "tilemap.hpp"

Entity::Entity(Entity::Type type, bool collidable, int level)
: mType(type),
  mX(0),
  mY(0),
  mW(0),
  mH(0),
  mCollidable(collidable),
  mLevel(level)
{
}

Entity::Entity(Entity::Type type, int x, int y, int w, int h, bool collidable, int level)
 : mType(type),
   mX(x),
   mY(y),
   mW(w),
   mH(h),
   mCollidable(collidable),
   mLevel(level)
{
}

void Entity::setMaxHealth(int maxHealth)
{
	if (maxHealth > 16) 
	{
		maxHealth = 16; 
	}	
	mMaxHealth = maxHealth;
}

void Entity::setHealth(int health)
{
   if (health > mMaxHealth) 
	{ 
		mHealth = mMaxHealth; 
		return;
	} 
	mHealth = health;
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

int Entity::getBottomY()
{
	return mY + mH - 1;
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

bool Entity::collidesWith(Entity *other, int padding)
{
    if (other == this || !isCollidable() || !other->isCollidable())
    {
        return false;
    }

    int ax1 = mX, ay1 = mY,
		ax2 = mX + mW, ay2 = mY + mH;
	int bx1 = other->mX - padding, by1 = other->mY - padding,
		bx2 = other->mX + other->mW + padding, by2 = other->mY + other->mH + padding;

	return ax1 < bx2 && ay1 < by2 && bx1 < ax2 && by1 < ay2;
}

int Entity::getDistance(Entity* other)
{
	double dist = sqrt((double)((getCenterX()-other->getCenterX())*(getCenterX()-other->getCenterX()) + (getCenterY()-other->getCenterY())*(getCenterY()-other->getCenterY())));
	return dist;
}

bool Entity::isCollidable()
{
	return mCollidable;
}

void Entity::handleCollision(Entity *other)
{
}

int Entity::getXCenterInTile(int x)
{
	return x * TileMap::TILE_SIZE + 8;
}

int Entity::getYCenterInTile(int y)
{
	return y * TileMap::TILE_SIZE + 8;
}

int Entity::getYBottomInTile(int y)
{
	return y * TileMap::TILE_SIZE + 15;
}

int Entity::getXInTile(int x)
{
	return x * TileMap::TILE_SIZE;
}

int Entity::getYInTile(int y)
{
	return y * TileMap::TILE_SIZE;
}