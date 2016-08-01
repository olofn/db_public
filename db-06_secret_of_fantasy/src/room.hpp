#ifndef DB_ROOM
#define DB_ROOM

#include <queue>
#include <list>
#include <vector>
#include <allegro.h>
#include "guichan.hpp"
#include "keystate.hpp"
#include "gui/dialog.hpp"

#include "entity.hpp"
#include "entities/player.hpp"
#include "entities/door.hpp"

class Game;
class Animation;
class TileMap;
class InventoryDialog;
class ShopDialog;

class Room
{
public:
	Room(TileMap* tileMap, Animation *tileSet);
	~Room();
	void logic();
	void draw(BITMAP *buffer);
	void setTop(gcn::Container* top);
	TileMap *getTileMap() const;
	void addEntity(Entity* entity);

	void aquireLogic(Entity* entity);
	void releaseLogic(Entity* entity);
	void spawnDeath(Entity* entity);

	void freeze(int frames);
	void setTotalFreeze(bool totalFreeze);

	std::vector<Entity*> collidesWith(Entity* entity, Entity::Type type, int padding = 0);
	KeyState* getKeyState();

	void startCutScenes();
	void addDialogCutScene(std::string text, bool atTop = true);
	void addMusicCutScene(std::string music, int volym, bool loop = true);
	void addStopMusicCutScene();
	void addWaitCutScene(int frames, bool totalFreeze = false);
	void addActorStateCutScene(Actor* actor, const std::string& state);
	void addWaitForActorPostitionCutScene(Actor* actor, int x, int y, int width = 1);
	void addTextCutScene(const std::string& text, int frames);
	void addChangeRoomCutScene(const std::string& dungeon, int level, bool zoom, int playerX = -1, int playerY = -1);
	void addZoomCutScene(bool zoomIn);
	void addShopDialogCutScene();
	void addAddEntityCutScene(Entity *e);
	void addGameOverCutScene();

	void setCoinCaption(const std::string& caption);

	Player* getPlayer() { return mPlayer; }
	Actor* getLordVapor();
	Game* getGame() { return mGame; }
	void setPlayer(Player *player);
	void setGame(Game *game) { mGame = game; }

	Door* findDoor(const std::string &dungeonName, int dungeonLevel);
	Door* findUnboundDoor(bool down);

	void setDungeonName(const std::string &dungeonName) { mDungeonName = dungeonName; }
	const std::string &getDungeonName() { return mDungeonName; }
	void setDungeonLevel(int dungeonLevel) { mDungeonLevel = dungeonLevel; }
	int getDungeonLevel() { return mDungeonLevel; }
	void spawnSmallSmokeAtEntity(Entity* entity);
	void spawnLargeSmokeAtEntity(Entity* entity);
	bool isGameOver() { return mGameOver; }
	void setGameOver(bool gameOver);

	void setMusic(std::string music) { mMusic = music; mMusicStarted = false; }
	bool isLoadAtOverworld();

private:
	void drawGame(BITMAP *buffer, int scrollX, int scrollY);
	void drawGameOver(BITMAP *buffer, int scrollX, int scrollY);
	void runEntityLogic();
	void initGui();
	bool mGuiInitialised;

	Animation *mTileSet;
	TileMap *mTileMap;
	gcn::Container* mTop;
	Dialog* mDialog;
	Entity* mEntityWithLogic;
	KeyState mKeyState;
	bool mFreeze;
	int mFreezeFrames;
	bool mTotalFreeze;

	enum CutSceneType
	{
		NONE,
		DIALOG,
		WAIT,
		MUSIC,
		ACTOR_STATE,
		WAIT_FOR_ACTOR_POSITION,
		TEXT,
		STOP_MUSIC,
		CHANGE_ROOM,
		ZOOM,
		SHOP_DIALOG,
		ADD_ENTITY,
		GAME_OVER
	};

	class CutScene
	{
	public:
		CutSceneType type;
		std::string text;
		int frames;
		int level;
		float volym;
		bool loop;
		int x;
		int y;
		int width;
		bool dialogAtTop;
		bool zoomIn;
		Actor* actor;
		Entity* entity;
		bool totalFreeze;
	};

	std::queue<CutScene> mCutScenes;
	CutSceneType mCutScene;
	
	void runCutScenes();
	void popCutScene();
	bool mCutScenesRunning;

	void runWaitForActorPositionCutScene(CutScene& cutScene);

	void runWaitCutScene(CutScene& cutScene);

	void runTextCutScene(CutScene& cutScene);
	bool mTextRunning;
	int mTextFrames;

	void runDialogCutScene(CutScene& cutScene);
	bool mDialogRunning;

	void runShopDialogCutScene(CutScene& cutScene);
	bool mShopDialogRunning;

	void runGameOverCutScene(CutScene& cutScene);

	void runMusicCutScene(CutScene& cutScene);
	void runStopMusicCutScene(CutScene& cutScene);

	void runActorStateCutScene(CutScene& cutScene);

	void runChangeRoomCutScene(CutScene& cutScene);

	void runZoomCutScene(CutScene& cutScene);

	void runAddEntityCutScene(CutScene& cutScene);

	BITMAP *mZoomBuffer;

	std::vector<Entity *> mEntities;
	std::map<Entity::Type, std::vector<Entity *> > mEntitiesByType;

	Game* mGame;
	Player* mPlayer;
	Animation *mHearts;
	Animation *mCoin;
	gcn::Label* mCoinLabel;
	gcn::Label* mTextLabel;

	static const int MAX_ZOOM = 32;
	bool zoomActive;
	InventoryDialog* mInventoryDialog;
	ShopDialog* mShopDialog;

	int zoomLevel;

	int mDungeonLevel;
	std::string mDungeonName;

	bool mGameOver;
	int mGameOverCounter;
	bool mLoadAtOverWorld;

	std::string mMusic;
	bool mMusicStarted;

	SAMPLE* mGameOverSample;
};
#endif
