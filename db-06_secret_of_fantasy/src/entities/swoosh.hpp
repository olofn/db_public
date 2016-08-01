#ifndef DB_SWOOSH_HPP
#define DB_SWOOSH_HPP

#include "entity.hpp"
#include "animation.hpp"

class Swoosh : public Entity
{
public:
	Swoosh(int x, int y, Entity::Direction direction, int delay, int offset, int damageMin, int damageMax);

	void logic();

	void draw(BITMAP *dest, int scrollx, int scrolly);

	bool isToBeDeleted();

private:
	Animation mAnimationLeft;
	Animation mAnimationUp;
	Entity::Direction direction;
	int frame;
	int delay;
	int offset;
	bool sound;
	int mDamageMin;
	int mDamageMax;
};

#endif