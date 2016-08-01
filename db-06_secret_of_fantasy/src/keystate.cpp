#include "keystate.hpp"

KeyState::KeyState() :
	mUp(false), 
	mDown(false), 
	mLeft(false), 
	mRight(false),
	mFire(false), 
	mAction(false), 
	mSpecial(false), 
	mInventory(false),
	mOldUp(false), 
	mOldDown(false), 
	mOldLeft(false), 
	mOldRight(false),
    mOldFire(false), 
	mOldAction(false), 
	mOldSpecial(false), 
	mOldInventory(false),
	mDisabled(false)
{
}

void KeyState::setKeys(bool up, bool down, bool left, bool right, 
                       bool fire, bool action, bool special, bool inventory)
{
	mOldUp = mUp;
	mOldDown = mDown;
	mOldLeft= mLeft;
	mOldRight = mRight;
	mOldFire= mFire;
	mOldAction = mAction;
	mOldSpecial = mSpecial;
    mOldInventory = mInventory;

	mUp = up;

	mDown = down;
	mLeft = left;
	mRight = right;
	mFire = fire;
	mAction = action;
	mSpecial = special;
    mInventory = inventory;
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

bool KeyState::isActionHeld() const
{
	return mAction && !mDisabled;
}

bool KeyState::isSpecialHeld() const
{
	return mSpecial && !mDisabled;
}

bool KeyState::isInventoryHeld() const
{
	return mInventory && !mDisabled;
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

bool KeyState::isActionPressed() const
{
	return mAction && !mOldAction && !mDisabled;
}

bool KeyState::isSpecialPressed() const
{
	return mSpecial && !mOldSpecial && !mDisabled;
}

bool KeyState::isInventoryPressed() const
{
	return mInventory && !mOldInventory && !mDisabled;
}

bool KeyState::isDisabled() const
{
	return mDisabled;
}

void KeyState::setDisabled(bool disabled)
{
	mDisabled = disabled;
}