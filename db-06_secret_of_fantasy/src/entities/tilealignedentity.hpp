#ifndef DB_TILEALIGENDENTITY_HPP
#define DB_TILEALIGENDENTITY_HPP

#include "entity.hpp"

class TileAlignedEntity: public Entity
{
public:
	TileAlignedEntity(Entity::Type type, int x, int y, bool collidable);

};

#endif