#ifndef DB_LEVEL_HPP
#define DB_LEVEL_HPP

#include "animation.hpp"
#include "entity.hpp"
#include "tilemap.hpp"
#include "entities/player.hpp"
#include "entities/camera.hpp"
#include "guichan.hpp"
#include "gui/dialog.hpp"

#include <string>
#include <allegro.h>
#include <list>

class Level
{
public:
    Level(gcn::Container* top, const std::string& filename, int totalStarsCollected);
    ~Level();
    void draw(BITMAP* dest);
    void logic();
    TileMap* getTileMap();
    Player* getPlayer();
    Camera* getCamera();
    void initGui();
    void distributeMessage(const std::string& message, Entity* distributor);
    void addEntity(Entity* entity);
    void spawnExplosions(int amount, int x, int y, int w, int h);
    bool isGameOver();
    bool isGoalReached();
    void setGoalReached(bool reached);
    void setCollectedStars(int collectedStars);
    int getCollectedStars();
protected:
    void logicDialog();
    void logicGame();
    void logicEntities();
    void logicTime();
    void logicShakes();
    void logicStars();

    enum State
    {
        GAME,
        DIALOG
    };
    State mState;

    void load(const std::string& filename);
    std::string mLevelName;
    std::string mMotif;
    std::list<Entity*> mEntities;
    TileMap* mTileMap;
    Player* mPlayer;
    Camera* mCamera;
    float mShakeAmount;
    std::list<std::string> mDialogText;
    bool mEscapePressed;
    int mTotalStarsCollected;

    Dialog* mDialog;
	gcn::Container* mTop;
    gcn::Label* mTimeLabel;
    gcn::Label* mStarsLabel;

    int mFrameCounter;
    int mLevelTime;
    bool mGoalReached;
    int mCollectedStars;
    Animation mCountdownAnimation;
    Animation mReadySteadyGoAnimation;

    SAMPLE* mBigBombSample;
};

#endif
