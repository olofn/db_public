#ifndef DB_KEYSTATE_HPP
#define DB_KEYSTATE_HPP

class KeyState
{
public:
	KeyState();

	void setKeys(bool up, bool down, bool left, bool right, 
                 bool fire, bool action, bool special, bool inventory);
	
	bool isUpHeld() const;
	bool isDownHeld() const;
	bool isLeftHeld() const;
	bool isRightHeld() const;
	bool isFireHeld() const;
	bool isActionHeld() const;
	bool isSpecialHeld() const;
    bool isInventoryHeld() const;

	bool isUpPressed() const;
	bool isDownPressed() const;
	bool isLeftPressed() const;
	bool isRightPressed() const;
	bool isFirePressed() const;
	bool isActionPressed() const;
	bool isSpecialPressed() const;
    bool isInventoryPressed() const;

	bool isDisabled() const;
	void setDisabled(bool disabled);

protected:
	bool mUp, mDown, mLeft, mRight, mFire, mAction, mSpecial, mInventory;
	bool mOldUp, mOldDown, mOldLeft, mOldRight, mOldFire, mOldAction, mOldSpecial, mOldInventory;
	bool mDisabled;
};

#endif