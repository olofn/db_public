#ifndef DB_NORMALACTOR_HPP
#define DB_NORMALACTOR_HPP

#include "actor.hpp"
#include "animation.hpp"

class NormalActor: public Actor
{
public:
	NormalActor(const std::string& name, 
				Entity::Type type,
				int x, 
				int y, 
				int width, 
				int height, 
				bool collidable);
protected:
	Animation mStandAnimation;
	Animation mWalkSidewaysAnimation;
	Animation mWalkDownwardsAnimation;
	Animation mWalkUpwardsAnimation;
};

#endif