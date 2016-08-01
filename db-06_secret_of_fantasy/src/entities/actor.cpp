#include "entities/actor.hpp"
#include "exception.hpp"
#include "room.hpp"
#include "tilemap.hpp"
#include "util.hpp"

Actor::Actor(Entity::Type type,
			 int x,
			 int y,
			 int width,
			 int height,
			 bool collidable)
			 :Entity(type, x, y, width, height, collidable)
{
	mState = NULL;
	mAnimationFrame = 0;
	mFrameCounter = 0;
	mCheckForCollisions = true;
	mDirection = DOWN;
	mFlashFrames = 0;
	mBlinkFrames = 0;
	addState("pause", NULL, 0, 0, 0, DOWN, false, false);
	mVisible = true;
}

Actor::~Actor()
{

}

void Actor::setVisible(bool visible)
{
	mVisible = visible;
}

void Actor::setCheckForCollisions(bool check)
{
	mCheckForCollisions = check;
}

void Actor::draw(BITMAP *dest, int scrollx, int scrolly)
{
	if (!mVisible)
		return;

	if (mBlinkFrames > 0 && mBlinkFrames % 4 < 2)
		return;

	Animation::Blending blending = Animation::NONE;

	if (mFlashFrames > 0)
	{
		blending = ((mFlashFrames / 2) & 1) ? Animation::LIGHTEN : Animation::NONE;
	}

	int yTweak = mState->animation->getFrameHeight() - getHeight();
	int xTweak = (mState->animation->getFrameWidth() - getWidth()) / 2;
	mState->animation->drawFrame(dest, mAnimationFrame, mX - scrollx - xTweak, mY - scrolly - yTweak, mState->hflip, mState->vflip, blending);
}

void Actor::setState(const std::string& name)
{
	if (mStates.find(name) == mStates.end())
	{
		throw DB_EXCEPTION("State " + name + " not found!");
	}

	if (mState == &mStates[name])
		return;

	if (name == "pause")
	{
		State* mPauseState = &mStates[name];
		mPauseState->animation = mState->animation;
		mPauseState->hflip = mState->hflip;
		mPauseState->vflip = mState->vflip;
		mState = mPauseState;
	}
	else
	{
		mState = &mStates[name];
		mDirection = mState->direction;
	}

	mAnimationFrame = 0;
	mFrameCounter = 0;
	mCurrentStateName = name;
}

std::string Actor::getCurrentStateName()
{
	return mCurrentStateName;
}
void Actor::addState(const std::string& name,
			      Animation* animation,
				  int x,
				  int y,
				  int delay,
				  Direction direction,
				  bool hflip,
				  bool vflip)
{
	State state;
    state.animation = animation;
    state.x = x;
	state.y = y;
	state.delay = delay;
	state.direction = direction;
	state.hflip = hflip;
	state.vflip = vflip;
    mStates[name] = state;
}
bool Actor::move(int x, int y)
{
	mFrameCounter++;

	if (mState->delay > 0 && mFrameCounter % mState->delay == 0) 
		mAnimationFrame++;
	
	if (!mCheckForCollisions)
	{
		mX += x;
		mY += y;
		return false;
	}


	TileMap *tileMap = mRoom->getTileMap();

	bool result = false;

	mX += x;

	// Check collision left
	if (x < 0)
	{
		int x = mX / TileMap::TILE_SIZE;
		int y1 = mY / TileMap::TILE_SIZE;
		int y2 = (mY + mH - 1) / TileMap::TILE_SIZE;
		
		if (tileMap->isSolid(x, y1) || tileMap->isSolid(x, y2))
		{
			int depth = (x + 1) * TileMap::TILE_SIZE - mX;
			mX += depth;
			result = true;
		}
	}
	// Check collision right
	if (mState->x > 0)
	{
		int x = (mX + mW - 1) / TileMap::TILE_SIZE;
		int y1 = mY / TileMap::TILE_SIZE;
		int y2 = (mY + mH - 1) / TileMap::TILE_SIZE;
		
		if (tileMap->isSolid(x, y1) || tileMap->isSolid(x, y2))
		{
			int depth = (mX + mW) - x * TileMap::TILE_SIZE;
			mX -= depth;
			result = true;
		}
	}

	mY += y;

	// Check collision up
	if (y < 0)
	{
		int y = mY / TileMap::TILE_SIZE;
		int x1 = mX / TileMap::TILE_SIZE;
		int x2 = (mX + mW - 1) / TileMap::TILE_SIZE;
		
		if (tileMap->isSolid(x1, y) || tileMap->isSolid(x2, y))
		{
			int depth = (y + 1) * TileMap::TILE_SIZE - mY;
			mY += depth;
			result = true;
		}
	}

	// Check collision down
	if (y > 0)
	{
		int y = (mY + mH) / TileMap::TILE_SIZE;
		int x1 = mX / TileMap::TILE_SIZE;
		int x2 = (mX + mW - 1) / TileMap::TILE_SIZE;
		
		if (tileMap->isSolid(x1, y) || tileMap->isSolid(x2, y))
		{
			int depth = (mY + mH) - y * TileMap::TILE_SIZE;
			mY -= depth;
			result = true;
		}
	}

	mFlashFrames = max(mFlashFrames - 1, 0);
	mBlinkFrames = max(mBlinkFrames - 1, 0);

	return result;
}

bool Actor::move()
{
	return move(mState->x, mState->y);
}

Actor::Direction Actor::getDirection()
{
	return mDirection;
}

void Actor::flash(int frames)
{
	mFlashFrames = frames;
}

void Actor::blink(int frames)
{
	mBlinkFrames = frames;
}