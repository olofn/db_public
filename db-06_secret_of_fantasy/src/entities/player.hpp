#ifndef DB_PLAYER_HPP
#define DB_PLAYER_HPP

#include "normalactor.hpp"
#include "animation.hpp"
#include "keystate.hpp"
#include "inventory.hpp"

class Room;

class Player: public NormalActor
{
public:
	Player();
	~Player();
	void logic();
	void setInputDisabled(bool disabled);
	Inventory* getInventory();
	void setRoom(Room* room);
	void addCoins(int coins);
	void setCoins(int coins);
	int getCoins();
	void damage(int damage, Entity::Direction direction);
	void setInvincible(int frames) { mDamageTimer = frames; }

private:
	void checkInput();

	Animation mSwingSidewaysAnimation;
	Animation mSwingUpAnimation;
	Animation mSwingDownAnimation;
	int mAttackTimer;
	int mDamageTimer;
	Inventory* mInventory;
	int mCoins;
	bool mPendingSwing;

	SAMPLE *mSampleHurt;
};

#endif