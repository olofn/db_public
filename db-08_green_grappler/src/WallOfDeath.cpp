#include "WallOfDeath.hpp"

#include "Room.hpp"
#include "Hero.hpp"
#include "Animation.hpp"
#include "Resource.hpp"
#include "ParticleSystem.hpp"
#include "PlayerSkill.hpp"
#include "Sound.hpp"

WallOfDeath::WallOfDeath()
: myInited(false)
, myBoost(false)
, mySpeed(0)
, myFrameCounter(0)
, myRunning(false)
, mySoundCountdown(10.0f)
{
	setSize(float2(10, 12 * 100));
	mySaw = Resource::getAnimation("data/images/saw.bmp");
}

void WallOfDeath::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	int x = getDrawPositionX() + offsetX - getSize().x / 2;
	int y = getDrawPositionY() + offsetY - getSize().y / 2;

	int saws = (int)getSize().y / 12;

	for (int i = 0; i < saws; i++)
	{
		mySaw->drawFrame(buffer, myFrameCounter / 5 + i, x, y + i * 12);
	}
	//Entity::draw(buffer, offsetX, offsetY, layer);
}

void WallOfDeath::update()
{
	myFrameCounter++;
	
	if (!myInited)
	{
		myOriginalPosition = getPosition();
		myInited = true;
		mRoom->createTileBackup();
	}

	if (!myRunning)
		return;

	if (mPosition.x > 2950.0f) {
		ParticleSystem *ps = new ParticleSystem(mySaw, 2, 100, 20, 10, 20, 1, float2(0.0f, -50.0f), 4.0f);

		int x = getDrawPositionX() - getSize().x / 2;
		int y = getDrawPositionY() - getSize().y / 2;
		int saws = (int)getSize().y / 12;

		for (int i = 0; i < saws; i++)
		{
			ps->setPosition(float2(x, y + i * 12), 0.1f, true);
		}

		mRoom->addEntity(ps);
		remove();
		return;
	}

	for (int xo = 0; xo < 3; xo++) {
		for (int yt = 0; yt < mRoom->getHeightInTiles(); yt++) {
			int xt = xo + (int)((mPosition.x - mSize.x / 2) / mRoom->getTileWidth());
			mRoom->destroyTile(xt, yt);
		}
	}

	float heroX = mRoom->getHero()->getPosition().x;
	float x = getPosition().x;

	float distance = heroX - x;
	if (distance > 190 && !myBoost)
	{
		mPosition.x = heroX - 190;
	}

	if (distance < 80)
	{
		myBoost = false;
	}
	
	if (myBoost)
	{
		mySpeed = lerp(5.0f, 9.0f, PlayerSkill::get());
	}
	else
	{
		float wantedSpeed = lerp(1.0f, 1.9f, PlayerSkill::get());
		mySpeed = lerp(mySpeed, wantedSpeed, 0.05f);
	}

	mySoundCountdown -= mySpeed;
	if (mySoundCountdown <= 0.0f) {
		mySoundCountdown += 10.0f;
		Sound::playSample("data/sounds/damage.wav");
	}

		
	setPosition(float2(getPosition().x + mySpeed, getPosition().y));

	if (Collides(mRoom->getHero()->getCollisionRect(), getCollisionRect()))
	{
		mRoom->getHero()->kill();
	}
}

void WallOfDeath::onRespawn()
{
	mRoom->restoreTileBackup();
	setPosition(myOriginalPosition);
	myRunning = false;
	myBoost = false;
	mySoundCountdown = 10.0f;
}

void WallOfDeath::onStartWallOfDeath()
{
	if (!myRunning) {
		myRunning = true;
	} else {
		myBoost = true;
	}
}
