#include "roomloader.hpp"
#include "room.hpp"
#include "tilemap.hpp"
#include "entityfactory.hpp"
#include "stringutil.hpp"
#include "fileutil.hpp"
#include "exception.hpp"
#include "random.hpp"

TileMap *RoomLoader::loadTileMap(const std::string& filename)
{
	std::cout << "Loading tilemap " + filename + "...";
    std::vector<std::string> data = tokenize(loadFile(filename), "\n", true);

	int width = 0;
	int height = 0;
	int row;
    int col;

	for (row = 0; row < (int)data.size(); row++)
	{
		if (row == 0)
            width = data[row].size();
		height++;
	}
	height = (height - 1) / 2;

	TileMap* tileMap = new TileMap(width, height);
	tileMap->clear(0,0);

	// Load solidities 
	for (row = 0; row < height; row++)
	{
		for (col = 0; col < width; col++)
		{
			char c = data.at(row).at(col);
			if (c == '.')
			{
				tileMap->setFlags(col, row, 0);
			}
			else if (c == '#')
			{
				tileMap->setFlags(col, row, TileMap::FLAG_SOLID);
			} 
		}
	}

	// Load tiles
	for (row = height; row < height*2; row++)
	{
		for (col = 0; col < width; col++)
		{
			char c = data.at(row).at(col);
			int tile = c - ((c >= 'a')? 'a' - 10 : '0');
			tileMap->setTile(col, row - height, tile);
		}
	}

	//std::cout << tileMap->toString() << std::endl;

    std::cout << " Done!" << std::endl;
	return tileMap;
}

Room *RoomLoader::loadRoom(const std::string& filename)
{
	TileMap* tileMap = loadTileMap(filename);

	std::cout << "Loading room " + filename + "...";
    std::vector<std::string> data = tokenize(loadFile(filename), "\n", true);

	std::vector<std::string> tileSetInfo = tokenize(data[data.size()-1], " ");

	if (tileSetInfo.size() == 0)
	{
		throw DB_EXCEPTION("Tilset info is missing in file " + filename);
	}

	std::string tileSetFileName = "graphics/" + tileSetInfo[0];
	int numTiles = fromString<int>(tileSetInfo[1]);

	Room* room = new Room(tileMap, new Animation(tileSetFileName, numTiles));	

	int width = 0;
	int height = 0;
	int row;
    int col;

	// Load entities 
	int x = 0;
	int y = 0;
	for (row = 0; row < tileMap->getHeight(); row++)
	{
		for (col = 0; col < tileMap->getWidth(); col++)
		{
			char c = data[row].at(col);
			// Ignore solidities.
			if (c != '.' && c != '#')
			{
				Entity* entity = createEntity(c, x * TileMap::TILE_SIZE, y * TileMap::TILE_SIZE, Random::get());
				room->addEntity(entity);
			}
	
			x++;
		}
		x = 0;
		y++;
	}

    std::cout << " Done!" << std::endl;

	return room;
}