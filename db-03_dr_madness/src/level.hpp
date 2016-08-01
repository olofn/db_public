#ifndef DBSH07_LEVEL_HPP
#define DBSH07_LEVEL_HPP

#include "entity.hpp"
#include "player.hpp"
#include "guichan.hpp"
#include "guichan/allegro.hpp"
#include "gui/dialog.hpp"
#include "gui/extendedallegroinput.hpp"
#include "pointsummary.hpp"

#include <list>

class Level
{
public:
    Level(const std::string& filename);
    ~Level();
    void draw(BITMAP* dest);
    void logic();
    void load(const std::string& filename);
    void addEntity(Entity* entity);
	void addShakeAmount(int amount);
    void spawnNewPlayer();

    bool isGameOver();
    bool isLevelComplete();
    bool isQuit();

	int getMouseX();
	int getMouseY();
	Player* getPlayer();
	bool isFirePressed();
    bool isBrakePressed();
    bool isBurnPressed();
    bool isMegaBlastPressed();

    int getScrollY() { return mGameScrollY; }

	int getLevelLength() { return mLevelLength; }

	void spawnDebris(int amount, int x, int y, int w, int h);
    void spawnExplosions(int amount, int x, int y, int w, int h);

	int getAirResistance() { return mAirResistance; }
	int setAirResistance(int a) { mAirResistance = a; }
	void addKilledEnemy(int amount) { mKilledEnemies += amount; }
	void addDestroyedBlocks(int amount) { mDestroyedBlocks += amount; }

	int getBackgroundScroll() { return mBackgroundScrollY; }

    static const int SPACE_MOTIF = 0;
    static const int SKY_MOTIF = 1;
    static const int WATER_MOTIF = 2;
    static const int CAVE_MOTIF = 3;
    static const int BONUS_MOTIF = 4;

    static const int BLOCK_SIZE = 16;
    static const int LEVEL_WIDTH = 240;
    static const int BLOCK_WIDTH = LEVEL_WIDTH / BLOCK_SIZE;

protected:
    enum State
    {
        DIALOG,
        GAME,
        GAMEOVER,
        LEVEL_COMPLETE,
		LEAVE_LEVEL
    };

	void updateScrolling();
	void drawMousePointer(BITMAP *dest);
    void checkCollision(std::list<Entity*>& list1, std::list<Entity*>& list2);
    void checkStaticCollision(std::list<Entity*>& list);
    void initGui();

    std::list<Entity*> mEntities;
    std::list<Entity*> mHibernatingEntities;
    std::list<Entity*> mEnemyEntities;
    std::list<Entity*> mEnemyBulletEntities;
    std::list<Entity*> mPlayerEntities;
    std::list<Entity*> mPlayerBulletEntities;
    std::list<Entity*> mPowerUpEntities;

    int mGameScrollY;
    int mBackgroundScrollY;
	unsigned int mKilledEnemies;
	unsigned int mDestroyedBlocks;

    Player* mPlayer;
    Entity* mBackground;
    int mMotif;
    gcn::Gui* mGui;
    gcn::ExtendedAllegroInput* mInput;
    gcn::AllegroGraphics* mGraphics;
    gcn::AllegroImageLoader* mImageLoader;
    gcn::ImageFont* mImageFont;
    gcn::Container* mTop;
    Dialog* mDialog;
    gcn::Label* mLivesLabel;
    gcn::Label* mMegaBlastsLabel;
    gcn::Label* mEnergyOrbsLabel;
    gcn::Label* mTimeLabel;
	gcn::Label* mPointLabel;
    gcn::Label* mTimeCaptionLabel;
	gcn::Label* mPointsCaptionLabel;
    gcn::Label* mGameOverLabel;
    gcn::Label* mLevelCompleteLabel;
    gcn::Label* mLevelNumberLabel;
    gcn::Label* mLevelNameLabel;

    unsigned int mState;
    std::list<std::string> mDialogText;
    int mFrameCounter;
    int mTimeCounter;

	float mScrollSpeed;
	float mGameScrollFloat;

	PointSummary* mPointSummary;

    std::vector<Entity*> mStaticEntities;

	int mLevelLength;
	bool mLogicDoneOnce;
	float mShakeAmount;
	int mAirResistance;

    std::string mLevelName;

    unsigned int mNumberOfEnemies;
    unsigned int mNumberOfBlocks;
    unsigned int mLevelParTime;

    bool mEscapePressed;
    bool mQuit;
};

#endif