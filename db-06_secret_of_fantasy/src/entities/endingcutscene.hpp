#ifndef DB_ENDINGCUTSCENE_HPP
#define DB_ENDINGCUTSCENE_HPP

#include "entity.hpp"

class EndingCutScene: public Entity
{
public:
	EndingCutScene();
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly) {}
private:
	bool mHasRun;
};
#endif