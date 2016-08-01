#ifndef DB_TOWERDOOR_HPP
#define DB_TOWERDOOR_HPP

#include "entity.hpp"
#include "animation.hpp"

class TowerDoor : public Entity
{
public:
	TowerDoor(int x, 
		      int y, 
			  const std::string& targetDungeon,
			  int targetLevel);

	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly);

private:
	std::string buildGameStateVariableString();
	Animation animation;
	bool open;
	std::string targetDungeon;
	int targetLevel;
	bool mInitialized;
	bool mCheckForCrystals;
};

#endif
