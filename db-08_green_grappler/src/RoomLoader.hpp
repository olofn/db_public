#pragma  once

#include "Room.hpp"

class RoomLoader
{
public:
	static Room* LoadRoom(const std::string& aRoomName);
};