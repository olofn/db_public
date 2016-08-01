#include <cmath>

#include "entities/goal.hpp"
#include "level.hpp"
#include "blending.hpp"
#include "level.hpp"

Goal::Goal(int x, int y) 
    : Entity(x + 15, y, 2, 16, true),
      mTriggered(false),
	  mFrame(-10),
	  mSprite("goal.bmp", 1)
{
}

Goal::~Goal()
{
}

void Goal::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
	std::list<Particle>::iterator it;

	mSprite.drawFrame(dest, 0, mX - scrollx - 16, mY - scrolly, false, false, Animation::ADD);

	setAddBlender();
	drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);

	for (it = mParticles.begin(); it != mParticles.end(); it++)
	{
		circle(dest, it->x + mX - scrollx, it->y + mY - scrolly, 1, makecol(255, 50, 100));
		putpixel(dest, it->x + mX - scrollx, it->y + mY - scrolly, makecol(255, 100, 150));
	}

	drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

	//rect(dest, mX - scrollx, mY - scrolly, mX - scrollx + mW - 1, mY - scrolly + mH -1, rand()*256);
}

void Goal::logic(Level *Level)
{
	mFrame++;

	std::list<Particle>::iterator it;

	for (it = mParticles.begin(); it != mParticles.end(); it++)
	{
		it->time++;
		it->y -= it->time / it->speed;
	}


	mParticles.push_back(Particle(std::sin((mFrame * 10 + rand() % 100) / 100.0f) * 16.0f, rand() % 10 + 16));		
	
	if (rand() % 4 == 0)
	{
		mParticles.push_back(Particle(std::sin((rand() % 3142) / 100.0f) * 16.0f, rand() % 10 + 16));
	}

	if (mTriggered)
	{
		mParticles.push_back(Particle(std::sin((rand() % 3142) / 100.0f) * 16.0f, rand() % 10 + 16));
		mParticles.push_back(Particle(std::sin((rand() % 3142) / 100.0f) * 16.0f, rand() % 10 + 16));
	}

	while (mParticles.front().time > 40)
	{
		mParticles.pop_front();
	}

	mTriggered = false;
}

void Goal::handleCollision(Entity *other, Level* level)
{
    if (other == level->getPlayer())
    {
        mTriggered = true;
        level->setGoalReached(true);
    }
}
