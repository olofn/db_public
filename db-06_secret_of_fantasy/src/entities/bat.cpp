#include "bat.hpp"
#include "stringutil.hpp"
#include "random.hpp"
#include "room.hpp"
#include "game.hpp"
#include "gamestate.hpp"

Bat::Bat(int x, int y, int batType, int level) : 
	Actor(ENEMY, x, y, 14, 10, true),
	mAnimation("graphics/bat" + toString(batType + 1) + ".bmp", 2),
	stateChangeTimer(0),
	mBatType(batType)
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

	setMaxHealth(10 * (batType + 1));
	setHealth(getMaxHealth());
}

Bat::~Bat()
{
}

void Bat::logic()
{
	stateChangeTimer--;

	if (stateChangeTimer <= 0)
	{
		Player* player = mRoom->getPlayer();
		
		int distBeforeAggro = mBatType*30;
		//std::cout << "type: " << mBatType << "dist before aggro: " << distBeforeAggro << std::endl;
		
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

void Bat::damage(int damage, Entity::Direction direction)
{
	if (mRoom->getGame()->isHeroicMode())
		damage = (damage * 2) / 3;

	if (!isToBeDeleted())
	{
		Player* player = mRoom->getPlayer();

		switch(player->getDirection())
		{
		case DOWN:
			move(0, 10);
			break;
		case UP:
			move(0, -10);
			break;
		case LEFT:
			move(-10, 0);
			break;
		case RIGHT:
			move(10, 0);
			break;
		}
		flash();
		setState(Random::get().getInt(2) == 0 ? "idleleft" : "idleright");
		stateChangeTimer = Random::get().getInt(1, 5);
		setHealth(getHealth() - damage);

		if (isToBeDeleted())
		{
			GameState *s = mRoom->getGame()->getGameState();
			s->put("kills", s->getInt("kills") + 1);
			mRoom->spawnDeath(this);
		}
	}
}

bool Bat::isToBeDeleted()
{
	return getHealth() <= 0;
}