#ifndef NMC_KEYSTATE_HPP
#define NMC_KEYSTATE_HPP

namespace nmc
{
	class KeyState
	{
	public:
		KeyState();

		void setKeys(bool up, bool down, bool left, bool right, bool fire, bool jump, bool special);
		
		bool isUpHeld() const;
		bool isDownHeld() const;
		bool isLeftHeld() const;
		bool isRightHeld() const;
		bool isFireHeld() const;
		bool isJumpHeld() const;
		bool isSpecialHeld() const;
		
		bool isUpPressed() const;
		bool isDownPressed() const;
		bool isLeftPressed() const;
		bool isRightPressed() const;
		bool isFirePressed() const;
		bool isJumpPressed() const;
		bool isSpecialPressed() const;

		bool isDisabled() const;
		void setDisabled(bool disabled);

	protected:
		bool mUp, mDown, mLeft, mRight, mFire, mJump, mSpecial;
		bool mOldUp, mOldDown, mOldLeft, mOldRight, mOldFire, mOldJump, mOldSpecial;
		bool mDisabled;
	};
}

#endif