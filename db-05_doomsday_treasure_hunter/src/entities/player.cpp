#include "entities/player.hpp"

#include "level.hpp"
#include "resourcehandler.hpp"
#include "blending.hpp"
#include "entities/bomb.hpp"

#include <iostream>

#include <cmath>

const int JUMP_CONTROL = 3; 
const int JUMP_STRENGTH = 10;
const int MAX_AIR_SPEED = 6;
const int WALL_GLIDE_MAX_AIR_SPEED = 3;
const int RUN_SPEED = 23; 
const int GROUND_ACCELERATION = 16;

const int STARS_FOR_LASER_SHEILD = 30;
const int STARS_FOR_BOMB = 18;
const int STARS_FOR_ELECTRIC = 22;

Player::Player(int x, int y)
:Entity(x, y, 16, 16, true),
mRunningAnimation("playerrunning.bmp"),
mJumpingAnimation("playerjumping.bmp"),
mWallSmokeAnimation("playerwallsmoke.bmp"),
mElectricAnimation("playerelectric.bmp")
{
    mDX = 0;
    mDY = 0;
    mState = GROUND;
    mLeftWallJumpCounter = 0;
    mRightWallJumpCounter = 0;
    mFrameCounter = 0;
    mJumpSample = ResourceHandler::getInstance()->getSample("jump.wav");
    mElectricSample = ResourceHandler::getInstance()->getSample("electric.wav");
    mNumberOfJumps = 0;
    mImmortal = false;
    mElectricCounter = 100;
    mLaserShielded = false;
    mLaserShieldCounter = 500;
    mCanPlaceBomb = true;
    mJumpY = 0;
    mFrameCounter = 0;
    mShouldDieFromBomb = false;
    mFacingLeft = false;
}

Player::~Player()
{
    
}

bool Player::isLaserShielded()
{
    return mLaserShielded;
}

bool Player::isFreezed()
{
    return mState == FROZEN;
}

int Player::getLaserShieldStatus()
{
    if (mLaserShieldCounter > 500)
        return 100;
    if (mLaserShieldCounter < 0)
        return 0;
    else
        return mLaserShieldCounter / 5;
}

void Player::setTotalStarsCollected(int total)
{
    mTotalStarsCollected = total;
}

bool Player::isDead()
{
    return mState == DEAD;
}

void Player::freeze()
{
    mState = FROZEN;
}
void Player::unfreeze()
{
    mState = GROUND;
}

void Player::kill()
{
    if (mImmortal)
        return;
    mState = DEAD;
}

void Player::logic(Level* level)
{
    if (mState == FROZEN || mState == DEAD)
        return;

    mFrameCounter++;
    mElectricCounter++;

    if (mShouldDieFromBomb && mFrameCounter > 10)
        kill();

    if (mLaserShielded)
        mLaserShieldCounter--;
    else
        mLaserShieldCounter++;

    mFrameCounter++;
    mLeftWallJumpCounter--;
    mRightWallJumpCounter--;
    mKeyState.setKeys(key[KEY_UP], 
                      key[KEY_DOWN], 
                      key[KEY_LEFT], 
                      key[KEY_RIGHT],
		              key[KEY_LCONTROL], 
                      key[KEY_ALT], 
                      key[KEY_LSHIFT],
                      key[KEY_I],
                      key[KEY_SPACE]);	

    // Become immortal
    if (mKeyState.isImmortalPressed())
    {
        mImmortal = !mImmortal;
    }

     // Become laser shielded
    if (mKeyState.isLaserShieldPressed() 
        && mLaserShieldCounter > 500 
        && !mLaserShielded
        && STARS_FOR_LASER_SHEILD <= mTotalStarsCollected)
    {
        //play_sample(mElectricSample, 100, 128, 1000, 0);
        mLaserShieldCounter = 500;
        mLaserShielded = true;
        play_sample(mElectricSample, 150, 128, 400, 0);
       // level->distributeMessage("playerelectric", this);
    }

    if (mLaserShielded && mLaserShieldCounter < 0)
    {
        mLaserShielded = false;
        mLaserShieldCounter = 0;
    }

    // Become electric
    if (mKeyState.isFirePressed() 
        && mElectricCounter > 100 
        && !mLaserShielded
        &&  STARS_FOR_ELECTRIC <= mTotalStarsCollected)
    {
        play_sample(mElectricSample, 100, 128, 1000, 0);
        mElectricCounter = 0;
    }

    if (mElectricCounter < 15)
         level->distributeMessage("playerelectric", this);

    // Place a bomb
    if (mKeyState.isSpecialPressed() 
        && !mLaserShielded 
        && mCanPlaceBomb
        && STARS_FOR_BOMB <= mTotalStarsCollected)
    {
        level->addEntity(new Bomb(getX(), getY()));
        mCanPlaceBomb = false;
    }

    // Move left
    if (mKeyState.isLeftHeld() && !mKeyState.isRightHeld() && mLeftWallJumpCounter < 0) 
    {
		mDX -= GROUND_ACCELERATION;
		if (mDX < -RUN_SPEED) 
        {
			mDX = -RUN_SPEED;
		}

		mFacingLeft = true;
		mRunning = true;
	} 
    // Move right
    else if (!mKeyState.isLeftHeld() && mKeyState.isRightHeld() && mRightWallJumpCounter < 0) 
    {
		mDX += GROUND_ACCELERATION;
		if (mDX > RUN_SPEED) 
        {
			mDX = RUN_SPEED;
		}

		mFacingLeft = false;
		mRunning = true;
	} 
    else if (mDX > 0) 
    {
		mDX -= 4;
		if (mDX < 0)
        {
			mDX = 0;
		}
		mRunning = false;
	} 
    else if (mDX < 0) 
    {
		mDX += 4;
		if (mDX > 0) 
        {
			mDX = 0;
		}
		mRunning = false;
	} 
    else 
    {
		mRunning = false;
	}

	mX += mDX / 8;

	if (!mKeyState.isJumpHeld() && mState == AIR_UP 
        && mDY > JUMP_CONTROL) 
    {
		mDY = JUMP_CONTROL;
	}

	if (!mKeyState.isJumpHeld() && (mState == AIR_UP || mState == AIR_DOWN)) 
    {
		mJumpKeyHeld = false;
	}

    // Right collision
    if (mDX > 0 && level->getTileMap()->isRightSolid(this)) 
    {
        level->getTileMap()->alignToRightTile(this);
        mDX = 0;
	}

    // Left collision
    if (mDX < 0 && level->getTileMap()->isLeftSolid(this)) 
    {
        level->getTileMap()->alignToLeftTile(this);
        mDX = 0;
	}


    // Jumping from left wall
    if (mKeyState.isJumpPressed() 
        && mState == AIR_DOWN
        && !mKeyState.isDownHeld()
        && (mKeyState.isRightHeld() || mKeyState.isRightPressed() || mKeyState.isUpHeld() || mKeyState.isUpPressed())
        && level->getTileMap()->isPeekLeftSolid(this)
        && !level->getTileMap()->isPeekAboveSolid(this)) 
    {
		mDY = JUMP_STRENGTH;
        mDX = RUN_SPEED*2 + 3;
		mState = AIR_UP;
		mJumpKeyHeld = true;
        mLeftWallJumpCounter = 15;
        mFacingLeft = false;
        play_sample(mJumpSample, 100, 128, 1000, 0);
        mJumpY = getCenterY();
        mNumberOfJumps = 1;
	}

    // Jumping from right wall
    else if (mKeyState.isJumpPressed() 
        && mState == AIR_DOWN
        && !mKeyState.isDownHeld()
        && (mKeyState.isLeftHeld() || mKeyState.isLeftPressed() || mKeyState.isUpHeld() || mKeyState.isUpPressed())
        && level->getTileMap()->isPeekRightSolid(this)
        && !level->getTileMap()->isPeekAboveSolid(this)) 
    {
		mDY = JUMP_STRENGTH;
        mDX = -RUN_SPEED*2 - 3;
		mState = AIR_UP;
		mJumpKeyHeld = true;
        mRightWallJumpCounter = 15;
        mFacingLeft = true;
        play_sample(mJumpSample, 100, 128, 1000, 0);
        mJumpY = getCenterY();
        mNumberOfJumps = 1;
	}        
    // Jumping in mid air
    else if (mKeyState.isJumpPressed() 
        && mState == AIR_DOWN
        && !mKeyState.isDownHeld()
        && mNumberOfJumps == 1) 
    {
		mDY = JUMP_STRENGTH;
		mState = AIR_UP;
		mJumpKeyHeld = true;
        play_sample(mJumpSample, 100, 128, 1000, 0);
        mNumberOfJumps++;
        mJumpY = getCenterY();
	}
    // Jumping from ground
	else if (mKeyState.isJumpPressed() 
            && mState == GROUND 
            && !mKeyState.isDownHeld()) 
    {
		mDY = JUMP_STRENGTH;
		mState = AIR_UP;
		mJumpKeyHeld = true;
        play_sample(mJumpSample, 100, 128, 1000, 0);
        mJumpY = getCenterY();
        mNumberOfJumps++;
	}

    if (mState == AIR_DOWN && mWallGliding)
    {
		mY += mDY > WALL_GLIDE_MAX_AIR_SPEED ? WALL_GLIDE_MAX_AIR_SPEED : mDY;
    } 
    else if (mState == AIR_DOWN)
    {
	    mY += mDY > MAX_AIR_SPEED ? MAX_AIR_SPEED : mDY;
    }
    else if (mState == AIR_UP) 
    {
		mY -= mDY > MAX_AIR_SPEED ? MAX_AIR_SPEED : mDY;
	}

	if (mState == AIR_DOWN) 
    {
		mDY += 1;
	}

	if (mState == AIR_UP) 
    {
		mDY--;
		if (mDY < 0) 
        {
			mState = AIR_DOWN;
			mDY = 0;
		}
	}

    // Ceiling collision
    
    if (mState == AIR_UP
        && (level->getTileMap()->isAboveSolid(this)))
       // && mLeftWallJumpCounter < 0
        //&& mRightWallJumpCounter < 0) 
        
    {
		mState = AIR_DOWN;
		mDY = 0;
        level->getTileMap()->alignToAboveTile(this);
	}

    // Ground collision
    if (mState == AIR_DOWN && level->getTileMap()->isOnGround(this)) 
    {
	    if (mKeyState.isJumpHeld() && !mJumpKeyHeld && !mKeyState.isDownHeld()) 
        {
		   // mDY = JUMP_STRENGTH;
		   // mState = AIR_UP;
		   // mJumpKeyHeld = true;
	    } 
        else 
        {
			mState = GROUND;
			mDY = 0;				
        }
			
         mJumpY = getCenterY();
        level->getTileMap()->alignToGroundTile(this);
    }
    
	if (mState == GROUND && !level->getTileMap()->isOnGround(this)) 
    {
		mState = AIR_DOWN;
		mDY = 0;
	}

    mWallGliding = mLastY - mY < 0
                    && !level->getTileMap()->isOnGround(this) 
                    && (level->getTileMap()->isPeekRightSolid(this) || level->getTileMap()->isPeekLeftSolid(this));

   
    if (mWallGliding && (level->getTileMap()->isPeekRightSolid(this)))
        mFacingLeft = true;
    else if (mWallGliding)
        mFacingLeft = false;

    mLastY = mY;

    if (mState == GROUND)
        mNumberOfJumps = 0;
}

void Player::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
{
    /*
    if (layer == Entity::AFTER_TILES_LAYER)
         circlefill(dest, 
                   getX() - scrollx + 8, 
                   getY() - scrolly + 8,
                   48, 
                   0);
                   */

    if (layer == Entity::AFTER_TILES_LAYER)
    {
        if (!mImmortal || mFrameCounter % 4  < 2)
        {
            drawPlayer(dest, scrollx, scrolly, layer);
        }

        /*
        rect(dest, 
             mX - scrollx, 
             mY - scrolly, 
             mX - scrollx + mW - 1,
             mY - scrolly + mH - 1,
             makecol(255, 0, 0));
             */    
    }

}

void Player::drawPlayer(BITMAP* dest, int scrollx, int scrolly, unsigned int layer)
{
    if (mLaserShielded)
    {
        int w = (500 - mLaserShieldCounter)*4;
        
        if (w > 78)
            w = 78;

        circlefill(dest, mX - scrollx + 8, mY  - scrolly + 8, w, 0);
    }

    if (mState == DEAD || mState == FROZEN)
    {
        mRunningAnimation.drawFrame(dest, 0, getX() - scrollx - 8, getY() - scrolly - 8, mFacingLeft);
        return;
    }

    Animation::Blending b = mElectricCounter < 100 && mElectricCounter % 10 < 5 ? Animation::FROZEN : Animation::NONE;

    if (mRunning && mState == GROUND)
        mRunningAnimation.drawFrame(dest, mFrameCounter / 5, getX() - scrollx - 8, getY() - scrolly - 8, mFacingLeft, false, b);
    else if (mState == GROUND)
        mRunningAnimation.drawFrame(dest, 0, getX() - scrollx - 8, getY() - scrolly - 8, mFacingLeft, false, b);
    else if (mState == AIR_UP)
         mJumpingAnimation.drawFrame(dest, 0, getX() - scrollx - 8, getY() - scrolly - 8, mFacingLeft, false, b);
    else if (mState == AIR_DOWN)
         mJumpingAnimation.drawFrame(dest, 1, getX() - scrollx - 8, getY() - scrolly - 8, mFacingLeft, false, b);

    if (mWallGliding)
        mWallSmokeAnimation.drawFrame(dest, mFrameCounter / 5, getX() - scrollx, getY() - scrolly, !mFacingLeft);

    if (mElectricCounter < 15)
    {
        mElectricAnimation.drawFrame(dest, 
                                     mFrameCounter, 
                                     getX() - scrollx - 24, 
                                     getY() - scrolly - 24,
                                     mFrameCounter % 2 == 0,
                                     mFrameCounter % 3 < 2,
                                     Animation::ADD);
    }
}

bool Player::isStunnedByElectric(Entity* entity)
{
    int dx = mX - entity->getX();
    int dy = mY - entity->getY();
    float length = std::sqrt((float)dx*dx + (float)dy*dy);
    float distance = length / 16.0f;
    return distance < 2.5f;
}

void Player::message(const std::string& message, Entity* distributor)
{
    if (message == "bombexplosion")
    {
        mCanPlaceBomb = true;
        Bomb* bomb = (Bomb*)distributor;

        if (bomb->getExplosionImpact(this) > 2.0f)
        {
            mShouldDieFromBomb = true;
            mFrameCounter = 0;
        }
    }
}
