#include "Precompiled.hpp"
#include "Entity.hpp"
#include "Time.hpp"
#include "Room.hpp"
Entity::Entity()
	: mRemoved(false)
	, mFrameCounter(0)
	, mRoom(0)
{
}

Entity::~Entity()
{
}

void Entity::setPosition(float2 position) { mPosition = position; }
float2 Entity::getPosition() { return mPosition; }

void Entity::setVelocity(float2 velocity) { mVelocity = velocity; }
float2 Entity::getVelocity() { return mVelocity; }

void Entity::setSize(float2 size) { mSize = size; }
float2 Entity::getSize() { return mSize; }
float2 Entity::getHalfSize() { return mSize * 0.5f; };

void Entity::setRoom(Room *room) { mRoom = room; }
Room *Entity::getRoom() { return mRoom; }

unsigned int Entity::moveWithCollision(float2 delta)
{
	int substeps = (int)ceil((abs(delta.x) + abs(delta.y)) * 0.2);
	delta /= substeps;
	unsigned int result = Direction_None;
	float2 halfSize = getHalfSize();

	for (int i = 0; i < substeps; i++) {
		mPosition.x += delta.x;
		int x1 = (int)((mPosition.x - halfSize.x) / mRoom->getTileWidth());
		int x2 = (int)((mPosition.x + halfSize.x) / mRoom->getTileWidth());
		int y1n = (int)((mPosition.y - halfSize.y + 0.01f) / mRoom->getTileHeight());
		int y2n = (int)((mPosition.y + halfSize.y - 0.01f) / mRoom->getTileHeight());

		if (delta.x > 0) {
			for (int y = y1n; y <= y2n; y++) {
				if (mRoom->isCollidable(x2, y)) {
					delta.x = 0;
					result |= Direction_Right;
					mPosition.x = x2 * mRoom->getTileWidth() - halfSize.x;
					break;
				}
			}
		} else if (delta.x < 0) {
			for (int y = y1n; y <= y2n; y++) {
				if (mRoom->isCollidable(x1, y)) {
					delta.x = 0;
					result |= Direction_Left;
					mPosition.x = (x1 + 1) * mRoom->getTileWidth() + halfSize.x;
					break;
				}
			}
		}

		mPosition.y += delta.y;
		int y1 = (int)((mPosition.y - halfSize.y) / mRoom->getTileHeight());
		int y2 = (int)((mPosition.y + halfSize.y) / mRoom->getTileHeight());
		int x1n = (int)((mPosition.x - halfSize.x + 0.01f) / mRoom->getTileWidth());
		int x2n = (int)((mPosition.x + halfSize.x - 0.01f) / mRoom->getTileWidth());
		
		if (delta.y > 0) {
			for (int x = x1n; x <= x2n; x++) {
				if (mRoom->isCollidable(x, y2)) {
					delta.y = 0;
					result |= Direction_Down;
					mPosition.y = y2 * mRoom->getTileHeight() - halfSize.y;
					break;
				}
			}
		} else if (delta.y < 0) {
			for (int x = x1n; x <= x2n; x++) {
				if (mRoom->isCollidable(x, y1)) {
					delta.y = 0;
					result |= Direction_Up;
					mPosition.y = (y1 + 1) * mRoom->getTileHeight() + halfSize.y;
				}
			}
		}
	}

	return result;
}

unsigned int Entity::moveWithCollision()
{
	return moveWithCollision(mVelocity / Time::TicksPerSecond);
}

void Entity::update()
{
	mFrameCounter++;
}

void Entity::draw(BITMAP *buffer, int offsetX, int offsetY, int layer)
{
	int x = getDrawPositionX() + offsetX;
	int y = getDrawPositionY() + offsetY;
	int x1 = (int)(x - getHalfSize().x);
	int y1 = (int)(y - getHalfSize().y);
	int x2 = (int)(x + getHalfSize().x);
	int y2 = (int)(y + getHalfSize().y);
	rect(buffer, x1, y1, x2, y2, makecol(255, 255, 0));
	line(buffer, x - 3, y, x + 3, y, makecol(255, 255, 0));
	line(buffer, x, y - 3, x, y + 3, makecol(255, 255, 0));
	//textout_centre_ex(buffer, font, typeid(this).name(), x, y - 9, makecol(200, 200, 200), 0);
}

void Entity::remove()
{	
	mRemoved = true;
}

bool Entity::isRemoved()
{
	return mRemoved;
}

int
Entity::getDrawPositionX()
{
	return getPosition().x+0.5;
}

int 
Entity::getDrawPositionY()
{
	return getPosition().y+0.5;
}

Entity::CollisionRect 
Entity::getCollisionRect()
{
	CollisionRect collisionRect;
	collisionRect.myTopLeft = getPosition()-getHalfSize();
	collisionRect.myBottomRight = getPosition()+getHalfSize();

	return collisionRect;
}

bool
Entity::Collides( const CollisionRect& aRect1, CollisionRect& aRect2 )
{
	if (aRect1.myBottomRight.x <= aRect2.myTopLeft.x)
		return false;

	if (aRect1.myTopLeft.x >= aRect2.myBottomRight.x)
		return false;

	if (aRect1.myBottomRight.y <= aRect2.myTopLeft.y)
		return false;

	if (aRect1.myTopLeft.y >= aRect2.myBottomRight.y)
		return false;

	return true;
}

bool Entity::isDamagable()
{
	return false;
}

bool Entity::isHookable()
{	
	return false;
}

void Entity::onDamage()
{

}

void Entity::onButtonUp( int aId )
{

}

void Entity::onButtonDown( int aId )
{

}

void Entity::onRespawn()
{

}

void Entity::onStartWallOfDeath()
{
	
}

void Entity::onLevelComplete()
{

}

void Entity::onBossFloorActivate()
{

}

void Entity::onBossWallActivate()
{

}

void Entity::onBossWallDeactivate()
{

}
