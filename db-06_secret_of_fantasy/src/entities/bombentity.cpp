#include "entities/bombentity.hpp"

#include "room.hpp"
#include "resourcehandler.hpp"
#include <cmath>

BombEntity::BombEntity(int x, int y)
:Entity(Entity::OTHER,x, y, 16, 16, true),
 mAnimation("graphics/bomb.bmp", 3)
{
    mFrameCounter = 0;
    mExploded = false;
    mSample = ResourceHandler::getInstance()->getSample("sound/bomb.wav");
}
    
void BombEntity::draw(BITMAP *dest, int scrollx, int scrolly)
{
	Animation::Blending blending = Animation::NONE;

	if (mFrameCounter > 100)
	{
		blending = ((mFrameCounter / 2) & 1) ? Animation::LIGHTEN : Animation::NONE;
	}

    mAnimation.drawFrame(dest, mFrameCounter % 5, mX - scrollx, mY - scrolly, false, false, blending);
}

void BombEntity::logic()
{
    mFrameCounter++;

    if (mFrameCounter > 150 && !mExploded)
    {
        mExploded = true;
		
		std::vector<Entity*> explodables = mRoom->collidesWith(this, Entity::EXPLODABLE, 32);
		for (unsigned int i = 0; i < explodables.size(); i++)
		{
			makeDamageToEntity(explodables[i], 10.0f);
		}

		std::vector<Entity*> enemies = mRoom->collidesWith(this, Entity::ENEMY, 32);
		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			makeDamageToEntity(enemies[i], 30.0f);
		}

		mRoom->spawnLargeSmokeAtEntity(this);
		play_sample(mSample, 127, 127, 750, 0);
    }
}

void BombEntity::makeDamageToEntity(Entity* entity, float inpact)
{
	int dx = mX - entity->getX();
	int dy = mY - entity->getY();
	float length = std::sqrt((float)dx*dx + (float)dy*dy);
	float distance = length / 16.0f;
	int damage = (int)(inpact / (distance *  distance));
	entity->damage(damage, Entity::LEFT);
}

bool BombEntity::isToBeDeleted()
{
    return mExploded;
}