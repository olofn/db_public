#ifndef DB_PLAYER_HPP
#define DB_PLAYER_HPP

#include <allegro.h>

#include "animation.hpp"
#include "entity.hpp"
#include "keystate.hpp"

class Player: public Entity
{
public:
	Player(int x, int y);
    ~Player();

	void logic(Level* level);

	void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
    bool isToBeDeleted() { return false; }
    bool drawInLayer(unsigned int layer) { return true; }
    void freeze();
    void unfreeze();
    bool isFreezed();
    void kill();
    bool isDead();
    bool isStunnedByElectric(Entity* entity);
    void message(const std::string& message, Entity* distributor);
    bool isLaserShielded();
    int getLaserShieldStatus();
    void setTotalStarsCollected(int total);

     enum State 
    {
	    GROUND,
	    AIR_UP,
	    AIR_DOWN,
	    DEAD,
        FROZEN
    };

    State getState() { return mState; }
    int getJumpY() { return mJumpY; }

protected:
    void drawPlayer(BITMAP* dest, int scrollx, int scrolly, unsigned int layer);

    int mDX;
    int mDY;
    bool mFacingLeft;
    bool mRunning;
    bool mJumpKeyHeld;
    bool mWallGliding;
    int mNumberOfJumps;
    State mState;
    KeyState mKeyState;
    int mLeftWallJumpCounter;
    int mRightWallJumpCounter;
    int mFrameCounter;
    Animation mRunningAnimation;
    Animation mJumpingAnimation;
    Animation mWallSmokeAnimation;
    Animation mElectricAnimation;
    int mLastY;
    SAMPLE* mJumpSample;
    SAMPLE* mElectricSample;
    bool mImmortal;
    int mElectricCounter;
    bool mLaserShielded;
    int mLaserShieldCounter;
    bool mCanPlaceBomb;
    int mTotalStarsCollected;
    int mJumpY;
    bool mShouldDieFromBomb;
};

#endif
