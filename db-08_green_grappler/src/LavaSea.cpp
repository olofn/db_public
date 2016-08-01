#include "LavaSea.hpp"

#include "Room.hpp"
#include "Hero.hpp"

#include "Camera.hpp"
#include "Resource.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "ParticleSystem.hpp"

void LavaSea::update()
{
	Hero* hero = mRoom->getHero();

	if (Entity::Collides(hero->getCollisionRect(), getCollisionRect()))
	{
		hero->kill();
	}

	mFrame++;

	if (mSafeMode)
	{
		mSafeLevel++;
		if (mSafeLevel > getPosition().y + 10)
		{
			mSafeLevel = getPosition().y + 10;
		}
	}

	if (mRandom.getFloat(0,1) < 0.3)
	{
		ParticleSystem* particleSystem = new ParticleSystem(
			Resource::getAnimation("data/images/particles.bmp"),
			2,
			30,
			10,
			1,
			50,
			10,
			float2(0, -30),
			5.0);

		float2 pos = float2(mRandom.getInt(-mRoom->getCamera()->getOffset().x, 320-mRoom->getCamera()->getOffset().x), getCurrentY());
		particleSystem->setPosition(pos, 5);

		mRoom->addEntity(particleSystem);
	}
}

LavaSea::LavaSea()
: mFrame(0)
, mSafeMode(false)
{
	mTopAnimation = Resource::getAnimation("data/images/lavatop.bmp",2);
	mFillAnimation = Resource::getAnimation("data/images/lavafill.bmp",2);
}

void LavaSea::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	int screenY = offsetY+getCurrentY();

	for (int x = -10 + offsetX%10; x <320; x+= 10)
	{
		mTopAnimation->drawFrame(buffer, mFrame/30, x, screenY);

		for (int y = screenY + 10; y < 240; y += 10)
		{
			mFillAnimation->drawFrame(buffer, mFrame/30, x, y);
		}
	}



//	line(buffer, 0, screenY, 320, screenY, makecol(255,0,0));
}

void LavaSea::onRespawn()
{
	
}

Entity::CollisionRect 
LavaSea::getCollisionRect()
{
	CollisionRect rect;
	rect.myTopLeft = float2(0, getCurrentY());
	rect.myBottomRight = float2(10000000, 10000000);

	return rect;
}

int LavaSea::getCurrentY()
{
	if (mSafeMode)
	{
		return mSafeLevel;
	}

	float sinwave = (sin((float)mFrame/100.0f)+1)/2;
	sinwave = sinwave*sinwave*sinwave ;
	return getPosition().y - sinwave*80 + 2;
}

void LavaSea::onLevelComplete()
{
	mSafeLevel = getCurrentY();
	mSafeMode = true;
}
