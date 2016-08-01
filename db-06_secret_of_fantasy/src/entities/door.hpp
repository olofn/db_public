#ifndef DB_DOOR_HPP
#define DB_DOOR_HPP

#include "entity.hpp"
#include "animation.hpp"

class Door : public Entity
{
public:
	Door(int x, int y, bool down, const std::string& targetDungeon, int targetLevel, bool realWorld);

	void logic();

	void draw(BITMAP *dest, int scrollx, int scrolly);

	const std::string getTargetDungeon() { return targetDungeon; }
	int getTargetLevel() { return targetLevel; }
	void setTargetDungeon(const std::string &d) { targetDungeon = d; }
	void setTargetLevel(int l) { targetLevel = l; }
	bool isDown() { return down; }

private:
	Animation animation;

	bool open;
	bool down;

	std::string targetDungeon;
	int targetLevel;
};

#endif