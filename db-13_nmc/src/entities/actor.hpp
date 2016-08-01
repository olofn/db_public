#ifndef NMC_ACTOR_HPP
#define NMC_ACTOR_HPP

#include <map>
#include <string>

#include "entity.hpp"
#include "animation.hpp"

namespace nmc
{
	class Actor : public Entity
	{
	public:
		Actor(const std::string &id, int x, int y);

		~Actor();

		virtual const std::string &getId();

		virtual void setAnimationOffset(int animationOffsetX, int animationOffsetY);

		virtual void insertAnimation(const std::string &name, const std::string &file);

		virtual void playAnimation(const std::string &name,
			                       int frameDelay,
								   bool hflip = false,
								   bool vflip = false,
								   bool looped = true);

		virtual void playAnimation(const std::string &name,
		                           int frameDelay,
								   int fromFrame,
								   int toFrame,
								   bool hflip = false,
								   bool vflip = false,
								   bool looped = true);

		virtual void move(int destinationX, int destinationY, int frames, bool absolute = false);
		
		virtual void moveX(int destinationX, int frames, bool absolute = false);
		
		virtual void moveY(int destinationY, int frames, bool absolute = false);

		virtual void remove();

		virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

		virtual void logic(Room *room);

		virtual bool isToBeDeleted();

		static Actor *createPlayerActor(int x, int y);

	private:
		std::string mId;
		std::map<std::string, Animation*> mAnimations;		
		int mAnimationOffsetX, mAnimationOffsetY;

		// For animation
		Animation *mCurrentAnimation;
		int mFromFrame, mToFrame;
		int mFrameDelay;
		bool mLooped;
		bool mHFlip, mVFlip;
		
		// For movement
		int mOriginX, mOriginY;
		int mDestinationX, mDestinationY;
		int mMovementFrames;

		bool mRemoved;

		// State variables
		bool mMoving;
		int mFrameCounter;
		int mMoveCounter;
	};
}

#endif