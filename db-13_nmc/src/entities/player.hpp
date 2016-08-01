#ifndef NMC_PLAYER_HPP
#define NMC_PLAYER_HPP

#include "entity.hpp"
#include "animation.hpp"

namespace nmc
{
	class Player : public Entity
	{
	public:
		enum State {
			GROUND,
			AIR_UP,
			AIR_DOWN,
			DEAD
		};

        enum ShotType
        {
            NORMAL,
            ICE,
            FIRE
        };

		Player(int x = 0, int y = 0);

		virtual ~Player();

		virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

		virtual void logic(Room *room);

		virtual State getState();

		virtual bool isToBeDeleted();

		virtual int getJumpY();

		virtual void setPosition(int x, int y);

		virtual void damage(Entity *e, int amount);

		virtual int getHealth();

		virtual void setHealth(int health);

		virtual int getMaximumHealth();

		virtual void setMaximumHealth(int maximumHealth);

		virtual int getMana();		

		virtual void setMana(int Mana);

		virtual int getMaximumMana();

		virtual void setMaximumMana(int maximumMana);

		virtual void decreaseManaOrHealth(int amount);

		virtual void regenerateMana();

	protected:
		virtual void setState(State state);

		virtual void drawFrame(BITMAP *dest, Animation &src, int frame, bool hflip, int scrollx, int scrolly);

		virtual Entity *createShot();

		virtual bool isOnGround(Room* room, int& offset);

		virtual bool isOnIce(TileMap *tileMap);

		int mDX, mDY;
		int mJumpY;
		bool mJumpKeyHeld;
		bool mFacingLeft;
		int mStateCounter;
		int mRunFrame;
		int mShotCounter;
		bool mOnPlatform;
		bool mRunning;
		bool mCrouching;
		bool mHurt;
		int mInvincibleCounter;
		int mHealth;
		int mMana;
		int mRegenerateManaCounter;
		bool mShootAfterDelay;
       
		State mState;
        ShotType mShotType;

		Animation mStandingAni;
		Animation mStandingShootingAni;
		Animation mRunningAni;
		Animation mRunningShootingAni;
		Animation mJumpingAni;
		Animation mJumpingShootingAni;
		Animation mCrouchingAni;
		Animation mCrouchingShootingAni;
		Animation mHurtAni;
		Animation mShotFlareAni;
	};
}

#endif