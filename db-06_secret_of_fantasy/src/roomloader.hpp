#ifndef SH09_ROOMLOADER
#define SH09_ROOMLOADER

#include <string>
#include "guichan.hpp"

class TileMap;
class Room;

class RoomLoader
{
public:	
	static TileMap *loadTileMap(const std::string& filename);
	static Room *loadRoom(const std::string& filename);

private:
	RoomLoader() { }
};

#endif