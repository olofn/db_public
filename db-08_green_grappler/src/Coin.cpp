#include "Coin.hpp"

#include "Room.hpp"
#include "Hero.hpp"

#include "Resource.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "PlayerSkill.hpp"

void Coin::update()
{
	Hero* hero = mRoom->getHero();

	if (mType == Type_Dynamic)
	{
		if (mTemporary && !mLifeTime)
		{
			remove();
		}
		else
		{
			mVelocity.y += 6.0;

			unsigned int bumps = moveWithCollision();

			if ((bumps & (Direction_Left | Direction_Right)) != 0) {
				if (abs(mVelocity.x) > 10){
					Sound::playSample("data/sounds/coin.wav");
				}
				mVelocity.x *= -0.5;
			}

			if ((bumps & (Direction_Up | Direction_Down)) != 0) {
				if (abs(mVelocity.y) > 10){
					Sound::playSample("data/sounds/coin.wav");
				}
				mVelocity.y *= -0.2;
			}

			mLifeTime--;
		}
	}
	
	if (Collides(hero->getCollisionRect(), getCollisionRect()))
	{
		if (hero->gotCoin())
		{
			PlayerSkill::playerDidSomethingClever(0.3f, 0.05f);
			Sound::playSample("data/sounds/coin.wav");
			remove();
		}
	}

	mFrame++;
}

Coin::Coin()
: mType(Type_Static)
, mLifeTime(0)
, mFrame(0)
{
	mAminationCoin = Resource::getAnimation("data/images/coin.bmp", 4);
	setSize(float2(12,12));
}

void Coin::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{
	float2 pos = getPosition();
	pos -= float2(mAminationCoin->getFrameWidth(), mAminationCoin->getFrameHeight())/2;
	pos += float2(offsetX, offsetY);

	if (!mTemporary || (mLifeTime/10)%2 == 0 )
	{
		if (mFrame > 180)
		{
			mFrame = 0;
		}

		mAminationCoin->drawFrame(buffer, (mFrame < 5*4)?mFrame/5:0, pos.x, pos.y);
	}
}

void 
Coin::setLifeTime( int aLifeTime )
{
	mLifeTime = aLifeTime;
	mType = Type_Dynamic;
	mTemporary = aLifeTime != 0;
}

void Coin::onRespawn()
{
	if (mType == Type_Dynamic)
		remove();
}

void Coin::SpawnDeathCoins( int aNumberOfCoins, float2 aCenterPosition, int aLifeTime, Room* aRoom)
{
	for (int i = 0; i < aNumberOfCoins; i++)
	{

		float2 velocity = sincos(3.1415 * (i+1)/(aNumberOfCoins+1));
		velocity.x *= 100;
		velocity.y *= -200;

		Coin* coin = new Coin();
		coin->setLifeTime(aLifeTime);
		coin->setPosition(aCenterPosition);
		coin->setVelocity(velocity);
		aRoom->addEntity(coin);
		Sound::playSample("data/sounds/coin.wav");
	}
}