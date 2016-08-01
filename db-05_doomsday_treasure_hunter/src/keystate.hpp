#ifndef DB_KEYSTATE_HPP
#define DB_KEYSTATE_HPP

class KeyState
{
public:
	KeyState();

	void setKeys(bool up, bool down, bool left, bool right, 
                 bool fire, bool jump, bool special, bool immortal, bool laserShield);
	
	bool isUpHeld() const;
	bool isDownHeld() const;
	bool isLeftHeld() const;
	bool isRightHeld() const;
	bool isFireHeld() const;
	bool isJumpHeld() const;
	bool isSpecialHeld() const;
    bool isImmortalHeld() const;
	bool isLaserShieldHeld() const;

	bool isUpPressed() const;
	bool isDownPressed() const;
	bool isLeftPressed() const;
	bool isRightPressed() const;
	bool isFirePressed() const;
	bool isJumpPressed() const;
	bool isSpecialPressed() const;
    bool isImmortalPressed() const;
    bool isLaserShieldPressed() const;

	bool isDisabled() const;
	void setDisabled(bool disabled);

protected:
	bool mUp, mDown, mLeft, mRight, mFire, mJump, mSpecial, mImmortal, mLaserShield;
	bool mOldUp, mOldDown, mOldLeft, mOldRight, mOldFire, mOldJump, mOldSpecial, mOldImmortal, mOldLaserShield;
	bool mDisabled;
};

#endif
