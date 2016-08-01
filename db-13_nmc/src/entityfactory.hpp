#ifndef NMC_ENTITYFACTORY_HPP
#define NMC_ENTITYFACTORY_HPP

#include <vector>
#include <string>

#include "entity.hpp"

namespace nmc
{
	class EntityFactory
	{	
	public:
		static EntityFactory *getInstance();

		Entity *createEntity(int type, int x, int y);

	private:
		EntityFactory();

		static EntityFactory *mInstance;
	};
}

#endif