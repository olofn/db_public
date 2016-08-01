#ifndef DB_BAT_HPP
#define DB_BAT_HPP

#include "actor.hpp"

class Bat : public Actor
{
public:
	Bat(int x, int y, int type, int level);

	~Bat();
	
	void logic();

	void damage(int damage, Entity::Direction direction);

	bool isToBeDeleted();

protected:
	Animation mAnimation;
	int stateChangeTimer;
	int mBatType;
};

#endif