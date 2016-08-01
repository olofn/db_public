#include "slime.hpp"
#include "stringutil.hpp"
#include "random.hpp"
#include "room.hpp"
#include "game.hpp"
#include "gamestate.hpp"

Slime::Slime(int x, int y, int slimeType, int level) : 
	Actor(ENEMY, x, y, 14, 10, true),
	mAnimation("graphics/slime" + toString(slimeType + 1) + ".bmp", 4),
	stateChangeTimer(0),
	mSlimeType(slimeType)
{
	mLevel = level;
	addState("idleleft", &mAnimation, 0, 0, 6, Actor::LEFT, false, false);
	addState("idleright", &mAnimation, 0, 0, 6, Actor::RIGHT, true, false);
	addState("walkleft", &mAnimation, -1, 0, 3, Actor::LEFT, false, false);
	addState("walkright", &mAnimation, 1, 0, 3, Actor::RIGHT, true, false);
	addState("walkup", &mAnimation, 0, -1, 3, Actor::UP, true, false);
	addState("walkdown", &mAnimation, 0, 1, 3, Actor::DOWN, false, false);

	setState(Random::get().getInt(2) == 0 ? "idleleft" : "idleright");
	stateChangeTimer = Random::get().getInt(10, 30);

	setMaxHealth(10 * (slimeType + 1));
	setHealth(getMaxHealth());
}

Slime::~Slime()
{
}

void Slime::logic()
{
	stateChangeTimer--;

	if (stateChangeTimer <= 0)
	{
		Player* player = mRoom->getPlayer();
		//std::cout << "type: " << mSlimeType << std::endl;
		int distBeforeAggro = 0;
		if(mSlimeType == 2)
		{
			distBeforeAggro = 120;
		} else if(mSlimeType == 1)
		{
			distBeforeAggro = 60;
		}

		if(getDistance(player) < distBeforeAggro) // && Random::get().getInt(3) = 2)
		{
			if(Random::get().getInt(2) == 1)
			{
				if(player->getCenterX()<getCenterX())
				{
					setState("walkleft");
				} else {
					setState("walkright");
				}
			}
			else
			{
				if(player->getCenterY()<getCenterY())
				{
					setState("walkup");
				} else {
					setState("walkdown");
				}
			}


		}
		else
		{
			switch (Random::get().getInt(5))
			{
			case 0:
				setState("walkleft");
				break;
			case 1:
				setState("walkright");
				break;
			case 2:
				setState("walkup");
				break;
			case 3:
				setState("walkdown");
				break;
			default:
				setState(Random::get().getInt(2) == 0 ? "idleleft" : "idleright");
				break;
			}
		}

		stateChangeTimer = Random::get().getInt(10, 30);
	}

	Actor::move();

	std::vector<Entity*> players = mRoom->collidesWith(this, Entity::PLAYER);

	if (players.size() != 0)
	{
		mRoom->getPlayer()->damage(1, getDirection());
	}
}

void Slime::damage(int damage, Entity::Direction direction)
{
	if (mRoom->getGame()->isHeroicMode())
		damage = (damage * 2) / 3;

	if (!isToBeDeleted())
	{
		Player* player = mRoom->getPlayer();

		int len = 3 * (mSlimeType + 1) + 1;

		switch(player->getDirection())
		{
		case DOWN:
			move(0, len);
			break;
		case UP:
			move(0, -len);
			break;
		case LEFT:
			move(-len, 0);
			break;
		case RIGHT:
			move(len, 0);
			break;
		}
		flash();
		setState(Random::get().getInt(2) == 0 ? "idleleft" : "idleright");
		stateChangeTimer = Random::get().getInt(10, 30);
		setHealth(getHealth() - damage);

		if (isToBeDeleted())
		{
			GameState *s = mRoom->getGame()->getGameState();
			s->put("kills", s->getInt("kills") + 1);
			mRoom->spawnDeath(this);
		}
	}
}

bool Slime::isToBeDeleted()
{
	return getHealth() <= 0;
}