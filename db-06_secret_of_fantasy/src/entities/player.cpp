#include "entities/player.hpp"
#include "entities/swoosh.hpp"
#include "room.hpp"
#include "stringutil.hpp"
#include "items/cure.hpp"
#include "items/bomb.hpp"
#include "items/shovel.hpp"
#include "items/woodensword.hpp"
#include "items/windsword.hpp"
#include "items/magicgun.hpp"
#include "items/calciumcrystal.hpp"
#include "items/energydrink.hpp"
#include "resourcehandler.hpp"
#include "game.hpp"

Player::Player()
:NormalActor("player",
			 PLAYER,
			 0, 
		     0, 
		     12, 
		     10, 
		     true),
 mSwingSidewaysAnimation("graphics/playerswingsideways.bmp", 1),
 mSwingDownAnimation("graphics/playerswingdownwards.bmp", 1),
 mSwingUpAnimation("graphics/playerswingupwards.bmp", 1),
 mAttackTimer(0),
 mDamageTimer(0),
 mSampleHurt(ResourceHandler::getInstance()->getSample("sound/hurt.wav")),
 mPendingSwing(false)
{
	setState("standdown");
	mHealth = 6;
	mMaxHealth = 6;
	mCoins = 0;

	addState("swingright", &mSwingSidewaysAnimation, 0, 0, 6, RIGHT, true, false);
	addState("swingleft", &mSwingSidewaysAnimation, 0, 0, 6, LEFT, false, false);
	addState("swingdown", &mSwingDownAnimation, 0, 0, 6, DOWN, false, false);
	addState("swingup", &mSwingUpAnimation, 0, 0, 6, UP, false, false);

	// Precache swoosh and bomb animations
	Animation("graphics/swooshleft.bmp", 3);
	Animation("graphics/swooshup.bmp", 3);
	Animation("graphics/bomb.bmp", 3);

	mInventory = new Inventory();
	WoodenSword* sword = new WoodenSword();
	mInventory->add(sword);
	mInventory->useOrEquipe(sword, false);
}

Player::~Player()
{
	delete mInventory;
}

void Player::logic()
{
	mAttackTimer--;
	mDamageTimer--;

	checkInput();
	
	int oldX = getX();
	int oldY = getY();
	Actor::move();

	GameState *s = mRoom->getGame()->getGameState();
	s->put("walkdistance", s->getInt("walkdistance") + abs(oldX - getX()) + abs(oldY - getY()));
//	std::cout << s->getInt("walkdistance") << std::endl;
}

Inventory* Player::getInventory()
{
	return mInventory;
}

void Player::checkInput()
{
	if (mRoom->getKeyState()->isDisabled())
		return;

	if (mRoom->getKeyState()->isFirePressed())
		mPendingSwing = true;

	if (mAttackTimer > 0)
		return;

	if (mRoom->getKeyState()->isUpHeld())
		setState("walkup");
	else if (mRoom->getKeyState()->isDownHeld())
		setState("walkdown");
	else if (mRoom->getKeyState()->isLeftHeld())
		setState("walkleft");
	else if (mRoom->getKeyState()->isRightHeld())
		setState("walkright");
	else
		setState("pause");

	if (mPendingSwing)
	{
		mPendingSwing = false;

		//std::cout << *(mRoom->getGame()->getGameState()) << std::endl;
		switch(getDirection())
		{
		case Actor::LEFT:
			setState("swingleft");
			break;
		case Actor::RIGHT:
			setState("swingright");
			break;
		case Actor::UP:
			setState("swingup");
			break;
		case Actor::DOWN:
			setState("swingdown");
			break;
		}

		GameState *s = mRoom->getGame()->getGameState();
		s->put("attacks", s->getInt("attacks") + 1);

		mInventory->useEquipedWeapon(mRoom);

		mAttackTimer = 10;
	}

	if (mRoom->getKeyState()->isSpecialPressed())
	{
		mInventory->useUsable();
	}
}

void Player::setRoom(Room* room)
{
	Entity::setRoom(room);
	mInventory->setRoom(room);
}

void Player::addCoins(int coins)
{
	mCoins += coins;
}

void Player::setCoins(int coins)
{
	mCoins = coins;
}

int Player::getCoins()
{
	return mCoins;
}

void Player::damage(int damage, Entity::Direction direction)
{
	if (mHealth <= 0 || mDamageTimer > 0)
		return;

	play_sample(mSampleHurt, 127, 127, 1000, 0);

	GameState *s = mRoom->getGame()->getGameState();
	s->put("damagetaken", s->getInt("damagetaken") + damage);

	int speed = 4;
	switch(direction)
	{
	case DOWN:
		move(0, speed);
		break;
	case UP:
		move(0, -speed);
		break;
	case LEFT:
		move(-speed, 0);
		break;
	case RIGHT:
		move(speed, 0);
		break;
	}

	mHealth -= damage;
	mDamageTimer = 40;
	
	if (mHealth <= 0)
		blink(0);
	else
		blink(40);
}
