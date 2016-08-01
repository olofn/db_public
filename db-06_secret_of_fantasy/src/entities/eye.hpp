#ifndef DB_EYE_HPP
#define DB_EYE_HPP

#include "actor.hpp"

class Eye : public Actor
{
public:
	Eye(int x, int y, int level);

	~Eye();
	
	void logic();

	void damage(int damage, Entity::Direction direction);

	bool isToBeDeleted();

	void nextState();

protected:
	Animation mAnimLeft;
	Animation mAnimRight;
	Animation mAnimUp;
	Animation mAnimDown;
	int mStateChangeTimer;
};

#endif