#include "Precompiled.hpp"

#include "Savepoint.hpp"
#include "Room.hpp"
#include "Hero.hpp"
#include "GameState.hpp"
#include "Font.hpp"
#include "Resource.hpp"
#include "Sound.hpp"


Savepoint::Savepoint()
	: mAnimation("data/images/savepoint.png", 4)
	, mHeroOn(true)
	, mTextCounter(0)
	, mFrame(0)
{
	setSize(float2(10, 10));
	mFont = Resource::getFont("data/images/font.bmp");
}


void Savepoint::update()
{
	mFrame++;

	if (mTextCounter > 0)
	{
		mTextCounter--;
	}

	Hero *hero = getRoom()->getHero();
	Entity::CollisionRect cr= hero->getCollisionRect();
	bool heroOn = Collides(getCollisionRect(), cr);

	if (heroOn && !mHeroOn)
	{
		// SAVE
		GameState::put(GameState::LOCATION_X, getRoom()->getWorldOffsetX() * getRoom()->getTileWidth() + this->getPosition().x);
		GameState::put(GameState::LOCATION_Y, getRoom()->getWorldOffsetY() * getRoom()->getTileHeight() + this->getPosition().y + 10);
		GameState::saveToFile();
		Sound::playSample("data/sounds/coin.wav");
		mTextCounter = 50;
	}

	mHeroOn = heroOn;
}

void Savepoint::draw(BITMAP *buffer, int offsetX, int offsetY, int layer)
{
	if (mTextCounter > 0)
	{
		mFont->drawCenter(buffer, "GAME SAVED", 0, 0, 320, 100);
	}

	mAnimation.drawFrame(
		buffer, 
		mFrame / 4, 
		offsetX + getDrawPositionX() - mAnimation.getFrameWidth() / 2,
		offsetY + getDrawPositionY() + getHalfSize().y - mAnimation.getFrameHeight() + 10);
}
