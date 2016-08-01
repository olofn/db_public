#ifndef DB_MILK_HPP
#define DB_MILK_HPP

#include "entity.hpp"
#include "animation.hpp"

class MilkCutScene : public Entity
{
public:
	MilkCutScene(int x, int y);

	~MilkCutScene();
	
	void logic();

	void draw(BITMAP *dest, int scrollx, int scrolly);

private:
	Animation mAnimation;
	bool mActivated;
	bool mInitialized;
};

#endif