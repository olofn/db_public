#ifndef DBSH07_POINTSUMMARY_HPP
#define DBSH07_POINTSUMMARY_HPP

#include "guichan.hpp"
#include <allegro.h>

class PointSummary
{
public:
    PointSummary(gcn::Container* mTop, 
                 unsigned int blocks, 
                 unsigned int maxBlocks, 
                 unsigned int enemies,
                 unsigned int maxEnemies, 
                 unsigned int orbs, 
                 unsigned int time,
                 unsigned int partime);
    ~PointSummary();
	void logic();
	bool isDone();

protected:
	void initGui(gcn::Container* mTop);

	unsigned int mOrbs;
	unsigned int mEnemies;
	unsigned int mMaxEnemies;
	unsigned int mBlocks;
    unsigned int mMaxBlocks;
	unsigned int mTime;
	unsigned int mState;

	unsigned int mOrbPoints;
	unsigned int mEnemyPoints;
	unsigned int mBlockPoints;
	unsigned int mTimePoints;
	unsigned int mTotalPoints;

	float mBlockPointsCounter;
	float mEnemyPointsCounter;
	float mOrbPointsCounter;
	float mTimePointsCounter;
	float mTotalPointsCounter;

	bool mDoneCounting;
	bool mCountingPoints;

	unsigned int mFrameCounter;

    unsigned int mParTime;

//point count gui
	gcn::Label* mBlocksDestroyedLabel;
	gcn::Label* mEnemiesKilledLabel;
	gcn::Label* mOrbsTakenLabel;
	gcn::Label* mTimePassedLabel;
	gcn::Label* mTotalLabel;

	gcn::Label* mBlockPointsLabel;
	gcn::Label* mEnemyKillPointsLabel;
	gcn::Label* mOrbsTakenPointsLabel;
	gcn::Label* mTimeBonusLabel;
	gcn::Label* mTotalPointsLabel;

	SAMPLE* mBeepSample;
	SAMPLE* mBuySample;

};

#endif