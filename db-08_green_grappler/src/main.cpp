#include "Precompiled.hpp"
#include "Speedhack11Game.hpp"

#include "Tmx.h"

int main(int argc, char **argv)
{			

	Tmx::Map map;
	map.ParseFile("data/example.tmx");

	Speedhack11Game game;
	game.run();

	return 0;
}
END_OF_MAIN()