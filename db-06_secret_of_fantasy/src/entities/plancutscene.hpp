#ifndef DB_PLANCUTSCENE_HPP
#define DB_PLANCUTSCENE_HPP

#include "entity.hpp"

class PlanCutScene: public Entity
{
public:
	PlanCutScene();
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly) {}
private:
	bool mHasRun;
};
#endif