#ifndef DB_FRIENDLYVAPOR_HPP
#define DB_FRIENDLYVAPOR_HPP

#include "normalactor.hpp"
#include "animation.hpp"

class FriendlyVapor : public NormalActor
{
public:
	FriendlyVapor(int x, int y);
	void logic();

private:
	Animation mSwingSidewaysAnimation;
	Animation mSwingUpAnimation;
	Animation mSwingDownAnimation;
	Animation mHurtAnimation;
};

#endif