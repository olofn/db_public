#include "swoosh.hpp"
#include "actor.hpp"
#include "room.hpp"
#include "random.hpp"

Swoosh::Swoosh(int x, int y, Entity::Direction direction, int delay_, int offset_, int damageMin, int damageMax)
: Entity(OTHER, true),
	mAnimationLeft("graphics/swooshleft.bmp", 3),
	mAnimationUp("graphics/swooshup.bmp", 3),
	direction(direction),
	frame(0),
	delay(delay_),
	offset(offset_),
	mDamageMin(damageMin),
	mDamageMax(damageMax)
{
	if (direction == Actor::UP || direction == Actor::DOWN)
	{
		setWidth(32);
		setHeight(10);
		setX(x - 16);
		setY(y - 5);
	}
	else
	{
		setWidth(10);
		setHeight(32);
		setX(x - 5);
		setY(y - 16);
	}

	int dist = 14;

	switch(direction)
	{
	case Actor::LEFT:
		mX -= dist + 2 + offset;
		break;
	case Actor::RIGHT:
		mX += dist + 2 + offset;
		break;
	case Actor::UP:
		mY -= dist + offset;
		break;
	case Actor::DOWN:
		mY += dist + offset;
		break;
	}
}

void Swoosh::logic()
{
	if (delay > 0)
	{
		delay--;
		return;
	}
	frame++;
	
	if (frame == 1)
	{
		std::vector<Entity *> enemies = mRoom->collidesWith(this, ENEMY, 0);
		
		for(int i = 0; i < (int)enemies.size(); i++)
		{
			enemies[i]->damage(Random::get().getInt(mDamageMin, mDamageMax), direction);
		}			
	}
}

void Swoosh::draw(BITMAP *dest, int scrollx, int scrolly)
{
	if (delay > 0)
		return;

	switch(direction)
	{
	case Actor::LEFT:
		mAnimationLeft.drawFrame(dest, frame, getX() - scrollx, getY() - scrolly, false, true);
		break;
	case Actor::RIGHT:
		mAnimationLeft.drawFrame(dest, frame, getX() - scrollx, getY() - scrolly, true, false);
		break;
	case Actor::UP:
		mAnimationUp.drawFrame(dest, frame, getX() - scrollx, getY() - scrolly, true, false);
		break;
	case Actor::DOWN:
		mAnimationUp.drawFrame(dest, frame, getX() - scrollx, getY() - scrolly, false, true);
		break;
	};
}

bool Swoosh::isToBeDeleted()
{
	return frame >= mAnimationLeft.getFrameCount();
}