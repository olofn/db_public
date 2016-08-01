#include <string>
#include <allegro.h>
#include <iostream>

#include "entities/player.hpp"
#include "resourcehandler.hpp"
#include "tilemap.hpp"
#include "room.hpp"
#include "entities/shot.hpp"
#include "entities/iceshot.hpp"
#include "entities/fireshot.hpp"
#include "exception.hpp"
#include "gamestatemanager.hpp"

namespace nmc
{
	const int JUMP_STRENGTH = 13;       // Higher = Jump higher
	const int MAX_AIR_SPEED = 7;        // Higher = Jump higher and faster
	const int JUMP_CONTROL = 4;         // Lower  = More exact control of jump height
	const int RUN_SPEED = 24;           // Higher = Run faster
	const int GROUND_ACCELERATION = 16; // Higher = Faster turning on ground
	const int AIR_ACCELERATION = 3;     // Higher = Faster turning in air
	const int ICE_ACCELERATION = 1;     // Higher = Faster turning in air
	const int CROUCH_SHRINK = 8;
	const int SHOT_DELAY = 10;
	const int SHOT_ANIMATION_LENGTH = 25;

	Player::Player(int x, int y) : Entity(x, y, 16, 32, true),
		mStandingAni("dante-standing.bmp"),
		mStandingShootingAni("dante-standing-shooting.bmp"),
		mRunningAni("dante-running.bmp"),
		mRunningShootingAni("dante-running-shooting.bmp"),
		mJumpingAni("dante-jumping.bmp"),
		mJumpingShootingAni("dante-jumping-shooting.bmp"),
		mCrouchingAni("dante-crouching.bmp"),
		mCrouchingShootingAni("dante-crouching-shooting.bmp"),
		mHurtAni("dante-hurt.bmp"),
		mShotFlareAni("flare.bmp")
	{
		mDY = 0;
		mDX = 0;
		setState(GROUND);
        mShotType = NORMAL;
		mJumpY = 0;
		mFacingLeft = false;
		mRunFrame = 0;
		mShotCounter = SHOT_ANIMATION_LENGTH + 1;
		mShootAfterDelay = false;
		mOnPlatform = false;
		mRunning = false;
		mCrouching = false;
		mHurt = false;
		mInvincibleCounter = 0;
		mMana = 12;
		mHealth = 12;
		mRegenerateManaCounter = 0;
	}

	Player::~Player() {
	}

	void Player::logic(Room *room)
	{
		//std::cout << "HP:" << getHealth() << " MP:" << getMana() << "/" << getMaximumMana() << " Couter:" << mRegenerateManaCounter << std::endl;
		mStateCounter++;		

		if (mInvincibleCounter > 0) {
			mInvincibleCounter--;
		}

		if (getState() == DEAD) {
			return;
		}

		regenerateMana();
		
		const KeyState &keys = room->getKeyState();
		TileMap *tileMap = room->getTileMap();

		bool onIce = isOnIce(tileMap);

		int acceleration = AIR_ACCELERATION;
		if (getState() == GROUND) {
			if (onIce) {
				acceleration = ICE_ACCELERATION;
			} else {
				acceleration = GROUND_ACCELERATION;
			}
		}

		if (keys.isLeftHeld() && !keys.isRightHeld() && !mHurt) {
			mDX -= acceleration;
			if (mDX < -RUN_SPEED) {
				mDX = -RUN_SPEED;
			}
			mRunFrame += onIce && mDX > -20 ? 3 : 2;
			mFacingLeft = true;
			mRunning = true;
		} else if (!keys.isLeftHeld() && keys.isRightHeld() && !mHurt) {
			mDX += acceleration;
			if (mDX > RUN_SPEED) {
				mDX = RUN_SPEED;
			}
			mRunFrame += onIce && mDX < 20 ? 3 : 2;
			mFacingLeft = false;
			mRunning = true;
		} else if (mDX > 0 && !mHurt) {
			mDX -= onIce ? 1 : 4;
			if (mDX < 0) {
				mDX = 0;
			}
			mRunning = false;
		} else if (mDX < 0 && !mHurt) {
			mDX += onIce ? 1 : 4;
			if (mDX > 0) {
				mDX = 0;
			}
			mRunning = false;
		} else {
			mRunning = false;
		}

		// Crouching
		if (!mRunning && keys.isDownHeld() && getState() == GROUND) {
			if (!mCrouching) {
				mCrouching = true;
				mY += CROUCH_SHRINK;
				mH -= CROUCH_SHRINK;
			}
		} else if (mCrouching) {
			mCrouching = false;
			mY -= CROUCH_SHRINK;
			mH += CROUCH_SHRINK;
		}
		

		if (mDX == 0 || getState() != GROUND) {
			mRunFrame = 0;
		}

		// Interrupting jumping
		if (!keys.isJumpHeld() && getState() == AIR_UP && mDY > JUMP_CONTROL && !mHurt) {
			mDY = JUMP_CONTROL;
		}

		if (!keys.isJumpHeld() && (getState() == AIR_UP || getState() == AIR_DOWN)) {
			mJumpKeyHeld = false;
		}

		// Jumping
		if (keys.isJumpPressed() && getState() == GROUND && !keys.isDownHeld()) {
			mDY = JUMP_STRENGTH;
			setState(AIR_UP);
			mJumpKeyHeld = true;
			mJumpY = getCenterY();
		}
		// Drop off platform
		if (keys.isJumpPressed() && mOnPlatform && keys.isDownHeld()) {
			mDY = 1;
			mY++;
			setState(AIR_DOWN);
			mJumpKeyHeld = true;
			mJumpY = getCenterY();
		}

		// Sideways movement
		if (onIce) {
			if (mDX < 0) {
				mX += (mDX - 7) / 8;
			} else {
				mX += (mDX + 7) / 8;
			}
		} else {
			mX += mDX / 8;
		}
		

		// Left Wall
        int solidLeftOffset;
		if (mDX < 0 && solidLeft(room, solidLeftOffset)) 
        {
			// Align player to solid object
			mX += solidLeftOffset;
            
            mDX = 0;
		}

		// Right Wall
        int solidRightOffset;
		if (mDX > 0 && solidRight(room, solidRightOffset)) 
        {
			// Align player to solid object
			mX -= solidRightOffset;
			mDX = 0;
		}

		// Vertical movement
		if (getState() == AIR_DOWN) {
			mY += mDY > MAX_AIR_SPEED ? MAX_AIR_SPEED : mDY;
		} else if (getState() == AIR_UP) {
			mY -= mDY > MAX_AIR_SPEED ? MAX_AIR_SPEED : mDY;
		}

		// Falling, acceleration
		if (getState() == AIR_DOWN) {
			mDY += 1;
		}

		// Raising, deacceleration
		if (getState() == AIR_UP) {
			mDY--;
			if (mDY < 0) {
				setState(AIR_DOWN);
				mDY = 0;
			}
		}

		// Ceiling bouncing
        int solidAboveOffset;
		if (getState() == AIR_UP && solidAbove(room, solidAboveOffset)) 
        {
			setState(AIR_DOWN);
			mDY = 0;
			// Align player to solid object
			mY += solidAboveOffset;
		}

		// Ground bouncing / landing
        int groundOffset;
		if (getState() == AIR_DOWN && isOnGround(room, groundOffset)) {
			if (keys.isJumpHeld() && !mJumpKeyHeld && !keys.isDownHeld()) {
				// Rejump
				mDY = JUMP_STRENGTH;
				setState(AIR_UP);
				mJumpKeyHeld = true;
			} else {
				// Land
				setState(GROUND);
				mDY = 0;				
			}
			mHurt = false;

			// Align to tile
			mY -= groundOffset;
			mJumpY = getCenterY();
		}

		// Falling
        int fallingOffset;
		if (getState() == GROUND && !isOnGround(room, fallingOffset)) {
			setState(AIR_DOWN);
			mDY = 0;
		}

		// Shooting
		if (keys.isFirePressed())	{
			if (mShotCounter >= SHOT_DELAY) {
				mShotCounter = 0;
				room->addEntity(createShot());
				mShootAfterDelay = false;
			} else {
				mShootAfterDelay = true;
			}
		}
		if (mShotCounter >= SHOT_DELAY && mShootAfterDelay) {
			mShotCounter = 0;
			room->addEntity(createShot());
			mShootAfterDelay = false;
		}
		
		mShotCounter++;


		if (keys.isSpecialPressed()) 
        {
		    if (mShotType == NORMAL)
            {
                mShotType = ICE;
            }
            else if (mShotType == ICE)
            {
                mShotType = FIRE;
            }
            else
            {
                mShotType = NORMAL;
            }
        }
	}

	void Player::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer) {		
		if ((mHurt || mInvincibleCounter > 0) && mStateCounter % 4 < 2) {
			return;
		}

		if (mHurt) {
			drawFrame(dest, mHurtAni, mStateCounter / 4, mFacingLeft, scrollx, scrolly);
			return;
		}

		if (getState() == GROUND) {
			if (!mRunning) {
				if (mCrouching) {
					if (mShotCounter < SHOT_ANIMATION_LENGTH) {
						drawFrame(dest, mCrouchingShootingAni, mStateCounter / 25, mFacingLeft, scrollx, scrolly);
					} else {
						drawFrame(dest, mCrouchingAni, mStateCounter / 25, mFacingLeft, scrollx, scrolly);
					}
				} else {
					if (mShotCounter < SHOT_ANIMATION_LENGTH) {
						drawFrame(dest, mStandingShootingAni, mStateCounter / 25, mFacingLeft, scrollx, scrolly);
					} else {
						drawFrame(dest, mStandingAni, mStateCounter / 25, mFacingLeft, scrollx, scrolly);
					}
				}
			} else {
				if (mShotCounter < SHOT_ANIMATION_LENGTH) {
					drawFrame(dest, mRunningShootingAni, mRunFrame / 6, mFacingLeft, scrollx, scrolly);
				} else {
					drawFrame(dest, mRunningAni, mRunFrame / 6, mFacingLeft, scrollx, scrolly);
				}
			}
		} else if (getState() == AIR_UP) {
			Animation *a = &mJumpingAni;
			if (mShotCounter < SHOT_ANIMATION_LENGTH) {
				a = &mJumpingShootingAni;
			}

			if (mStateCounter < 3) {
				drawFrame(dest, *a, 0, mFacingLeft, scrollx, scrolly - 2);
			} else if (mStateCounter < 6) {
				drawFrame(dest, *a, 1, mFacingLeft, scrollx, scrolly - 4);
			} else {
				drawFrame(dest, *a, 2, mFacingLeft, scrollx, scrolly - 6);
			}
		} else if (getState() == AIR_DOWN) {
			Animation *a = &mJumpingAni;
			if (mShotCounter < SHOT_ANIMATION_LENGTH) {
				a = &mJumpingShootingAni;
			}

			if (mStateCounter < 6) {
				drawFrame(dest, *a, 2, mFacingLeft, scrollx, scrolly - 6);
			} else if (mStateCounter < 8) {
				drawFrame(dest, *a, 3, mFacingLeft, scrollx, scrolly - 5);
			} else if (mStateCounter < 10) {
				drawFrame(dest, *a, 4, mFacingLeft, scrollx, scrolly - 5);
			} else {
				int frame = 5 + (mStateCounter % 4)/2;
				drawFrame(dest, *a, frame, mFacingLeft, scrollx, scrolly - 5);
			}
		}

		if (mShotCounter <= 6) {
			int f = mShotCounter;
			int x = mRunning ? 26 : 24;			
			int y = 7;
			if (mCrouching || mRunning) {
				y = 9;
			}
			if (mFacingLeft) {
				x = mRunning ? -18 : -16;
			}
			mShotFlareAni.drawFrame(dest, f, mX + x - scrollx, mY + y - scrolly, mFacingLeft);
		}
		
		//rect(dest, mX -scrollx, mY - scrolly, mX -scrollx + mW - 1, mY - scrolly + mH - 1, makecol(255,100,155));
	}
		

	void Player::setState(State newState) {
		if (mState == newState) {
			return;
		}
   
		mState = newState;
		mStateCounter = 0;
	}

	Player::State Player::getState() {
		return mState;
	}

	bool Player::isToBeDeleted() {
		return false;
	}

	int Player::getJumpY() {
		return mJumpY;
	}

	void Player::drawFrame(BITMAP *dest, Animation &src, int frame, bool hflip, int scrollx, int scrolly) {		
		int destX = mX - src.getFrameWidth() / 2 + mW / 2 - scrollx;
		int destY = mY - src.getFrameHeight() + mH - scrolly;
		src.drawFrame(dest, frame, destX, destY, hflip);
		//rect(dest, destX, destY, destX + frameSize - 1, destY + frameSize - 1, makecol(255,255,255));
	}

	Entity *Player::createShot() {
		int size = 6;
		int x, dx, y;

		if (mFacingLeft) {
			x = -size;
			dx = -1;
		} else {
			x = mW - 1;
			dx = 1;
		}

		y = mCrouching ? 10 : 10;

		switch (mShotType)
		{
		case NORMAL:
			return new Shot(x + mX, mY + y, "shot.bmp", "hit.bmp", size, dx*7, 0, 320/7, true);
		case ICE:
			return new IceShot(x + mX, mY + y, "iceshot.bmp", "hit.bmp", size, dx*7, 0, 320/7, true);
		case FIRE:
			return new FireShot(x + mX, mY + y, "fireshot.bmp", "hit.bmp", size, dx*2, 0, 320/2, true);
		default:
			throw NMC_EXCEPTION("Illegal shot type");
		}
	}

	void Player::setPosition(int x, int y) 
    {
		mX = x;
		mY = y;
		mJumpY = 0;
	}

	bool Player::isOnGround(Room* room, int& offset) 
    {
		mOnPlatform = false;

		if (solidBelow(room, offset)) 
        {
			return true;
		}
		
		if ((mDY == 0 && getState() == GROUND) || (mY - mDY + mH) / 16 < (mY  + mH) / 16) 
        {
			if (platformBelow(room, offset)) 
            {
				mOnPlatform = true;
				return true;
			}
		}
		return false;
	}

	bool Player::isOnIce(TileMap *tileMap) {
		int minX = mX / 16;
		int maxX = (mX + mW - 1) / 16;
		int x;
		int y = (mY + mH) / 16;
		for (x = minX; x <= maxX; x++)
		{
			if (tileMap->getTileFlags(x, y) & TileMap::ICE)
			{
				return true;
			}
		}
		return false;
	}

	void Player::damage(Entity *e, int amount) {
		if (mHurt || mInvincibleCounter > 0) {
			return;
		}

		if (mFacingLeft) {
			mDX = 20;
			mDY = 5;
			setState(AIR_UP);
		} else {
			mDX = -20;
			mDY = 5;
			setState(AIR_UP);
		}

		mHurt = true;
		mInvincibleCounter = 40;

		decreaseManaOrHealth(amount);
	}

	int Player::getHealth()
	{
		return mHealth;
	}

	void Player::setHealth(int health)
	{
		mHealth = health;
	}

	int Player::getMaximumHealth()
	{
		return GameStateManager::getInstance()->getCurrent()->getInt("maxHealth");
	}

	void Player::setMaximumHealth(int maximumHealth)
	{
		GameStateManager::getInstance()->getCurrent()->setInt("maxHealth", maximumHealth);
	}

	int Player::getMana()
	{
		return mMana;
	}

	void Player::setMana(int mana)
	{
		mMana = mana;
	}

	int Player::getMaximumMana()
	{
		return GameStateManager::getInstance()->getCurrent()->getInt("maxMana");
	}

	void Player::setMaximumMana(int maximumMana)
	{
		GameStateManager::getInstance()->getCurrent()->setInt("maxMana", maximumMana);
	}

	void Player::decreaseManaOrHealth(int amount)
	{
        setHealth(getHealth() - amount);

        /*
		int newMana = getMana() - amount;
		int newHealth = getHealth();

		if (newMana < 0)
		{
			newHealth += newMana;
			newMana = 0;
		}

		setHealth(newHealth);
		setMana(newMana);

		mRegenerateManaCounter = -80;
        */
	}

	void Player::regenerateMana()
	{
		if (mRegenerateManaCounter >= 0)
		{
			if (getMana() < getMaximumMana() && (mRegenerateManaCounter % 20 == 0))
			{
				setMana(getMana() + 1);
			}
		}

		mRegenerateManaCounter++;
	}
}