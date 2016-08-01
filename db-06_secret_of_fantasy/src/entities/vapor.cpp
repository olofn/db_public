#include "entities/vapor.hpp"
#include "room.hpp"
#include "game.hpp"
#include "entities/shot.hpp"
#include "random.hpp"
#include "exception.hpp"
#include "util.hpp"
#include "tilemap.hpp"
#include "items/milk.hpp"
#include "entities/chest.hpp"
#include "entities/portalhome.hpp"

Vapor::Vapor(int x, int y)
:NormalActor("vapor",
			 ENEMY,
			 x, 
		     y, 
		     14, 
		     10, 
		     true),
 mSwingSidewaysAnimation("graphics/vaporswingsideways.bmp", 1),
 mSwingDownAnimation("graphics/vaporswingdownwards.bmp", 1),
 mSwingUpAnimation("graphics/vaporswingupwards.bmp", 1),
 mHurtAnimation("graphics/vaporhurt.bmp", 1)
{
	mHealth = 750;
	mCanTakeDamage = true;
	mStateChangeTimer = 0;
	setState("standdown");
	addState("warmupforshot", &mWalkDownwardsAnimation, 0, 0, 0, DOWN, false, false);
	addState("teleport", &mWalkDownwardsAnimation, 0, 0, 0, DOWN, false, false);
	addState("hurt", &mHurtAnimation, 0, 0, 0, DOWN, false, false);
	mDialog = false;
	mEndDialog = false;
	mIsToBeDeleted = false;
}

void Vapor::logic()
{
	if (!mDialog)
	{
		Player* player = mRoom->getPlayer();
		player->setPosition(this->getX() + 16, 0);
		mRoom->addActorStateCutScene(this, "standdown");
		mRoom->addActorStateCutScene(player, "walkdown");
		mRoom->addWaitForActorPostitionCutScene(player, player->getX(), 100);
		mRoom->addActorStateCutScene(player, "standdown");
		mRoom->addWaitCutScene(50);
		mRoom->addDialogCutScene("ted: Now give me back my milk!", false);
		mRoom->addActorStateCutScene(this, "standup");
		mRoom->addWaitCutScene(50);
		mRoom->addDialogCutScene("lord vapor: What? Who?...", false);
		mRoom->addDialogCutScene("lord vapor: Ah it is you again. Are you still following me?", false);
		mRoom->addDialogCutScene("ted: I want my milk!", false);
		mRoom->addDialogCutScene("lord vapor: If you want it so bad than come and get it!", false);
		mRoom->addMusicCutScene("music/olof3.xm", 1);
		mRoom->addWaitCutScene(50, true);
		mRoom->startCutScenes();
		mDialog = true;
		mStateChangeTimer = 200;
		return;
	}

	if (mHealth > 0 && mDialog)
	{
		battleLogic();
		return;
	}
	
	if (!mEndDialog)
	{
		flash(0);
		mRoom->getPlayer()->blink(0);
		mRoom->setTotalFreeze(true);
		mRoom->addActorStateCutScene(this, "standdown");
		mRoom->addDialogCutScene("lord vapor: aaaahhhhhh!", false);
		mRoom->addDialogCutScene("lord vapor: this is not happening!", false);
		mRoom->addDialogCutScene("ted: give me back me milk!", false);
		mRoom->addDialogCutScene("lord vapor: i have no choice but to give in to your demands!", false);
		mRoom->addDialogCutScene("lord vapor: farewell cruel world!", false);
		mRoom->addWaitCutScene(100, true);
		mRoom->addEntity(new PortalHome(200, 48));
		mRoom->startCutScenes();
		mEndDialog = true;
		return;
	}

	mIsToBeDeleted = true;
	mRoom->spawnLargeSmokeAtEntity(this);
	mRoom->addEntity(new Chest(mX, mY, new Milk(), false));
}

void Vapor::battleLogic()
{
	mStateChangeTimer--;
	
	Actor::move();

	int tw = mRoom->getTileMap()->getWidth() * TileMap::TILE_SIZE;
	int th = mRoom->getTileMap()->getHeight() * TileMap::TILE_SIZE;

	if (mStateChangeTimer <= 0)
	{
		nextState(true);
	}

	if (mX < 46)
	{
		mX++;
		nextState();
	}

	if ((mX + mW) > (tw - 46))
	{
		mX = tw - 46 - mW;
		nextState();
	}
	
	if (mY < 96)
	{
		mY = 96;
		nextState();
	}

	if ((mY + mH) > (th - 80))
	{
		mY = th - 80 - mH;
		nextState();
	}

	std::vector<Entity*> players = mRoom->collidesWith(this, Entity::PLAYER, 0);
	if (players.size() != 0)
	{
		mRoom->getPlayer()->damage(1, getDirection());
	}
}

bool Vapor::isToBeDeleted()
{
	return mIsToBeDeleted;
}

void Vapor::damage(int damage, Entity::Direction direction)
{
	if (!mCanTakeDamage)
		return;

	if (mRoom->getGame()->isHeroicMode())
		damage = (damage * 2) / 3;

	if (!isToBeDeleted())
	{
		switch(direction)
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
		setState("hurt");
		mStateChangeTimer = Random::get().getInt(5, 10);
		mHealth -= damage;
	}
}

void Vapor::nextState(bool canShoot)
{
	Direction d = (Direction)mod(getDirection() + Random::get().getInt(-1, 1), 4);

	if (getCurrentStateName() == "teleport")
	{
		mX = Random::get().getInt(50, 320);
		mY = Random::get().getInt(100, 192);
		mRoom->spawnLargeSmokeAtEntity(this);
		setVisible(true);
		mCanTakeDamage = true;
	}

	if (getCurrentStateName() == "warmupforshot")
	{
		setState("standdown");
		mStateChangeTimer = 50;
		int shootSpeed = 2;
		int x = mX + mW / 2;
		int y = mY + mH / 2;
		mRoom->addEntity(new Shot(Entity::ENEMY, Entity::PLAYER, x, y, -shootSpeed, 0, 200, "graphics/vaporshot.bmp", 3, 2, getDirection()));
		mRoom->addEntity(new Shot(Entity::ENEMY, Entity::PLAYER, x, y,  shootSpeed, 0, 200, "graphics/vaporshot.bmp", 3, 2, getDirection()));
		mRoom->addEntity(new Shot(Entity::ENEMY, Entity::PLAYER, x, y,  0, shootSpeed, 200, "graphics/vaporshot.bmp", 3, 2, getDirection()));
		mRoom->addEntity(new Shot(Entity::ENEMY, Entity::PLAYER, x, y,  0, -shootSpeed, 200, "graphics/vaporshot.bmp", 3, 2, getDirection()));
		mRoom->addEntity(new Shot(Entity::ENEMY, Entity::PLAYER, x, y, -shootSpeed, -shootSpeed, 200, "graphics/vaporshot.bmp", 3, 2, getDirection()));
		mRoom->addEntity(new Shot(Entity::ENEMY, Entity::PLAYER, x, y,  shootSpeed, -shootSpeed, 200, "graphics/vaporshot.bmp", 3, 2, getDirection()));
		mRoom->addEntity(new Shot(Entity::ENEMY, Entity::PLAYER, x, y,  -shootSpeed, shootSpeed, 200, "graphics/vaporshot.bmp", 3, 2, getDirection()));
		mRoom->addEntity(new Shot(Entity::ENEMY, Entity::PLAYER, x, y,  shootSpeed, shootSpeed, 200, "graphics/vaporshot.bmp", 3, 2, getDirection()));
		return;
	}

	if (canShoot && Random::get().getInt(0, 2) == 0)
	{
		setState("warmupforshot");
		flash(25);
		mStateChangeTimer = 25;
		return;
	}

	if (Random::get().getInt(0, 7) == 0)
	{
		setState("teleport");
		setVisible(false);
		mStateChangeTimer = 30;
		mRoom->spawnLargeSmokeAtEntity(this);
		mCanTakeDamage = false;
		return;
	}

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

	mStateChangeTimer = Random::get().getInt(40, 60);
	setVisible(true);
}