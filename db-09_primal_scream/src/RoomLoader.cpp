#include "Precompiled.hpp"

#include "RoomLoader.hpp"
#include "Resource.hpp"
#include "Entity.hpp"

#include "Tmx.h"
#include "Tile.hpp"
#include "Layer.hpp"
#include "Camera.hpp"
#include "EntityFactory.hpp"

Tmx::Map RoomLoader::map;

void RoomLoader::Initialize()
{
	map.ParseFile("data/map/map.tmx");

	if (map.HasError()) {
	  //throw std::exception(map.GetErrorText().c_str());
	  throw std::runtime_error(map.GetErrorText().c_str());
	}
}

Tile*
GetTile(
	const Tmx::Map& aMap,
	std::string		aLayerName,
	int				aX,
	int				aY,
	std::map<int, Tile*>& aCache)
{
	const std::vector<Tmx::Layer*> layers = aMap.GetLayers();

	for (unsigned int i = 0; i < layers.size(); i++)
	{
		if (layers[i]->GetName() != aLayerName)
			continue;

		int gid = layers[i]->GetTileGid(aX, aY);

		if (aCache.find(gid) != aCache.end())
			return aCache[gid];

		if (gid == 0)
		{
			aCache[0] = new Tile;
			return new Tile();
		}

		const Tmx::Tileset* tileset = aMap.FindTileset(gid);
		const Tmx::Image* image = tileset->GetImage();

		//Get the image:
		BITMAP* tileMap = Resource::getBitmap(aMap.GetFilepath() + "/" + image->GetSource());

		int relativeGid = gid - tileset->GetFirstGid();

		int tilesWide = image->GetWidth()/tileset->GetTileWidth();
		int tilesHigh = image->GetHeight()/tileset->GetTileHeight();

		int tileX = relativeGid % tilesWide * tileset->GetTileWidth();
		int tileY = relativeGid / tilesWide * tileset->GetTileHeight();	

		Tile* resulttile = new Tile(tileMap, tileX, tileY, tileset->GetTileWidth(), tileset->GetTileHeight());
		
		if (relativeGid < 40)
		{
			resulttile->setCollide(true);
		}
		else if (relativeGid < 50)
		{
			resulttile->setDangerous(true);
		}


		/*const Tmx::Tile* tile = tileset->GetTile(relativeGid);
		if (tile)
		{
			//resulttile->setCollide(tile->GetProperties().GetLiteralProperty("collide") == "true");
			resulttile->setCollide(relativeGid < 50); 
		}*/

		aCache[gid] = resulttile;
		return resulttile;
	}

	return new Tile();
}



Layer*
GetLayer(
	const Tmx::Map& aMap,
	int roomX,
	int roomY,
	int roomW,
	int roomH,
	std::string		aLayerName)
{
	Layer* layer = new Layer(roomW, roomH, aMap.GetTileWidth(), aMap.GetTileHeight());

	std::map<int, Tile*> cache;

	for (int x = 0; x < roomW; x++)
	{
		for (int y = 0; y < roomH; y++)
		{	
			layer->setTile(x, y, *GetTile(aMap, aLayerName, x + roomX, y + roomY, cache));
		}
	}

	return layer;
}

std::vector<Entity*>
GetEntities(
	const Tmx::Map& aMap,
	int roomX,
	int roomY,
	int roomW,
	int roomH,
	std::string		aLayerName)
{

	const std::vector<Tmx::Layer*> layers = aMap.GetLayers();
	Tmx::Layer* layer = 0;

	for (unsigned int i = 0; i < layers.size(); i++)
	{
		if (layers[i]->GetName() == aLayerName)
		{
			layer = layers[i];
			break;
		}
	}

	std::vector<Entity*> entities;

	if (layer == 0) {
		return entities;
	}

	for (int y = 0; y < roomH; y++) {
		for (int x = 0; x < roomW; x++) {
			Tmx::MapTile tile = layer->GetTile(x + roomX, y + roomY);
			const Tmx::Tileset *tileset = aMap.FindTileset(tile.gid);

			if (!tileset) {
				continue;
			}

			int firstGid = tileset->GetFirstGid();
			int entityId = tile.gid - firstGid;

			Entity* entity = EntityFactory::create(entityId);

			if (!entity)
			{
				continue;
			}

			float2 pos(aMap.GetTileWidth() * x + aMap.GetTileWidth() / 2, aMap.GetTileHeight() * (y + 1));
			pos.y -= entity->getHalfSize().y;

			entity->setInitialPosition(pos);
			entities.push_back(entity);
		}
	}

	return entities;
}

Room* 
RoomLoader::LoadRoom( int x, int y )
{
	const Tmx::ObjectGroup *roomObjectGroup = map.GetObjectGroup(0);

	int roomX = -1;
	int roomY = -1;
	int roomW = -1;
	int roomH = -1;

	for (int i = 0; i < roomObjectGroup->GetNumObjects(); i++)
	{
		const Tmx::Object *roomObject = roomObjectGroup->GetObject(i);
		int rX = roomObject->GetX() / 10;
		int rY = roomObject->GetY() / 10;
		int rW = roomObject->GetWidth() / 10;
		int rH = roomObject->GetHeight() / 10;
		if (x >= rX && y >= rY && x < rX + rW && y < rY + rH)
		{
			roomX = rX;
			roomY = rY;
			roomW = rW;
			roomH = rH;
			break;
		}
	}

	if (roomX < 0)
	{
	  //throw std::exception("Found no room at these coordinates");
	  throw std::runtime_error("Found no room at these coordinates");
	}

	Room* room = new Room(GetLayer(map, roomX, roomY, roomW, roomH, "tiles"), roomX, roomY);

	std::vector<Entity*> entities = GetEntities(map, roomX, roomY, roomW, roomH, "entities");

	room->setCamera(new Camera());

	for (unsigned int i = 0; i < entities.size(); i++)
	{
		room->addEntity(entities[i]);
	}

	return room;
}
