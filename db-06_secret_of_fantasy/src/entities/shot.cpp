#include "entities/shot.hpp"
#include "room.hpp"

Shot::Shot(Entity::Type type,
		   Entity::Type killType,
		   int x, 
		   int y, 
		   int dx, 
		   int dy, 
		   int framesToLive,
		   const std::string& animation,
		   int animationFrames,
		   int damage,
		   Entity::Direction direction)
:Entity(type, 0, 0, 0, 0, true, 0),
mDX(dx), 
mDY(dy),
mAnimation(animation, animationFrames),
mFramesToLive(framesToLive),
mKillType(killType),
mDamage(damage),
mDirection(direction)
{
	mX = x - mAnimation.getFrameWidth() / 2;
	mY = y - mAnimation.getFrameHeight() / 2;
	mW = mAnimation.getFrameWidth();
	mH = mAnimation.getFrameHeight();
	mDamagePerformed = false;
}
	
void Shot::logic()
{
	if (mDamagePerformed)
		return;

	mFramesToLive--;
	mX += mDX;
	mY += mDY;

	std::vector<Entity*> toKill = mRoom->collidesWith(this, mKillType, 0);
	for (unsigned int i = 0; i < toKill.size(); i++)
	{
		toKill[i]->damage(mDamage, mDirection);
		mDamagePerformed = true;
		break;
	}
}

bool Shot::isToBeDeleted()
{
	return mFramesToLive < 0 || mDamagePerformed;
}

void Shot::drawForeground(BITMAP *dest, int scrollx, int scrolly)
{
	mAnimation.drawFrame(dest, 
						 mFramesToLive, 
						 mX - scrollx, 
						 mY - scrolly);
}