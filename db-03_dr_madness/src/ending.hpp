#ifndef DBSH07_ENDING_HPP
#define DBSH07_ENDING_HPP

#include <allegro.h>

#include "animation.hpp"

class Ending
{
public:
    Ending();
    void logic();
    void draw(BITMAP* dest);
    bool isDone();
	void reset();
protected:
    int mFrameCounter;
	Animation mPlanet;
	Animation mExplosion;
	SAMPLE *mS1;
	SAMPLE *mS2;
};
#endif