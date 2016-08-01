#include <cmath>
#include <iostream>

#include "entities/savepoint.hpp"
#include "room.hpp"
#include "blending.hpp"

namespace nmc
{
	SavePoint::SavePoint(int x, int y) 
        : Entity(x-1, y, 2, 16, true),
          mTriggered(true),
          mDialogShown(true),
		  mKeysDisabled(false),
		  mFrame(-10),
		  mSprite("savepoint.bmp", 1)
	{
	}

	SavePoint::~SavePoint()
	{
	}

	void SavePoint::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
	{
		std::list<Particle>::iterator it;

		mSprite.drawFrame(dest, 0, mX - scrollx - 16, mY - scrolly, false, false, Animation::ADD);

		setAddBlender();
		drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);

		for (it = mParticles.begin(); it != mParticles.end(); it++)
		{
			circle(dest, it->x + mX - scrollx, it->y + mY - scrolly, 1, makecol(70, 50, 100));
			putpixel(dest, it->x + mX - scrollx, it->y + mY - scrolly, makecol(120, 100, 150));
		}

		drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

		//rect(dest, mX - scrollx, mY - scrolly, mX - scrollx + mW - 1, mY - scrolly + mH -1, rand()*256);
	}

	void SavePoint::logic(Room *room)
	{
		mFrame++;

		if (!mTriggered)
		{
			mDialogShown = false;			
		}

		if (!room->getSaveDialog()->isVisible() && mKeysDisabled)
		{
			room->setKeysDisabled(false);
			mKeysDisabled = false;
		}


		std::list<Particle>::iterator it;

		for (it = mParticles.begin(); it != mParticles.end(); it++)
		{
			it->time++;
			it->y -= it->time / it->speed;
		}


		mParticles.push_back(Particle(std::sin((mFrame * 10 + rand() % 100) / 100.0f) * 16.0f, rand() % 10 + 8));		
		
		if (rand() % 4 == 0)
		{
			mParticles.push_back(Particle(std::sin((rand() % 3142) / 100.0f) * 16.0f, rand() % 10 + 8));
		}

		if (mTriggered || room->getSaveDialog()->isVisible())
		{
			mParticles.push_back(Particle(std::sin((rand() % 3142) / 100.0f) * 16.0f, rand() % 10 + 8));
			mParticles.push_back(Particle(std::sin((rand() % 3142) / 100.0f) * 16.0f, rand() % 10 + 8));
		}

		while (mParticles.front().time > 40)
		{
			mParticles.pop_front();
		}

		mTriggered = false;
	}

	bool SavePoint::isToBeDeleted()
	{
		return false;
	}

	void SavePoint::handleCollision(Entity *other, Room* room)
	{
        if (other == room->getPlayer())
        {
            if (!mDialogShown)
            {
                room->setKeysDisabled(true);
                room->getSaveDialog()->setVisible(true);
                mDialogShown = true;
				mKeysDisabled = true;
            }    

                
            mTriggered = true;
        }
	}
}