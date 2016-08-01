#include "entities/bomb.hpp"

#include "level.hpp"
#include "resourcehandler.hpp"
#include <cmath>

Bomb::Bomb(int x, int y)
:Entity(x, y, 16, 16, false),
 mAnimation("bomb.bmp")
{
    mFrameCounter = 0;
    mExploded = false;
    mExplosionSample = ResourceHandler::getInstance()->getSample("explo2.wav");
}
    
void Bomb::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    mAnimation.drawFrame(dest, mFrameCounter % 5, mX - scrollx, mY - scrolly);
}

void Bomb::logic(Level *level)
{
    mFrameCounter++;
    
    mY+=4;

    if (level->getTileMap()->isOnGround(this))
        level->getTileMap()->alignToGroundTile(this);

    if (mFrameCounter > 150 && !mExploded)
    {
        level->spawnExplosions(20, getX(), getY(), 16, 16);
        mExploded = true;

        int pan = ((getCenterX() - level->getCamera()->getX()) * 256) / 240;
		
        if (pan < 0)
		{
			pan = 0;
		} 
		else if (pan > 255)
		{
			pan = 255;
		}

        play_sample(mExplosionSample, 150, pan, 750, 0);
        level->distributeMessage("bombexplosion", this);
    }
}

bool Bomb::isToBeDeleted()
{
    return mExploded;
}

float Bomb::getExplosionImpact(Entity* entity)
{
    int dx = mX - entity->getX();
    int dy = mY - entity->getY();
    float length = std::sqrt((float)dx*dx + (float)dy*dy);
    float distance = length / 16.0f;

    return 10.0f / (distance *  distance);
}
