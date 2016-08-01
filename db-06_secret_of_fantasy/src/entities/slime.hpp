#ifndef DB_SLIME_HPP
#define DB_SLIME_HPP

#include "actor.hpp"

class Slime : public Actor
{
public:
	Slime(int x, int y, int type, int level);

	~Slime();
	
	void logic();

	void damage(int damage, Entity::Direction direction);

	bool isToBeDeleted();

protected:
	Animation mAnimation;
	int mSlimeType;
	int stateChangeTimer;
};

#endif