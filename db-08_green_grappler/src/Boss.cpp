#include "Boss.hpp"
#include "Animation.hpp"
#include "Resource.hpp"
#include "Room.hpp"
#include "Hero.hpp"
#include "Camera.hpp"
#include "ParticleSystem.hpp"
#include "Sound.hpp"
#include "ReactorCore.hpp"
#include "Music.hpp"
#include "Coin.hpp"
#include "PlayerSkill.hpp"

#define BLOW_TIME (60 * 4 + 30)
#define DAMAGE_MAX 16
#define FRAME_PER_DAMAGE 4
#define INITIAL_BLOW_TIME (60 * 4 + 30)
#define MAX_HEALTH 40
#define MIN_HEALTH 10

Boss::Boss()
: myState(State_Init)
, myDirection(Direction_Left)
, myInitalHealth(16)
, myAnimFrameCounter(0)
{
	setSize(float2(30, 40));
	myReactor = Resource::getAnimation("data/images/reactor_shell.bmp", 4);
	myBoss = Resource::getAnimation("data/images/boss.bmp", 4);

	myHealth = lerp(MAX_HEALTH, MIN_HEALTH, PlayerSkill::get());
}

void Boss::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	int x = getDrawPositionX() + offsetX - getHalfSize().x;
	int y = getDrawPositionY() + offsetY - getHalfSize().y;

	if (myState == State_Sleeping)
		myReactor->drawFrame(buffer, DAMAGE_MAX / FRAME_PER_DAMAGE - (myInitalHealth + 3) / FRAME_PER_DAMAGE, x , y );
	else if (myState == State_InitialBlow)
		myReactor->drawFrame(buffer, 3, x , y );
	else if  (myState == State_Vulnerable)
		myBoss->drawFrame(buffer, 0, x, y);
	else
		myBoss->drawFrame(buffer, myAnimFrameCounter / 5, x, y);
	

//	Entity::draw(buffer, offsetX, offsetY, layer);
}

void Boss::update()
{
	myAnimFrameCounter++;
	myFrameCounter++;

	if (myState == State_Init)
	{
		myOriginalPos = getPosition();
		myState = State_Sleeping;
	}

	if (myState != State_MoveUpwards && myState != State_Sleeping && myState != State_InitialBlow && myState != State_Dead && myState != State_Vulnerable)
	{
		if (Collides(mRoom->getHero()->getCollisionRect(), getCollisionRect()))
		{
			mRoom->getHero()->kill();
		}
	}

	if (myState == State_InitialBlow)
	{
		if (myFrameCounter % 60 == 0)
			Sound::playSample("data/sounds/alarm.wav");

		if (myFrameCounter >= INITIAL_BLOW_TIME)
		{
			Sound::playSample("data/sounds/reactor_explosion.wav");
			Sound::playSample("data/sounds/start.wav");
			ParticleSystem* ps = new ParticleSystem(Resource::getAnimation("data/images/debris.bmp", 4), 20, 200, 20, 1, 50, 50, -float2(0.0f, 150.0f), 5.0f);
			ps->setPosition(getPosition(), 10.0f);
			mRoom->addEntity(ps);
			myFrameCounter = 0;
			myState = State_Awakening;
		}		
	}

	if (myState == State_Awakening)
	{
		if (myFrameCounter > 60 * 3)
		{
			myState = State_MoveUpwards;
			myFrameCounter = 0;
			setTilesCollidable(false);
			Music::pushSong();
			Music::playSong("data/music/olof3.xm");
		}
	}

	if (myState == State_MoveUpwards)
	{
		setPosition(getPosition() + float2(0, -1));
		if (myOriginalPos.y - getPosition().y > 130)
		{
			myState = State_Float;
			mRoom->broadcastBoosWallActivate();
			myFrameCounter = 0;
		}
	}

	if (myState == State_Float)
	{
		float y =  sinf(myFrameCounter / 8) * 2.0f;
		if (myDirection == Direction_Right)
		{
			setPosition(getPosition() + float2(1.5f, y));
			if (getPosition().x  - myOriginalPos.x > 110)
				myDirection = Direction_Left;

		}

		if (myDirection == Direction_Left)
		{
			setPosition(getPosition() + float2(-1.5f, y));
			if (myOriginalPos.x - getPosition().x > 110)
				myDirection = Direction_Right;
		}

		if (myFrameCounter > 60 * 7)
		{
			myState = State_Attack;
			myFrameCounter = 0;
		}
	}

	if (myState == State_Attack)
	{
		if (myFrameCounter < 40)
		{
			if (myFrameCounter % 2 == 0)
				setPosition(getPosition() + float2(-2, 0));
			else 
				setPosition(getPosition() + float2(2, 0));
		}
		else
		{
			setPosition(getPosition() + float2(0, 6.0f));
			if (myOriginalPos.y < getPosition().y)
			{
				mRoom->broadcastBoosWallDectivate();
				setPosition(float2(getPosition().x, myOriginalPos.y));
				myState = State_Vulnerable;
				mRoom->getCamera()->addShake(5.0f, 80);
				int numPs = rand() % 10 + 5;
				ParticleSystem* ps = new ParticleSystem(Resource::getAnimation("data/images/debris.bmp", 4), 10, 40, 10, 1, 50, numPs, -float2(0.0f, 20.0f), 2.0f);
				ps->setPosition(getPosition(), 10.0f);
				mRoom->addEntity(ps);
				mRoom->broadcastBoosFloorActivate();
				Sound::playSample("data/sounds/reactor_explosion.wav");
				Coin::SpawnDeathCoins(rand() % 5 + 3, getPosition(), 60 * 6, mRoom);
			}
		}
	
	}

	if (myState == State_Vulnerable)
	{
		if (myFrameCounter > 60 * 5)
		{
			myState = State_MoveUpwards;
			myFrameCounter = 0;
		}
	}

	if (myState == State_Dead)
	{
		if (myFrameCounter % 60 == 0)
			Sound::playSample("data/sounds/alarm.wav");

		if (myFrameCounter >= BLOW_TIME)
		{
			Sound::playSample("data/sounds/reactor_explosion.wav");
			Sound::playSample("data/sounds/start.wav");
			ParticleSystem* ps = new ParticleSystem(Resource::getAnimation("data/images/debris.bmp", 4), 20, 200, 20, 1, 50, 50, -float2(0.0f, 150.0f), 5.0f);
			ps->setPosition(getPosition(), 10.0f);
			mRoom->addEntity(ps);
			ReactorCore* core = new ReactorCore;
			core->setPosition(getPosition());
			core->setVelocity(float2(0, -50));
			mRoom->addEntity(core);
			remove();
		}
	}
}

int Boss::getLayer()
{
	return 3;
}

void 
Boss::setTilesCollidable( 
							bool aCollidable )
{
	int sx = (getPosition().x-getHalfSize().x)/10;
	int sy = (getPosition().y-getHalfSize().y)/10;

	for (int x = sx; x < sx + 3; x++)
		for (int y = sy; y < sy + 4; y++)
			mRoom->setCollidable(x, y, aCollidable);
}

void Boss::setRoom( Room *room )
{
	Entity::setRoom(room);
	setTilesCollidable(true);
}

void Boss::onDamage()
{
	if (myState == State_Sleeping)
	{
		int numPs = rand() % 5 + 1;
		ParticleSystem* ps = new ParticleSystem(Resource::getAnimation("data/images/debris.bmp", 4), 10, 40, 10, 1, 50, numPs, -float2(0.0f, 20.0f), 2.0f);
		ps->setPosition(getPosition(), 10.0f);
		mRoom->addEntity(ps);

		myInitalHealth--;
		if (myInitalHealth == 0)
		{
			myFrameCounter = 0;
			myState = State_InitialBlow;
			Sound::playSample("data/sounds/damage.wav");
			mRoom->getCamera()->addShake(4.0f, INITIAL_BLOW_TIME);
		}
		else
		{
			Sound::playSample("data/sounds/damage.wav");
			mRoom->getCamera()->addShake(1.0f, 20);
		}
	}

	if (myState == State_Vulnerable)
	{
		int numPs = rand() % 5 + 1;
		ParticleSystem* ps = new ParticleSystem(Resource::getAnimation("data/images/debris.bmp", 4), 10, 40, 10, 1, 50, numPs, -float2(0.0f, 20.0f), 2.0f);
		ps->setPosition(getPosition(), 10.0f);
		mRoom->addEntity(ps);

		myHealth--;

		if (myHealth < 0)
		{
			myState = State_Dead;
			myFrameCounter = 0;
			Sound::playSample("data/sounds/damage.wav");
			mRoom->getCamera()->addShake(4.0f, BLOW_TIME);
		}
		else
		{
			Sound::playSample("data/sounds/damage.wav");
			mRoom->getCamera()->addShake(1.0f, 20);
		}
	}
}

Entity::CollisionRect Boss::getCollisionRect()
{
	CollisionRect rect;
	rect.myTopLeft = getPosition()-getHalfSize()-float2(2,2);
	rect.myBottomRight = getPosition()+getHalfSize()+float2(2,2);
	return rect;
}

bool Boss::isDamagable()
{
	return true;
}

void Boss::onRespawn()
{
	setPosition(myOriginalPos);
	myState = State_Sleeping;
	myDirection = Direction_Left;
	myHealth = lerp(MAX_HEALTH, MIN_HEALTH, PlayerSkill::get());
	myInitalHealth = 16;
	myAnimFrameCounter = 0;
	Music::popSong();
	setTilesCollidable(true);
}

