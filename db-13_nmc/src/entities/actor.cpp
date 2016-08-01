#include "entities/actor.hpp"
#include "room.hpp"
#include "exception.hpp"

namespace nmc
{
	Actor::Actor(const std::string &id, int x, int y) : 
		Entity(x, y),
		mId(id),
		mCurrentAnimation(NULL),
		mAnimationOffsetX(0),
		mAnimationOffsetY(0),
		mFromFrame(0),
		mToFrame(0),
		mFrameDelay(1),
		mLooped(true),
		mHFlip(false),
		mVFlip(false),
		mOriginX(x),
		mOriginY(y),
		mDestinationX(x),
		mDestinationY(y),
		mMovementFrames(1),
		mRemoved(false),
		mMoving(false),
		mFrameCounter(0),
		mMoveCounter(0)
	{
	}

	Actor::~Actor()
	{
		std::map<std::string, Animation*>::iterator it;

		for (it = mAnimations.begin(); it != mAnimations.end(); it++)
		{
			delete it->second;
		}
	}

	const std::string &Actor::getId()
	{
		return mId;
	}

	void Actor::setAnimationOffset(int animationOffsetX, int animationOffsetY)
	{
		mAnimationOffsetX = animationOffsetX;
		mAnimationOffsetY = animationOffsetY;
	}

	void Actor::insertAnimation(const std::string &name, const std::string &file)
	{
		if (mAnimations.find(name) != mAnimations.end())
		{
			throw NMC_EXCEPTION("The animation '" + name + "' already exists");
		}

		mAnimations[name] = new Animation(file);

		if (mCurrentAnimation == NULL)
		{
			mCurrentAnimation = mAnimations[name];
		}
	}

	void Actor::playAnimation(const std::string &name, int frameDelay, bool hflip, bool vflip, bool looped)
	{
		playAnimation(name, frameDelay, 0, mAnimations[name]->getFrameCount() - 1, hflip, vflip, looped);
	}

	void Actor::playAnimation(const std::string &name, int frameDelay, int fromFrame, int toFrame, bool hflip, bool vflip, bool looped)
	{
		mFrameDelay = frameDelay;
		mFromFrame = fromFrame;
		mToFrame = toFrame;
		mLooped = looped;
		mFrameCounter = 0;
		mCurrentAnimation = mAnimations[name];
		mHFlip = hflip;
		mVFlip = vflip;
	}

	void Actor::move(int destinationX, int destinationY, int frames, bool absolute)
	{
		mOriginX = mX;
		mOriginY = mY;
		mDestinationX = destinationX;
		mDestinationY = destinationY;
		if (!absolute)
		{
			mDestinationX += mX;
			mDestinationY += mY;
		}
		mMovementFrames = frames;
		mMoveCounter = 0;
		mMoving = true;
	}

	void Actor::moveX(int destinationX, int frames, bool absolute)
	{
		move(destinationX, absolute ? mY : 0, frames, absolute);
	}
		
	void Actor::moveY(int destinationY, int frames, bool absolute)
	{
		move(absolute ? mX : 0, destinationY, frames, absolute);
	}

	void Actor::remove()
	{
		mRemoved = true;
	}

	void Actor::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
	{
		if (mRemoved)
		{
			return;
		}

		if (mCurrentAnimation == NULL)
		{
			throw NMC_EXCEPTION("No animation set!");
		}

		int frame = mFrameCounter / mFrameDelay;

		if (mLooped)
		{
			frame = (frame % (mToFrame - mFromFrame + 1)) + mFromFrame;
		}
		else
		{
			frame += mFromFrame;

			if (frame > mToFrame)
			{
				frame = mToFrame;
			}
		}
		
		mCurrentAnimation->drawFrame(dest,
			                         frame,
									 mX + mAnimationOffsetX - scrollx,
									 mY + mAnimationOffsetY - scrolly,
									 mHFlip,
									 mVFlip);
	}

	void Actor::logic(Room *room)
	{
		mFrameCounter++;		

		if (mMoving)
		{
			mMoveCounter++;
			
			mX = (mOriginX * (mMovementFrames - mMoveCounter) +
				  mDestinationX * mMoveCounter) / mMovementFrames;
			mY = (mOriginY * (mMovementFrames - mMoveCounter) +
				  mDestinationY * mMoveCounter) / mMovementFrames;

			if (mMoveCounter >= mMovementFrames)
			{
				mMoving = false;
				mX = mDestinationX;
				mY = mDestinationY;
			}
		}
	}

	bool Actor::isToBeDeleted()
	{
		return mRemoved;
	}

	Actor *Actor::createPlayerActor(int x, int y)
	{
		Actor *a = new Actor("player", x, y);
		
		a->setAnimationOffset(-16, -16);

		a->insertAnimation("standing", "dante-standing.bmp");
		a->insertAnimation("running", "dante-running.bmp");
		a->insertAnimation("jumping", "dante-jumping.bmp");
		a->insertAnimation("crouching", "dante-crouching.bmp");
		a->insertAnimation("hurt", "dante-hurt.bmp");
		a->insertAnimation("talking", "dante-talking.bmp");

		a->insertAnimation("standing-shooting", "dante-standing-shooting.bmp");
		a->insertAnimation("running-shooting", "dante-running-shooting.bmp");	
		a->insertAnimation("jumping-shooting", "dante-jumping-shooting.bmp");		
		a->insertAnimation("crouching-shooting", "dante-crouching-shooting.bmp");

		return a;
	}
}