#include "keystate.hpp"

KeyState::KeyState() :
	mUp(false), mDown(false), mLeft(false), mRight(false),
	mFire(false), mJump(false), mSpecial(false), mImmortal(false), mLaserShield(false),
	mOldUp(false), mOldDown(false), mOldLeft(false), mOldRight(false),
    mOldFire(false), mOldJump(false), mOldSpecial(false), mOldImmortal(false), mOldLaserShield(false),
	mDisabled(false)
{
}

void KeyState::setKeys(bool up, bool down, bool left, bool right, 
                       bool fire, bool jump, bool special, bool immortal, bool laserShield)
{
	mOldUp = mUp;
	mOldDown = mDown;
	mOldLeft= mLeft;
	mOldRight = mRight;
	mOldFire= mFire;
	mOldJump = mJump;
	mOldSpecial = mSpecial;
    mOldImmortal = mImmortal;
    mOldLaserShield = mLaserShield;

	mUp = up;
	mDown = down;
	mLeft = left;
	mRight = right;
	mFire = fire;
	mJump = jump;
	mSpecial = special;
    mImmortal = immortal;
    mLaserShield = laserShield;
}

bool KeyState::isUpHeld() const
{
	return mUp && !mDisabled;
}

bool KeyState::isDownHeld() const
{
	return mDown && !mDisabled;
}

bool KeyState::isLeftHeld() const
{
	return mLeft && !mDisabled;
}

bool KeyState::isRightHeld() const
{
	return mRight && !mDisabled;
}

bool KeyState::isFireHeld() const
{
	return mFire && !mDisabled;
}

bool KeyState::isJumpHeld() const
{
	return mJump && !mDisabled;
}

bool KeyState::isSpecialHeld() const
{
	return mSpecial && !mDisabled;
}

bool KeyState::isImmortalHeld() const
{
	return mImmortal && !mDisabled;
}

bool KeyState::isLaserShieldHeld() const
{
	return mLaserShield && !mDisabled;
}

bool KeyState::isUpPressed() const
{
	return mUp && !mOldUp && !mDisabled;
}

bool KeyState::isDownPressed() const
{
	return mDown && !mOldDown && !mDisabled;
}

bool KeyState::isLeftPressed() const
{
	return mLeft && !mOldLeft && !mDisabled;
}

bool KeyState::isRightPressed() const
{
	return mRight && !mOldRight && !mDisabled;
}

bool KeyState::isFirePressed() const
{
	return mFire && !mOldFire && !mDisabled;
}

bool KeyState::isJumpPressed() const
{
	return mJump && !mOldJump && !mDisabled;
}

bool KeyState::isSpecialPressed() const
{
	return mSpecial && !mOldSpecial && !mDisabled;
}

bool KeyState::isImmortalPressed() const
{
	return mImmortal && !mOldImmortal && !mDisabled;
}

bool KeyState::isLaserShieldPressed() const
{
	return mLaserShield && !mOldLaserShield && !mDisabled;
}

bool KeyState::isDisabled() const
{
	return mDisabled;
}

void KeyState::setDisabled(bool disabled)
{
	mDisabled = disabled;
}
