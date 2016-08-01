#include "BossSaw.hpp"
#include "Animation.hpp"
#include "Resource.hpp"
#include "Room.hpp"
#include "Hero.hpp"
#include "Sound.hpp"

BossSaw::BossSaw( Direction aDirection )
: myLifeTime(60 * 6)
, myFrameCounter(0)
{
	if (aDirection == Direction_Left)
		mySpeed = float2(-2.0f, 0);
	else
		mySpeed = float2(2.0f, 0);

	mySaw = Resource::getAnimation("data/images/saw.bmp");
	Sound::playSample("data/sounds/boss_saw.wav");
	setSize(float2(mySaw->getFrameWidth(), mySaw->getFrameHeight()));
}

void BossSaw::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	int x = getDrawPositionX() + offsetX - getHalfSize().x;
	int y = getDrawPositionY() + offsetY - getHalfSize().y;

	mySaw->drawFrame(buffer, myFrameCounter / 10, x, y);

	//Entity::draw(buffer, offsetX, offsetY, layer);
}

void BossSaw::update()
{
	myFrameCounter++;

	if (myFrameCounter > myLifeTime)
		remove();

	setPosition(getPosition() + mySpeed);


	if (Collides(mRoom->getHero()->getCollisionRect(), getCollisionRect()))
	{
		mRoom->getHero()->kill();
	}
}

int BossSaw::getLayer()
{
	return 3;
}

void BossSaw::onRespawn()
{
	remove();
}
