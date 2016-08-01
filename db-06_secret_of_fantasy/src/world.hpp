#ifndef DB_WORLD_HPP
#define DB_WORLD_HPP

#include <string>
#include <vector>
#include <map>

class Room;

class World
{
public:
	World();

	void load(int seed);

	Room *getRoom(const std::string &dungeon, int level);

private:
	typedef std::map<std::string, std::string> RoomDescriptor;
	typedef std::vector<RoomDescriptor> DungeonDescriptor;
	typedef std::map<std::string, DungeonDescriptor> WorldDescriptor;

	void createWorldDescriptor();

	std::vector<std::string> createDungeonList();
	
	DungeonDescriptor createDungeonDescriptor(const std::string &str);

	RoomDescriptor createRoomDescriptor(const std::string &str);


	WorldDescriptor worldDescriptor;
	int seed;
};

#endif