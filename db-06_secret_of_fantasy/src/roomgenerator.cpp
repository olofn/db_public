#include "roomgenerator.hpp"
#include "tilemap.hpp"
#include "random.hpp"
#include "room.hpp"
#include "random.hpp"
#include "entityfactory.hpp"
#include "entities/door.hpp"


Room *RoomGenerator::generateRoom(int w, int h, Algorithm algorithm, const std::string &tileSetFile, const std::string &enemies, int numChests, Random &random)
{
	TileMap *tileMap = generateTileMap(w, h, algorithm, random);
	Animation *tileSet = new Animation(tileSetFile, 6);
	Room *room = new Room(tileMap, tileSet);

	for (int i = 0; i < numChests; i++)
	{
		placeChest(room, random);
	}

	int numEnemies = random.getInt(4, 6);

	for (int i = 0; i < numEnemies; i++)
	{
		placeEnemies(room, enemies[random.getInt(enemies.size())], random);
	}

	int numPatches = random.getInt(3) * random.getInt(4);

	for (int i = 0; i < numPatches; i++)
	{
		placeDirtPatch(room, random);
	}

	return room;
}

void RoomGenerator::placeEnemies(Room *room, char enemyType, Random &random)
{
	int originX;
	int originY;

	do
	{
		originX = random.getInt(room->getTileMap()->getWidth());
		originY = random.getInt(room->getTileMap()->getHeight());
	} while (room->getTileMap()->isSolid(originX, originY));

	int numEnemies = random.getInt(3, 10);

	for (int i = 0; i < numEnemies; i++)
	{
		int x = originX + random.getInt(-5, 5);
		int y = originY + random.getInt(-5, 5);

		if (room->getTileMap()->getFlags(x, y) == 0)
		{
			Entity *e = createEntity(enemyType, x * TileMap::TILE_SIZE, y * TileMap::TILE_SIZE, random);
			room->addEntity(e);
		}
	}
}

void RoomGenerator::placeDirtPatch(Room *room, Random &random)
{
	int x, y;

	do
	{
		x = random.getInt(room->getTileMap()->getWidth());
		y = random.getInt(room->getTileMap()->getHeight());
	} while (room->getTileMap()->isSolid(x, y));

	for (int i = 0; i < 5; i++)
	{
		room->addEntity(createEntity('F', x * 16, y * 16, random));

		if (random.getInt(2) == 0)
		{
			x++;
		}
		else
		{
			y++;
		}

		if (room->getTileMap()->isSolid(x, y))
			break;
	}
}

void RoomGenerator::placeChest(Room *room, Random &random)
{
	while(true)
	{
		int x = random.getInt(room->getTileMap()->getWidth());
		int y = random.getInt(room->getTileMap()->getHeight());

		bool free = true;

		for (int yo = -1; yo <= 2; yo++)
		{
			for (int xo = -1; xo <= 1; xo++)
			{
				if (room->getTileMap()->isSolid(x + xo, y + yo))
					free = false;
			}
		}

		if (free)
		{
			Entity *e = createEntity('A', x * TileMap::TILE_SIZE, y * TileMap::TILE_SIZE, random);
			room->addEntity(e);
			room->getTileMap()->setFlags(x, y, TileMap::FLAG_SOLID);
			return;
		}
	}
}

void RoomGenerator::placeDoor(Room *room, const std::string &targetDungeon, int targetLevel, bool down, Random &random)
{
	TileMap *tm = room->getTileMap();

	while(true)
	{
		int x = random.getInt(tm->getWidth());
		int y = random.getInt(tm->getHeight());
		
		bool ok = false;

		while(true)
		{
			if (y < 0 || y >= tm->getHeight())
			{
				break;
			}

			if (tm->isSolid(x, y + 1))
			{
				y++;
			}
			else if (!tm->isSolid(x, y))
			{
				y--;
			}
			else if (tm->isSolid(x - 1, y) && tm->isSolid(x + 1, y))
			{
				ok = tm->isSolid(x, y - 1);
				break;
			}
			else
			{
				break;
			}
		}

		if (ok)
		{
			tm->setFlags(x, y, 0);
			room->addEntity(new Door(x * TileMap::TILE_SIZE, y * TileMap::TILE_SIZE, down, targetDungeon, targetLevel, false));
			break;
		}
	}
}

TileMap *RoomGenerator::generateTileMap(int w, int h, Algorithm algorithm, Random &random)
{
	TileMap *tileMap = new TileMap(w, h);

	do
	{
		switch(algorithm)
		{
		case ALGORITHM_BROWNIAN:
			generateBrownianSolidity(tileMap, random);
			break;
		case ALGORITHM_CASTLEMOOD:
			generateCastleMood(tileMap, random);
			break;
		}
	} while (!validateSolidity(tileMap));

	generateTiles(tileMap, random);

	return tileMap;
}

void RoomGenerator::generateCastleMood(TileMap *tileMap, Random &random)
{
	tileMap->clear(0, TileMap::FLAG_SOLID);
	int w = tileMap->getWidth();
	int h = tileMap->getHeight();

	//storlek på rum
	int minWidth = 4;
	int minHeight = 4;
	int maxWidth = 15;
	int maxHeight = 15;

	int minNbrOfRooms = 15;
	int maxNbrOfRooms = 25;

	int pathWidth = 2;

	int lastX1 = -1;
	int lastY1 = -1;
	int lastX2 = -1;
	int lastY2 = -1;

	for(int i = 0; i < random.getInt(minNbrOfRooms, maxNbrOfRooms); i++)
	{
		int x1 = random.getInt(2, w - maxWidth - 1);
		int y1 = random.getInt(2, h - maxHeight - 1);
		int x2 = x1+random.getInt(minWidth, maxWidth);
		int y2 = y1+random.getInt(minHeight, maxHeight);

		bool didTouchOtherRoom = false;
		for(int x = x1; x < x2; x++)
		{
			for(int y = y1; y < y2; y++)
			{
				if(tileMap->getFlags(x, y) == 0)
					didTouchOtherRoom = true;
				tileMap->setFlags(x, y, 0);
			}
		}

		if(lastX1 != -1) //finns det ett gammalt rum?
		{
			//gör en väg från gamla rummet till nya...
			if(!didTouchOtherRoom) //om det inte sitter ihop med något annat rum
			{
				int startX = lastX1 + (lastX2-lastX1)/2;
				int startY= lastY1 + (lastY2-lastY1)/2;
				int endX = x1 + (x2-x1)/2;
				int endY = y1 + (y2-y1)/2;
				int speedX = startX < endX ? 1 : -1;
				int speedY = startY < endY ? 1 : -1;
				
				int extraWidth = pathWidth%2!=0 ? 1 : 0;

				for(int x = startX; x != endX; x+=speedX)
				{
					for(int y = startY-pathWidth/2; y < startY+pathWidth/2+extraWidth; y++)
						tileMap->setFlags(x, y, 0);
				}

				for(int y = startY; y != endY; y+=speedY)
				{
					for(int x = endX-pathWidth/2; x < endX+pathWidth/2 + extraWidth; x++)
						tileMap->setFlags(x, y, 0);
				}
			}
		}
		lastX1 = x1;
		lastY1 = y1;
		lastX2 = x2;
		lastY2 = y2;
	}
}

void RoomGenerator::generateBrownianSolidity(TileMap *tileMap, Random &random)
{
	tileMap->clear(0, TileMap::FLAG_SOLID);

	int w = tileMap->getWidth();
	int h = tileMap->getHeight();

	int x = w / 2;
	int y = h / 2;
	int cleared = 0;

	while(cleared / (double)(w * h) < 0.35)
	{
		// Clear 3x3 tiles around x, y
		for (int yo = -1; yo <= 1; yo++)
		{
			for (int xo = -1; xo <= 1; xo++)
			{
				int rx = x + xo;
				int ry = y + yo;

				if (tileMap->isSolid(rx, ry))
				{
					cleared++;
					tileMap->setFlags(rx, ry, 0);
				}
			}
		}

		x += random.getInt(-2, 2);
		y += random.getInt(-2, 2);

		if (x <= 2 || y <= 2 || x >= w - 2 || y >= h - 3)
		{
			x = w / 2;
			y = h / 2;

			for (int i = 0; i < 30; i++)
			{
				int nx = random.getInt(3, w - 3);
				int ny = random.getInt(3, h - 4);

				if (tileMap->getFlags(nx, ny) == 0)
				{
					x = nx;
					y = ny;
					break;
				}
			}
		}
	}

	// Sprinkle some pillars
	int numPillars = random.getInt(cleared / 20, cleared / 70);

	for (int i = 0; i < numPillars; i++)
	{
		bool good = true;
		x = random.getInt(w);
		y = random.getInt(h);

		for (int yo = -1; yo <= 1; yo++)
		{
			for (int xo = -1; xo <= 1; xo++)
			{
				if (tileMap->isSolid(x + xo, y + yo))
				{
					good = false;
				}
			}
		}

		if (good)
			tileMap->setFlags(x, y, TileMap::FLAG_SOLID);
	}
}

bool RoomGenerator::validateSolidity(TileMap *tileMap)
{
	// TODO: Validate that all edge tiles are solid
	// TODO: Validate that all non-solid tiles are reachable
	return true;
}

void RoomGenerator::generateTiles(TileMap *tileMap, Random &random)
{
	int baseWall = 0;
	int numWall = 1;
	int basePillar = 1;
	int numPillar = 1;
	int baseGround = 2;
	int numGround = 4;

	for (int x = 0; x < tileMap->getWidth(); x++)
	{
		for (int y = 0; y < tileMap->getHeight(); y++)
		{
			// Put down ground
			tileMap->setTile(x, y, random.getInt(numGround) + baseGround);

			if (tileMap->isSolid(x, y))
			{
				if (tileMap->isSolid(x, y - 1))
				{
					// Put down wall
					tileMap->setTile(x, y, random.getInt(numWall) + baseWall);
				}
				else if (!tileMap->isSolid(x, y + 1))
				{
					// Put down pillar
					tileMap->setTile(x, y, random.getInt(numPillar) + basePillar);
				}
			}
		}
	}
}