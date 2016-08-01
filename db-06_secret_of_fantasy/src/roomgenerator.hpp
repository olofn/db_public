#ifndef SH09_ROOMGENERATOR
#define SH09_ROOMGENERATOR

#include <string>

class TileMap;
class Random;
class Room;

class RoomGenerator
{
public:
	enum Algorithm
	{
		ALGORITHM_BROWNIAN = 0,
		ALGORITHM_CASTLEMOOD = 1
	};

	static Room *generateRoom(int w, int h, Algorithm algorithm, const std::string &tileSet, const std::string &enemies, int numChests, Random &random);

	static void placeChest(Room *room, Random &random);
	
	static void placeEnemies(Room *room, char enemyType, Random &random);

	static void placeDoor(Room *room, const std::string &targetDungeon, int targetLevel, bool down, Random &random); 

	static void placeDirtPatch(Room *room, Random &random);

	static TileMap *generateTileMap(int w, int h, Algorithm algorithm, Random &random);

	static void generateBrownianSolidity(TileMap *tileMap, Random &random);
	
	static void generateCastleMood(TileMap *tileMap, Random &random);

	static bool validateSolidity(TileMap *tileMap);

	static void generateTiles(TileMap *tileMap, Random &random);

private:
	RoomGenerator() { }
};

#endif