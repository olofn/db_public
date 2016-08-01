#ifndef DB_VAPOR_HPP
#define DB_VAPOR_HPP

#include "normalactor.hpp"
#include "animation.hpp"

class Vapor : public NormalActor
{
public:
	Vapor(int x, int y);

	void logic();
	bool isToBeDeleted();
	void damage(int damage, Entity::Direction direction);

private:
	void battleLogic();
	void nextState(bool canShoot = false);
	int mStateChangeTimer;
	bool mCanTakeDamage;
	Animation mSwingSidewaysAnimation;
	Animation mSwingUpAnimation;
	Animation mSwingDownAnimation;
	Animation mHurtAnimation;
	bool mDialog;
	bool mEndDialog;
	bool mIsToBeDeleted;
};

#endif