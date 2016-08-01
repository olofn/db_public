#include "Precompiled.hpp"
#include "BreakingHookTile.hpp"
#include "Resource.hpp"
#include "ParticleSystem.hpp"
#include "Room.hpp"
#include "Hero.hpp"
#include "PlayerSkill.hpp"

static const int MIN_BREAK_FRAMES = 30;
static const int MAX_BREAK_FRAMES = 50;

BreakingHookTile::BreakingHookTile()
	: mSprite("data/images/breakinghooktile.bmp")
	, mBreakCounter(0)
	, mBreaking(false)
	, mDestroyed(false)
{
	setSize(float2(mSprite.getFrameWidth(), mSprite.getFrameHeight()));
}

void BreakingHookTile::setRoom(Room *room)
{
	Entity::setRoom(room);
	onRespawn();
}

void BreakingHookTile::onRespawn()
{
	mTileX = (int)(mPosition.x / mRoom->getTileWidth());
	mTileY = (int)(mPosition.y / mRoom->getTileHeight());
	mRoom->setHookable(mTileX, mTileY, true);
	mRoom->setCollidable(mTileX, mTileY, true);
	mBreakCounter = 0;
	mBreaking = false;
	mDestroyed = false;
}

void BreakingHookTile::update()
{
	if (mDestroyed) {
		return;
	}

	if (mBreaking) {
		mBreakCounter++;
		int breakFrames = lerp(MAX_BREAK_FRAMES, MIN_BREAK_FRAMES, PlayerSkill::get());

		if (mRoom->getHero()->getRopeState() != Hero::RopeState_Attached) {
			breakFrames = -1;
		}

		if (mBreakCounter >= breakFrames) {
			mDestroyed = true;
			mRoom->setHookable(mTileX, mTileY, false);
			mRoom->setCollidable(mTileX, mTileY, false);

			ParticleSystem* ps = new ParticleSystem(Resource::getAnimation("data/images/debris.bmp", 4), 10, 50, 20, 1, 50, 2, -float2(0.0f, 30.0f), 2.0f);
			ps->setPosition(getPosition(), 2.0f);
			mRoom->addEntity(ps);

		}
	}

	Hero *hero = mRoom->getHero();

	if (hero != 0) {
		if (hero->getRopeState() == Hero::RopeState_Attached) {
			int ropeTileX = (int)(hero->getRopePosition().x / mRoom->getTileWidth());
			int ropeTileY = (int)(hero->getRopePosition().y / mRoom->getTileWidth());
			if (ropeTileX == mTileX && ropeTileY == mTileY) {
				mBreaking = true;
			}
		}
	}
}

void BreakingHookTile::draw(BITMAP *buffer, int offsetX, int offsetY, int layer)
{
	if (mDestroyed) {
		return;
	}

	int x = getDrawPositionX() + offsetX - mSprite.getFrameWidth() / 2;
	int y = getDrawPositionY() + offsetY - mSprite.getFrameWidth() / 2;

	if (!mBreaking || (mBreakCounter & 1) == 0) {
		mSprite.drawFrame(buffer, 0, x, y);
	}

}