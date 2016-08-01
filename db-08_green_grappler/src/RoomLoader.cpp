#include "RoomLoader.hpp"
#include "Resource.hpp"
#include "Entity.hpp"

#include "Tmx.h"
#include "Tile.hpp"
#include "Layer.hpp"
#include "Spike.hpp"
#include "Camera.hpp"
#include "EntityFactory.hpp"

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

		const Tmx::Tile* tile = tileset->GetTile(relativeGid);
		if (tile)
		{
			resulttile->setCollide(tile->GetProperties().GetLiteralProperty("collide") == "true");
			resulttile->setHook(tile->GetProperties().GetLiteralProperty("hook") == "true");
		}

		aCache[gid] = resulttile;
		return resulttile;
	}

	return new Tile();
}



Layer*
GetLayer(
	const Tmx::Map& aMap,
	std::string		aLayerName)
{
	Layer* layer = new Layer(aMap.GetWidth(), aMap.GetHeight(), aMap.GetTileWidth(), aMap.GetTileHeight());

	std::map<int, Tile*> cache;

	for (int x = 0; x < aMap.GetWidth(); x++)
	{
		for (int y = 0; y < aMap.GetHeight(); y++)
		{	
			layer->setTile(x, y, *GetTile(aMap, aLayerName, x, y, cache));
		}
	}

	return layer;
}

std::vector<std::pair<float2, float2>>
GetCameraRects(
  const Tmx::Map&	aMap,
  std::string		aObjectGroupName)
{
	std::vector<std::pair<float2, float2>> result;

	const std::vector< Tmx::ObjectGroup* >& objectGroups = aMap.GetObjectGroups();

	for (unsigned int i = 0; i < objectGroups .size(); i++)
	{
		if (objectGroups[i]->GetName() != aObjectGroupName)
			continue;

		const std::vector< Tmx::Object* >& objects = objectGroups[i]->GetObjects();
		for (unsigned int j = 0; j < objects.size(); j++)
		{
			const Tmx::Object* object = objects[j];
			
			float2 topleft(object->GetX(), object->GetY());
			float2 botright = topleft + float2(object->GetWidth(), object->GetHeight());
			std::pair<float2, float2> rect(topleft, botright);

			result.push_back(rect);
		}
	}

	return result;
}

std::vector<Entity*>
GetEntities(
	const Tmx::Map& aMap,
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

	for (int y = 0; y < aMap.GetHeight(); y++) {
		for (int x = 0; x < aMap.GetWidth(); x++) {
			Tmx::MapTile tile = layer->GetTile(x, y);
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

			entity->setPosition(pos);
			entities.push_back(entity);
		}
	}

	return entities;
}

Room* 
RoomLoader::LoadRoom( const std::string& aRoomName )
{
	Tmx::Map map;
	map.ParseFile(aRoomName);

	if (map.HasError()) {
		printf("error code: %d\n", map.GetErrorCode());
		printf("error text: %s\n", map.GetErrorText().c_str());

		return NULL;
	}

	Room* room = new Room(GetLayer(map, "background"), GetLayer(map, "middle"), GetLayer(map, "foreground"));

	std::vector<Entity*> entities = GetEntities(map, "entities");

	float2 topleft(0,0);
	float2 bottomright((map.GetWidth()) * map.GetTileWidth(), (map.GetHeight()) * map.GetTileHeight());
	
	std::vector<std::pair<float2, float2>> rects = GetCameraRects(map, "camera");

	room->setCameraRect(topleft, bottomright);

	room->setCamera(new Camera(rects));

	for (unsigned int i = 0; i < entities.size(); i++)
	{
		room->addEntity(entities[i]);
	}

	return room;
}