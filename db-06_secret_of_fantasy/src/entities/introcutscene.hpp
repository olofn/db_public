#ifndef DB_INTROCUTSCENE_HPP
#define DB_INTROCUTSCENE_HPP

#include "entity.hpp"

class IntroCutScene: public Entity
{
public:
	IntroCutScene();
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly) {}
private:
	bool mHasRun;
};
#endif