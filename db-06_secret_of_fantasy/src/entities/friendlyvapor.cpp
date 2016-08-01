#include "entities/friendlyvapor.hpp"

FriendlyVapor::FriendlyVapor(int x, int y)
:NormalActor("vapor",
			 ENEMY,
			 x, 
		     y, 
		     14, 
		     10, 
		     true),
 mSwingSidewaysAnimation("graphics/vaporswingsideways.bmp", 1),
 mSwingDownAnimation("graphics/vaporswingdownwards.bmp", 1),
 mSwingUpAnimation("graphics/vaporswingupwards.bmp", 1),
 mHurtAnimation("graphics/vaporhurt.bmp", 1)
{
	mHealth = 100;
	setState("standdown");
	addState("warmupforshot", &mWalkDownwardsAnimation, 0, 0, 0, DOWN, false, false);
	addState("teleport", &mWalkDownwardsAnimation, 0, 0, 0, DOWN, false, false);
	addState("hurt", &mHurtAnimation, 0, 0, 0, DOWN, false, false);
}

void FriendlyVapor::logic()
{
	Actor::move();
}