#include "world.hpp"

#include "resourcehandler.hpp"
#include "exception.hpp"
#include "stringutil.hpp"
#include "fileutil.hpp"
#include <fstream>

namespace nmc
{
    World* World::mInstance = 0;

    World* World::getInstance()
    {
        if (mInstance == 0)
        {
            mInstance = new World();
        }

        return mInstance;
    }

    World::World()
    {
        load();
    }

    void World::setRoomPosition(int roomNumber, RoomPosition roomPosition)
    {
        mRoomPositions[roomNumber] = roomPosition;
    }

    RoomPosition World::getRoomPosition(int roomNumber)
    {
        return mRoomPositions[roomNumber];
    }

    int World::getRoomAt(int x, int y)
    {
        std::map<int, RoomPosition>::iterator it;

        for (it = mRoomPositions.begin(); it != mRoomPositions.end(); it++)
        {
            int roomNumber = it->first;
            int roomX = it->second.x;
            int roomY = it->second.y;
            int roomWidth = ResourceHandler::getInstance()->getRoomTilesBitmap(it->first)->w;
            int roomHeight = ResourceHandler::getInstance()->getRoomTilesBitmap(it->first)->h;

            if (x >= roomX && x < roomWidth + roomX
                && y >= roomY && y < roomHeight + roomY)
            {
                return roomNumber;
            }
        }
       
        throw NMC_EXCEPTION("No room found at coordinate (" + toString(x) + "," + toString(y) + ").");
    }

    void World::save()
    {
        std::map<int, RoomPosition>::iterator it;

        std::ofstream file(ResourceHandler::getInstance()->getRealFilename("world.dat").c_str(), 
                           std::ios_base::out | std::ios_base::binary);

		if (!file.is_open() || !file.good())
		{
			file.close();
			throw NMC_EXCEPTION("Unable to open " 
                + ResourceHandler::getInstance()->getRealFilename("world.dat") + " for writing.");
		}

        writeInt(file, mRoomPositions.size());

        for (it = mRoomPositions.begin(); it != mRoomPositions.end(); it++)
        {
            int roomNumber = it->first;
            int roomX = it->second.x;
            int roomY = it->second.y;

            writeInt(file, roomNumber);
            writeInt(file, roomX);
            writeInt(file, roomY);
        }

        file.close();
    }

    void World::load()
    {
        std::ifstream file(ResourceHandler::getInstance()->getRealFilename("world.dat").c_str(),
                           std::ios_base::in | std::ios_base::binary);
	
		if (!file.is_open() || !file.good())
		{
			file.close();
	        return;
		}

		int size = readInt(file);
		int i;
		for (i = 0; i < size; i++)
		{
            int roomNumber = readInt(file);
            int roomX = readInt(file);
            int roomY = readInt(file);

            mRoomPositions[roomNumber] = RoomPosition(roomX, roomY);
		}

		file.close();
    }

    std::vector<int> World::getRoomNumberList()
    {
        std::vector<int> roomNumberList;

        std::map<int, RoomPosition>::iterator it;

        for (it = mRoomPositions.begin(); it != mRoomPositions.end(); it++)
        {
            int roomNumber = it->first;
            roomNumberList.push_back(roomNumber);
        }

        return roomNumberList;
    }
}