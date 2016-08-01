#ifndef NMC_SHOOTABLEENTITY_HPP
#define NMC_SHOOTABLEENTITY_HPP

#include "entity.hpp"
#include "entities/shot.hpp"

namespace nmc
{
	class ShootableEntity : public Entity
	{
	public:
		ShootableEntity(bool collidable = false, bool solid = false) :
		  Entity(collidable, solid) {}
		
		ShootableEntity(int x, int y, int w = 0, int h = 0, bool collidable = false, bool solid = false) :
		  Entity(x, y, w, h, collidable, solid) {}
		
		virtual ~ShootableEntity() {}		

		virtual void damage(Shot *s, int amount) = 0;
	};
}

#endif