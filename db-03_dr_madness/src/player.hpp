#ifndef DBSH07_PLAYER_HPP
#define DBSH07_PLAYER_HPP

#include "entity.hpp"
#include "animation.hpp"

class Player: public Entity
{
public:
    Player();
    ~Player();
    void reset();
    void draw(BITMAP *dest, int scrolly, unsigned int layer);
    void logic(Level* level);
    bool isToBeDeleted();
    unsigned int getType() { return Entity::PLAYER_TYPE; }
    bool drawInLayer(unsigned int layer);
	int getPodOffset(int i);
	float getPodOffsetFloat(int i);
	float getPodDepth(int i);
    void kill();
    void setState(unsigned int state);
    unsigned int getState();
	int getSpeed();
	void handleCollision(Entity *other, Level *level);
	
	
	static const int AIR_RESISTANCE_LOW = 2;
	static const int AIR_RESISTANCE_MEDIUM = 3;
	static const int AIR_RESISTANCE_HIGH = 5;
	static const int SHOT_BURST_LENGTH = 15;
	static const int SHOT_FRAME_DELAY = 3;
	static const int SHOT_POD_DELAY = 4;

    enum State
    {
        NORMAL,
        KILLED,
        DEAD,
        IMORTAL,
        NEW,
        IDLE
    };

private:
    void movementLogic(Level* level);

	int mFrameCounter;
	int mDX, mDY;
	int mTargetX, mTargetY;
	bool mShotPressed;
    bool mMegaBlastPressed;
	bool mShotReleased;
	int mShotBurstCounter;
	int mNumPods;
    unsigned int mState;

	Animation mPlayerAni;
	Animation mPodAni;
	SAMPLE *mShotSample;
	SAMPLE *mExplosionSample;

    bool mImortalButtonPressed;
};

#endif