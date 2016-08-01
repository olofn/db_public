#include "entities/normalactor.hpp"

NormalActor::NormalActor(const std::string& name, 
						 Entity::Type type,
						 int x, 
						 int y, 
						 int width, 
						 int height, 
						 bool collidable)
:Actor(type,x, y, width, height, collidable),
	mStandAnimation("graphics/"+name+"stand.bmp"),
	mWalkUpwardsAnimation("graphics/"+name+"walkupwards.bmp", 2),
	mWalkDownwardsAnimation("graphics/"+name+"walkdownwards.bmp", 2),
	mWalkSidewaysAnimation("graphics/"+name+"walksideways.bmp", 2)
{
	addState("standleft", &mStandAnimation, 0, 0, 0, LEFT, false, false);
	addState("standright", &mStandAnimation, 0, 0, 0, RIGHT, true, false);
	addState("standdown", &mWalkDownwardsAnimation, 0, 0, 0, DOWN, false, false);
	addState("standup", &mWalkUpwardsAnimation, 0, 0, 0, UP, false, false);
	addState("walkright", &mWalkSidewaysAnimation, 1, 0, 6, RIGHT, true, false);
	addState("walkleft", &mWalkSidewaysAnimation, -1, 0, 6, LEFT, false, false);
	addState("walkdown", &mWalkDownwardsAnimation, 0, 1, 6, DOWN, false, false);
	addState("walkup", &mWalkUpwardsAnimation, 0, -1, 6, UP, false, false);
}