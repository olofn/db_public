#include "eye.hpp"
#include "stringutil.hpp"
#include "random.hpp"
#include "room.hpp"
#include "util.hpp"
#include "exception.hpp"
#include "game.hpp"
#include "gamestate.hpp"

Eye::Eye(int x, int y, int level) : 
	Actor(ENEMY, x, y, 14, 14, true),
	mAnimLeft("graphics/eyewalkleft.bmp", 4),
	mAnimRight("graphics/eyewalkright.bmp", 4),
	mAnimUp("graphics/eyewalkupwards.bmp", 4),
	mAnimDown("graphics/eyewalkdownwards.bmp", 4),
	mStateChangeTimer(0)
{
	mLevel = level;
	addState("walkleft", &mAnimLeft, -1, 0, 5, Actor::LEFT, false, false);
	addState("walkright", &mAnimRight, 1, 0, 5, Actor::RIGHT, false, false);
	addState("walkup", &mAnimUp, 0, -1, 5, Actor::UP, false, false);
	addState("walkdown", &mAnimDown, 0, 1, 5, Actor::DOWN, false, false);

	setState("walkdown");

	setMaxHealth(50);
	setHealth(getMaxHealth());
}

Eye::~Eye()
{
}

void Eye::logic()
{
	mStateChangeTimer--;

	bool bump = Actor::move();

	if (bump || mStateChangeTimer <= 0)
	{
		nextState();
		mStateChangeTimer = 40;
	}

	//if (stateChangeTimer <= 0)
	//{
	//	switch (Random::get().getInt(5))
	//	{
	//	case 0:
	//		setState("walkleft");
	//		break;
	//	case 1:
	//		setState("walkright");
	//		break;
	//	case 2:
	//		setState("walkup");
	//		break;
	//	case 3:
	//		setState("walkdown");
	//		break;
	//	default:
	//		setState(Random::get().getInt(2) == 0 ? "idleleft" : "idleright");
	//		break;
	//	}

	//	stateChangeTimer = Random::get().getInt(10, 30);
	//}

	

	std::vector<Entity*> players = mRoom->collidesWith(this, Entity::PLAYER);

	if (players.size() != 0)
	{
		mRoom->getPlayer()->damage(1, getDirection());
	}
}

void Eye::nextState()
{
	Direction d = (Direction)mod(getDirection() + Random::get().getInt(-1, 1), 4);

	switch(d)
	{
	case Actor::LEFT:
		setState("walkleft");
		break;
	case Actor::RIGHT:
		setState("walkright");
		break;
	case Actor::DOWN:
		setState("walkdown");
		break;
	case Actor::UP:
		setState("walkup");
		break;
	default:
		throw DB_EXCEPTION("Knas");
	}
}

void Eye::damage(int damage, Entity::Direction direction)
{
	if (mRoom->getGame()->isHeroicMode())
		damage = (damage * 2) / 3;

	if (!isToBeDeleted())
	{
		flash();
		setState("pause");
		mStateChangeTimer = 2;
		setHealth(getHealth() - damage);

		if (isToBeDeleted())
		{
			GameState *s = mRoom->getGame()->getGameState();
			s->put("kills", s->getInt("kills") + 1);
			mRoom->spawnDeath(this);
		}
	}
}

bool Eye::isToBeDeleted()
{
	return getHealth() <= 0;
}