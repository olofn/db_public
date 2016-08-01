#include "tilealignedentity.hpp"
#include "room.hpp"
#include "tilemap.hpp"

TileAlignedEntity::TileAlignedEntity(Entity::Type type, int x, int y, bool collidable)
:Entity(type, 
		x - x % TileMap::TILE_SIZE, 
		y - y % TileMap::TILE_SIZE, 
		16, 
		16, 
		collidable)
{
}