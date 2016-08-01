#include "energyorb.hpp"
#include "level.hpp"
#include "gamestate.hpp"
#include "resourcehandler.hpp"

EnergyOrb::EnergyOrb(int x, int y)
: Entity(x, y, Level::BLOCK_SIZE, Level::BLOCK_SIZE, true),
mFrameCount(0)
{
	mKillsPlayer = false;
    mAnimation = new Animation("energyorb.bmp");
    mSample = ResourceHandler::getInstance()->getSample("shopbuy.wav");
}

EnergyOrb::~EnergyOrb()
{
    delete mAnimation;
}

void EnergyOrb::logic(Level* level)
{
    mFrameCount++;
	mY--;
}

void EnergyOrb::draw(BITMAP *dest, int scrolly, unsigned int layer)
{
    mAnimation->drawFrame(dest, mFrameCount, getX(), getY() - scrolly);
}

bool EnergyOrb::isToBeDeleted()
{
    return !isCollidable();
}

void EnergyOrb::handleCollision(Entity *other, Level *level)
{
    if (other->getType() == Entity::PLAYER_TYPE)
    {
		if (level->getPlayer()->getState() != Player::KILLED)
		{
			GameState::getInstance()->setEnergyOrbs(GameState::getInstance()->getEnergyOrbs() + 1);
			mCollidable = false;
			play_sample(mSample, 128, 128, 1000, 0);
		}
    }
}