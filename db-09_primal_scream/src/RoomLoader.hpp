#pragma  once

#include "Room.hpp"
#include "Tmx.h"

class RoomLoader
{
private:
	static Tmx::Map map;

public:
	static void Initialize();
	static Room* LoadRoom(int x, int y);
};