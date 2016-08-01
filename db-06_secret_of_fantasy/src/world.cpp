#include <allegro.h>

#include "world.hpp"
#include "room.hpp"
#include "roomgenerator.hpp"
#include "roomloader.hpp"
#include "fileutil.hpp"
#include "stringutil.hpp"
#include "resourcehandler.hpp"
#include "random.hpp"

World::World()
{
}

void World::load(int seed)
{
	this->seed = seed;
	createWorldDescriptor();
}

Room *World::getRoom(const std::string &dungeon, int level)
{
	Room *room = 0;
	DungeonDescriptor dungDesc = worldDescriptor[dungeon];
	RoomDescriptor roomDesc = dungDesc.at(level);
	std::string parent = roomDesc["parent"];
	std::string music = roomDesc["music"];

	if (music != "")
		music = "music/" + music;

	if (roomDesc["method"] == "load")
	{
		room = RoomLoader::loadRoom("rooms/" + roomDesc["file"]);

		// Patch up the doors
		if (parent != "")
		{
			Door *d = room->findUnboundDoor(false);
			if (d)
			{
				d->setTargetDungeon(parent);
				d->setTargetLevel(0);
			}
		}
		
		if (level > 0)
		{
			Door *d = room->findUnboundDoor(false);
			if (d)
			{
				d->setTargetDungeon(dungeon);
				d->setTargetLevel(level - 1);
			}
		}

		if (level < (int)dungDesc.size() - 1)
		{
			Door *d = room->findUnboundDoor(true);
			if (d)
			{
				d->setTargetDungeon(dungeon);
				d->setTargetLevel(level + 1);
			}
		}
	}
	else if (roomDesc["method"] == "generate")
	{
		std::string tileSet = roomDesc["tileset"];
		std::string enemies = roomDesc["enemies"];
		int algorithm = fromString<int>(roomDesc["algorithm"]);
		int width = fromString<int>(roomDesc["width"]);
		int height = fromString<int>(roomDesc["height"]);
		int chests = fromString<int>(roomDesc["chests"]);

		int roomSeed = seed + level * 1000;
		for (int i = 0; i < (int)dungeon.size(); i++)
		{
			roomSeed = (roomSeed + 431) * dungeon[i];
		}
		
		Random random(roomSeed);

		room = RoomGenerator::generateRoom(width, height, (RoomGenerator::Algorithm)algorithm, "graphics/" + tileSet, enemies, chests, random);
		
		if (parent != "")
		{
			RoomGenerator::placeDoor(room, parent, 0, false, random);
		}
		
		if (level > 0)
		{
			RoomGenerator::placeDoor(room, dungeon, level - 1, false, random);
		}

		if (level < (int)dungDesc.size() - 1)
		{
			RoomGenerator::placeDoor(room, dungeon, level + 1, true, random);
		}
	}

	room->setDungeonName(dungeon);
	room->setDungeonLevel(level);
	room->setMusic(music);

	return room;
}

void World::createWorldDescriptor()
{
	worldDescriptor.clear();
	std::vector<std::string> dungeonList = createDungeonList();

	for (int i = 0; i < (int)dungeonList.size(); i++)
	{
		std::string dungeonStr = loadFile("dungeons/" + dungeonList[i]);
		worldDescriptor[dungeonList[i]] = createDungeonDescriptor(dungeonStr);
	}
}

std::vector<std::string> World::createDungeonList()
{
	std::vector<std::string> result;

	al_ffblk findResult;

	std::string pattern = ResourceHandler::getInstance()->getRealFilename("dungeons/*.txt");

	if (al_findfirst(pattern.c_str(), &findResult, FA_ALL) != 0) {
		return result;
	}

	do {
		result.push_back(findResult.name);
	} while (al_findnext(&findResult) == 0);

	al_findclose(&findResult);

	return result;
}

World::DungeonDescriptor World::createDungeonDescriptor(const std::string &str)
{
	DungeonDescriptor result;
	std::vector<std::string> roomStrings = tokenize(str, "=\n", true);

	for (int i = 0; i < (int)roomStrings.size(); i++)
	{
		result.push_back(createRoomDescriptor(roomStrings[i]));
	}

	return result;
}

World::RoomDescriptor World::createRoomDescriptor(const std::string &str)
{
	RoomDescriptor result;
	std::vector<std::string> rows = tokenize(str, "\n", true);

	for (int i = 0; i < (int)rows.size(); i++)
	{
		std::vector<std::string> split = tokenize(rows[i], ":");
		result[split[0]] = split[1];
	}

	return result;
}
