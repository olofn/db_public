#include "ReactorCore.hpp"

#include "Room.hpp"
#include "Hero.hpp"

#include "Animation.hpp"
#include "Resource.hpp"
#include "Sound.hpp"
#include "PlayerSkill.hpp"

void ReactorCore::update()
{
	Hero* hero = mRoom->getHero();

	mVelocity.y += 6.0;
	mVelocity.x = 0;

	unsigned int bumps = moveWithCollision();

	if ((bumps & (Direction_Up | Direction_Down)) != 0) {
		mVelocity.y *= -0.8;
	}

	if (Collides(hero->getCollisionRect(), getCollisionRect()))
	{
		if (hero->gotCore())
		{
			PlayerSkill::playerDidSomethingClever(1.0f, 0.75f);
			mRoom->setCompleted();
			remove();
		}
	}

	mFrame++;
}

ReactorCore::ReactorCore()
: mFrame(0)
{
	mAnimation = Resource::getAnimation("data/images/core.bmp", 3);
	setSize(float2(30,30));
}

void ReactorCore::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	//Entity::draw(buffer, offsetX, offsetY, layer);
	float2 pos = getPosition();
	pos -= float2(mAnimation->getFrameWidth(), mAnimation->getFrameHeight())/2;
	pos += float2(offsetX, offsetY);

	mAnimation->drawFrame(buffer, mFrame/5, pos.x, pos.y);
}
