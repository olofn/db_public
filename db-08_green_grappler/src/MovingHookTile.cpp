#include "Precompiled.hpp"
#include "MovingHookTile.hpp"
#include "Room.hpp"
#include "Hero.hpp"

MovingHookTile::MovingHookTile()
	: mSprite("data/images/movinghooktile.bmp", 2)
	, hasHook(false)
{
	setSize(float2(mSprite.getFrameHeight(), mSprite.getFrameHeight()));
	mVelocity = float2(20.0f, 0.0f);
}

void MovingHookTile::setRoom(Room *room)
{
	mInitialPosition = mPosition;
	mInitialVelocity = mVelocity;
	Entity::setRoom(room);
}

void MovingHookTile::onRespawn()
{
	mPosition = mInitialPosition;
	mVelocity = mInitialVelocity;
	hasHook = false;
}

void MovingHookTile::update()
{
	Entity::update();
	
	hasHook = (mRoom->getHero()->getHookedEntity() == this);

	if (hasHook) {
		mVelocity.x = (mVelocity.x > 0) ? 40.0f : -40.0f;
		mFrameCounter++;
	} else {
		mVelocity.x = (mVelocity.x > 0) ? 20.0f : -20.0f;
	}

	unsigned int bumps = moveWithCollision();

	if ((bumps & (Direction_Left | Direction_Right)) != 0) {
		mVelocity.x = -mVelocity.x;
	}
}

void MovingHookTile::draw(BITMAP *buffer, int offsetX, int offsetY, int layer)
{
	int x = getDrawPositionX() + offsetX - mSprite.getFrameWidth() / 2;
	int y = getDrawPositionY() + offsetY - mSprite.getFrameHeight() / 2;
	mSprite.drawFrame(buffer, mFrameCounter / 12, x, y);
}

bool MovingHookTile::isHookable()
{
	return true;
}