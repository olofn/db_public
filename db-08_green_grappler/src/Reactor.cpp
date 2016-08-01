#include "Reactor.hpp"

#include "Room.hpp"
#include "Coin.hpp"
#include "Animation.hpp"
#include "Resource.hpp"
#include "Sound.hpp"
#include "Camera.hpp"
#include "ParticleSystem.hpp"
#include "Util.hpp"
#include "ReactorCore.hpp"

#define DAMAGE_MAX 16
#define FRAME_PER_DAMAGE 4
#define BLOW_TIME (60 * 4 + 30)

Reactor::Reactor()
: myDamage(0)
, myAboutToBlow(false)
, myFrameCounter(0)
{
	setSize(float2(30, 40));
	myShell = Resource::getAnimation("data/images/reactor_shell.bmp", 4);
}

void Reactor::onRespawn()
{
	myAboutToBlow = false;
	myDamage = 0;
}

void Reactor::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	int x = getDrawPositionX() + offsetX;
	int y = getDrawPositionY() + offsetY;

	if (myDamage >= DAMAGE_MAX)
		myShell->drawFrame(buffer, myDamage / FRAME_PER_DAMAGE - 1, x - (int)getSize().x / 2, y - (int)getSize().y / 2);
	else
		myShell->drawFrame(buffer, myDamage / FRAME_PER_DAMAGE, x - (int)getSize().x / 2, y - (int)getSize().y / 2);

	//Entity::draw(buffer, offsetX, offsetY, layer);
}

void Reactor::update()
{
	myFrameCounter++;

	if (myAboutToBlow && myFrameCounter % 60 == 0)
		Sound::playSample("data/sounds/alarm.wav");

	if (myAboutToBlow && myFrameCounter % 20 == 0)
	{
		int numPs = rand() % 5 + 1;
		ParticleSystem* ps = new ParticleSystem(Resource::getAnimation("data/images/debris.bmp", 4), 10, 40, 10, 1, 50, numPs, -float2(0.0f, 20.0f), 2.0f);
		ps->setPosition(getPosition(), 10.0f);
		mRoom->addEntity(ps);
	}

	if (myAboutToBlow && myFrameCounter >= BLOW_TIME)
	{
		Sound::playSample("data/sounds/reactor_explosion.wav");
		Sound::playSample("data/sounds/start.wav");
		ParticleSystem* ps = new ParticleSystem(Resource::getAnimation("data/images/debris.bmp", 4), 20, 200, 20, 1, 50, 50, -float2(0.0f, 150.0f), 5.0f);
		ps->setPosition(getPosition(), 10.0f);
		mRoom->addEntity(ps);

		//Coin::SpawnDeathCoins(10, getPosition(), 0, mRoom);

		ReactorCore* core = new ReactorCore;
		core->setPosition(getPosition());
		core->setVelocity(float2(0, -50));
		mRoom->addEntity(core);
		setTilesCollidable(false);
		remove();
	}
}

bool Reactor::isDamagable()
{
	return true;
}

void Reactor::onDamage()
{
	if (myDamage >= DAMAGE_MAX)
		return;

// 	2,
// 		30,
// 		10,
// 		1,
// 		50,
// 		20,
// 		-normalize(mRopeVelocity)*10,
// 		1.0);

	int numPs = rand() % 5 + 1;
	ParticleSystem* ps = new ParticleSystem(Resource::getAnimation("data/images/debris.bmp", 4), 10, 40, 10, 1, 50, numPs, -float2(0.0f, 20.0f), 2.0f);
	ps->setPosition(getPosition(), 10.0f);
	mRoom->addEntity(ps);

	myDamage++;
	if (myDamage == DAMAGE_MAX)
	{
		myFrameCounter = 1;
		myAboutToBlow = true;
		
		Sound::playSample("data/sounds/damage.wav");
		mRoom->getCamera()->addShake(4.0f, BLOW_TIME);
	}
	else
	{
		Sound::playSample("data/sounds/damage.wav");
		mRoom->getCamera()->addShake(1.0f, 20);
	}

}

void 
Reactor::setTilesCollidable( 
	bool aCollidable )
{
	int sx = (getPosition().x-getHalfSize().x)/10;
	int sy = (getPosition().y-getHalfSize().y)/10;

	for (int x = sx; x < sx + 3; x++)
		for (int y = sy; y < sy + 4; y++)
			mRoom->setCollidable(x, y, aCollidable);
}

void Reactor::setRoom( Room *room )
{
	Entity::setRoom(room);
	setTilesCollidable(true);
}

Entity::CollisionRect Reactor::getCollisionRect()
{
	CollisionRect rect;
	rect.myTopLeft = getPosition()-getHalfSize()-float2(2,2);
	rect.myBottomRight = getPosition()+getHalfSize()+float2(2,2);
	return rect;
}