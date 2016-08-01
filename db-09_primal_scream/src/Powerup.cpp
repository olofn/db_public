#include "Precompiled.hpp"

#include "Powerup.hpp"
#include "GameState.hpp"
#include "Hero.hpp"
#include "Room.hpp"
#include "Font.hpp"
#include "Resource.hpp"
#include "PowerUpScreen.hpp"
#include "ScreenManager.hpp"

Powerup::Powerup(std::string kind)
	: mKind(kind)
	, mFrame(0)
	, mAnimation("data/images/powerups.png", 12)
{
	setSize(float2(16, 16));
}

void Powerup::update()
{
	if (GameState::getInt(mKind) != 0)
	{
		return;
	}

	Hero *hero = getRoom()->getHero();
	Entity::CollisionRect cr = hero->getCollisionRect();
	if (Collides(getCollisionRect(), cr))
	{
		GameState::put(mKind, 1);
		std::string explanation;
		PowerUpScreen* screen;
		if (mKind == GameState::POWERUP_HIJUMP) {
			screen = new PowerUpScreen("HI JUMP SOCKS", "JUMP HIGHER");
		} else if (mKind == GameState::POWERUP_GUN) {
			screen = new PowerUpScreen("POWER GUN", "USE Z");
		} else if (mKind == GameState::POWERUP_GRENADE) {
			screen = new PowerUpScreen("GRAVITY GRANADE", "USE X");
		}
		
		ScreenManager::add(screen);
	}

	mFrame++;
}

void Powerup::draw(BITMAP *buffer, int offsetX, int offsetY, int layer)
{
	if (GameState::getInt(mKind) != 0)
	{
		return;
	}

	int f = (mFrame / 4) % 4;

	if (mKind == GameState::POWERUP_HIJUMP) {
		f += 4;
	} else if (mKind == GameState::POWERUP_GUN) {
		f += 8;
	}

	mAnimation.drawFrame(buffer, f, offsetX + getDrawPositionX() - getHalfSize().x, offsetY + getDrawPositionY() - getHalfSize().y);
}
