#include "entities/button.hpp"
#include "level.hpp"
#include "blending.hpp"
#include "level.hpp"

#include <iostream>

Button::Button(int x, int y) 
    : Entity(x, y, 16, 16, true),
      mTriggered(false),
	  mAnimation("button.bmp"),
      mLightRayAnimation("lightray2.bmp"),
      mCollisionThisFrame(false)
{
}

Button::~Button()
{
}

void Button::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    if (mTriggered)
        mAnimation.drawFrame(dest, 1, mX - scrollx, mY - scrolly);
    else
        mAnimation.drawFrame(dest, 0, mX - scrollx, mY - scrolly);
    mLightRayAnimation.drawFrame(dest, 0, mX - scrollx, mY - scrolly, false, false, Animation::ADD);
}

void Button::logic(Level *Level)
{
    if (!mCollisionThisFrame)
    {
        mTriggered = false;
    }

	mCollisionThisFrame = false;
}

void Button::handleCollision(Entity *other, Level* level)
{
    if (other == level->getPlayer() && !mTriggered)
    {
        mTriggered = true;
        level->distributeMessage("buttonpushed", this);
        std::cout << "Pushed!" << std::endl;
    }

    mTriggered = true;
    mCollisionThisFrame = true;
}
