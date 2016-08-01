#include "room.hpp"
#include "tilemap.hpp"
#include "animation.hpp"
#include "exception.hpp"
#include "music.hpp"
#include "random.hpp"
#include "stringutil.hpp"
#include "util.hpp"
#include "game.hpp"

#include "gui/inventorydialog.hpp"
#include "gui/shopdialog.hpp"
#include "entities/itementity.hpp"
#include "items/bomb.hpp"
#include "entities/chest.hpp"
#include "entities/smoke.hpp"
#include "entities/friendlyvapor.hpp"
#include "resourcehandler.hpp"

#include <cmath>
#include <algorithm>

class EntityComparator
{
public:
  int operator()(Entity *a, Entity *b)
  {
    return (a->getY() + a->getHeight()) < (b->getY() + b->getHeight());
  }
};

Room::Room(TileMap* tileMap, Animation *tileSet)
{
	//memset(this, 0, sizeof(Room));
	zoomLevel = 0;

	mHearts = new Animation("graphics/hearts.bmp");
	mCoin = new Animation("graphics/coin.bmp");
	
	mPlayer = 0;
	mTop = 0;
	zoomActive = false;
	mLoadAtOverWorld = false;
	mMusicStarted = false;

	mTileMap = tileMap;
	//tileMap = RoomLoader::loadTileMap("rooms/testroom.txt");//RoomGenerator::generateTileMap(40, 40, RoomGenerator::ALGORITHM_BROWNIAN, Random::get());
	mTileSet = tileSet;//new Animation("graphics/tilesethouse.bmp", 9);

	mEntityWithLogic = NULL;
	mCutScenesRunning = false;
	mDialogRunning = false;
	mShopDialogRunning = false;
	mTextRunning = false;
	mFreeze = false;
	mGuiInitialised = false;
	mTotalFreeze = false;

	mGameOver = false;
	mGameOverCounter = 75;

	mZoomBuffer = create_bitmap(320, 240);
	mGameOverSample = ResourceHandler::getInstance()->getSample("sound/bigselect.wav");
}

void Room::setTotalFreeze(bool freeze)
{
	mTotalFreeze = freeze;
}

void Room::setTop(gcn::Container* top)
{
	mTop = top;
	initGui();
}

void Room::setCoinCaption(const std::string& caption)
{
	mCoinLabel->setCaption(caption);
	mCoinLabel->adjustSize();
}

Room::~Room()
{
	delete mHearts;
	delete mCoin;
	delete mInventoryDialog;
	delete mShopDialog;
	delete mTileMap;
	delete mTileSet;
	delete mDialog;
	delete mCoinLabel;

	destroy_bitmap(mZoomBuffer);

	for (int i = 0; i < (int)mEntities.size(); i++)
	{
		if (mEntities[i] != mPlayer)
		{
			delete mEntities[i];
		}
	}
}

void Room::addEntity(Entity* entity)
{
	mEntities.push_back(entity);
	mEntitiesByType[entity->getType()].push_back(entity);
	entity->setRoom(this);
}

void Room::spawnSmallSmokeAtEntity(Entity* entity)
{
	addEntity(new Smoke(entity->getCenterX() - 8, 
						entity->getCenterY() - 8));
}

void Room::spawnLargeSmokeAtEntity(Entity* entity)
{
	addEntity(new Smoke(entity->getCenterX() - 16, 
						entity->getCenterY() - 16,
						true));
}

void Room::spawnDeath(Entity* entity)
{
	// Spawn heart
	if (Random::get().getInt(0, 4) == 0)
	{
		addEntity(new ItemEntity(new Animation("graphics/heart.bmp"), entity->getX(), entity->getY(), true, 0, 1));
	}
	// Spawn coins
	else
	{
		int maxCoin = 0;
		int minCoin = 0;
		if(entity->getLevel() == 0)
		{
			minCoin = 0;
			maxCoin = 1;
		}
		else if(entity->getLevel() == 1)
		{
			minCoin = 0;
			maxCoin = 2;
		}
		else if(entity->getLevel() == 2)
		{
			minCoin = 1;
			maxCoin = 3;
		}
		else if(entity->getLevel() > 2)
		{
			minCoin = entity->getLevel()/2;
			maxCoin = entity->getLevel();
		}

		int coins = Random::get().getInt(minCoin, maxCoin);

		for(int i = 0; i < coins; i ++)
		{
			addEntity(new ItemEntity(new Animation("graphics/coin.bmp"), entity->getX(), entity->getY(), true, 1, 0));
		}
	}

	spawnSmallSmokeAtEntity(entity);
}

bool Room::isLoadAtOverworld()
{
	return mLoadAtOverWorld;
}

void Room::logic()
{
	if (!mMusicStarted)
	{
		if (mMusic != "")
		{
			playMusic(mMusic, 1.0f);
		}
		else
		{
			stopMusic();
		}

		mMusicStarted = true;
	}

	if (mPlayer->getHealth() <= 0)
	{
		if (mGameOverCounter == 75)
		{
			stopMusic();
			play_sample(mGameOverSample, 127, 127, 1000, 0);
		}

		mGameOverCounter--;
		if (mGameOverCounter <= 0)
			mLoadAtOverWorld = true;
		return;
	}

	setCoinCaption("*" + toString(mPlayer->getCoins()));

	// Update this here might brake cut scenes.
	mKeyState.setKeys(key[KEY_UP], 
              key[KEY_DOWN], 
              key[KEY_LEFT], 
              key[KEY_RIGHT],
              key[KEY_LCONTROL], 
              key[KEY_ALT], 
              key[KEY_SPACE],
              key[KEY_I]);

	if (!mInventoryDialog->isVisible() && mKeyState.isInventoryPressed())
	{
		mInventoryDialog->setVisible(true);
		mInventoryDialog->requestFocus();
	}
	else if (mInventoryDialog->isVisible() &&  mKeyState.isInventoryPressed())
	{
		mInventoryDialog->setVisible(false);
	}
	else if (mInventoryDialog->isVisible())
	{
		return;
	}

	if (mFreeze)
	{
		mFreezeFrames--;

		if (mFreezeFrames <= 0)
		{
			mFreeze = false;
		}
	}
	else if (!mTotalFreeze)
	{
		runEntityLogic();
	}

	if (mCutScenesRunning /*&& mCutScene != NONE*/ )
	{
		mKeyState.setDisabled(true);
		mPlayer->setCheckForCollisions(false);
		if (getLordVapor())
			getLordVapor()->setCheckForCollisions(false);
		runCutScenes();
		return;
	}
	else
	{
		mKeyState.setDisabled(false);
		mPlayer->setCheckForCollisions(true);
		if (getLordVapor())
			getLordVapor()->setCheckForCollisions(true);
	}

	if (mEntityWithLogic != NULL)
	{
		mEntityWithLogic->logic();
		return;
	}
}

void Room::freeze(int frames)
{
	mFreeze = true;
	mFreezeFrames = frames;
}

void Room::runEntityLogic()
{
	std::vector<Entity *> toUpdate(mEntities);

	for (int i = 0; i < (int)toUpdate.size(); i++)
	{
		if (!toUpdate[i]->isToBeDeleted())
		{
			toUpdate[i]->logic();
		}

		if (mFreeze || mTotalFreeze)
			break;
	}
	
	// Remove old entities
	std::vector<Entity *> toConsider(mEntities);
	mEntities.clear();
	mEntitiesByType.clear();
	for	(int i = 0; i < (int)toConsider.size(); i++)
	{
		if (!toConsider[i]->isToBeDeleted())
		{
			mEntities.push_back(toConsider[i]);
			mEntitiesByType[toConsider[i]->getType()].push_back(toConsider[i]);
		}
		else
		{
			delete toConsider[i];
		}
	}
}

void Room::draw(BITMAP *buffer)
{
	int scrollX = clamp(mPlayer->getCenterX() - 160, 
						0, 
						mTileMap->getWidth() * TileMap::TILE_SIZE - 320);
	int scrollY = clamp(mPlayer->getCenterY() - 120,
						-16,
						mTileMap->getHeight() * TileMap::TILE_SIZE - 240 + 16);

	if (mPlayer->getHealth() > 0)
	{
		drawGame(buffer, scrollX, scrollY);
	}
	else
	{
		drawGameOver(buffer, scrollX, scrollY);
	}

	rectfill(buffer, 0, 0, 320, 16, 0);
	line(buffer, 0, 16, 320, 16, makecol(255, 255, 255));
	rectfill(buffer, 0, 240 - 16, 320,  240, 0);
	line(buffer, 0, 240 - 16, 320, 240 - 16, makecol(255, 255, 255));
	
	mCoin->drawFrame(buffer, 0, 2, 2);

	for (int i = 0; i < mPlayer->getMaxHealth(); i++)
	{
		mHearts->drawFrame(buffer, 
						  i >= mPlayer->getHealth() ? 1 : 0, 
						  160+ i * mHearts->getFrameWidth() + 3, 3);
	}

}

void Room::drawGame(BITMAP *buffer, int scrollX, int scrollY)
{
	std::vector<Entity *> toDraw(mEntities);


	std::sort(toDraw.begin(), toDraw.end(), EntityComparator());
	int drawEntityIndex = 0;

	BITMAP *mapBuffer = zoomActive ? mZoomBuffer : buffer;

	// TODO: Don't draw the whole map
	for (int tileRow = 0; tileRow < mTileMap->getHeight(); tileRow++)
	{
		mTileMap->draw(mapBuffer, *mTileSet, tileRow, scrollX, scrollY);
	
		while (drawEntityIndex < (int)toDraw.size() && 
			(toDraw[drawEntityIndex]->getY() + toDraw[drawEntityIndex]->getHeight() - 1) / TileMap::TILE_SIZE <= tileRow)
		{
			if ((toDraw[drawEntityIndex]->getY() + toDraw[drawEntityIndex]->getHeight() - 1) / TileMap::TILE_SIZE == tileRow)
			{
				toDraw[drawEntityIndex]->draw(mapBuffer, scrollX, scrollY);
			}
			
			drawEntityIndex++;
		}
	}

	for (unsigned int i = 0; i < mEntities.size(); i++)
	{
		mEntities[i]->drawForeground(mapBuffer, scrollX, scrollY);
	}

	// Draw bounding boxes when B is held
#ifdef _DEBUG
	if (key[KEY_B])
	{
		for (int i = 0; i < (int)toDraw.size(); i++)
		{
			Entity *e = toDraw[i];
			rect(mapBuffer, e->getX() - scrollX, e->getY() - scrollY, e->getX() - scrollX + e->getWidth() - 1, e->getY() - scrollY + e->getHeight() - 1, (int)e);
		}
	}
#endif

	if (zoomActive)
	{
		//stretch_blit(mZoomBuffer, buffer, 0, 0, 320, 240, -zoomLevel, -zoomLevel, 320 + zoomLevel * 2, 240 + zoomLevel * 2);
		pivot_scaled_sprite(buffer, mZoomBuffer, 160, 120, 160, 120, itofix(zoomLevel * 256.0 / MAX_ZOOM), ftofix(std::pow(2.0, zoomLevel * 4.0 / MAX_ZOOM)));
	}

	if (mTextRunning)
	{
		rectfill(buffer, 
				 mTextLabel->getX() - 15,
				 mTextLabel->getY() - 4,
				 mTextLabel->getX() + mTextLabel->getWidth() + 14,
				 mTextLabel->getY() + mTextLabel->getHeight() + 2,
				 makecol(0, 0, 0));
	}
}

void Room::drawGameOver(BITMAP *buffer, int scrollX, int scrollY)
{
	if (mGameOverCounter == 75 
		|| mGameOverCounter == 70
		|| mGameOverCounter == 65)
	{
		rectfill(buffer, 0, 0, 320, 240, makecol(255, 255, 255));
	}

	mPlayer->draw(buffer, scrollX, scrollY);
}

void Room::aquireLogic(Entity* entity)
{
	if (mEntityWithLogic != NULL)
	{
		throw DB_EXCEPTION("Entity has already aquired logic!");
	}

	mEntityWithLogic = entity;
}

TileMap *Room::getTileMap() const
{
	return mTileMap;
}

void Room::releaseLogic(Entity* entity)
{
	if (mEntityWithLogic != entity)
	{
		throw DB_EXCEPTION("An entity without logic is trying to release logic!");
	}

	mEntityWithLogic = NULL;
}

void Room::startCutScenes()
{
	if (mCutScenes.size() == 0)
	{
		throw DB_EXCEPTION("No cutscenes to start!");
	}

	mCutScenesRunning = true;
}

void Room::addDialogCutScene(std::string text, bool atTop)
{
	CutScene scene;
    scene.type = DIALOG;
    scene.text = text;
	scene.dialogAtTop = atTop;
    mCutScenes.push(scene);
}

void Room::addMusicCutScene(std::string music, int volym, bool loop)
{
	CutScene scene;
    scene.type = MUSIC;
    scene.text = music;
	scene.volym = volym;
	scene.loop = loop;
    mCutScenes.push(scene);
}

void Room::addStopMusicCutScene()
{
	CutScene scene;
    scene.type = STOP_MUSIC;
    mCutScenes.push(scene);
}

void Room::addWaitCutScene(int frames, bool totalFreeze)
{
	CutScene scene;
    scene.type = WAIT;
    scene.frames = frames;
	scene.totalFreeze = totalFreeze;
    mCutScenes.push(scene);
}

void Room::addTextCutScene(const std::string& text, int frames)
{
	CutScene scene;
    scene.type = TEXT;
	scene.text = toUpperCase(text);
    scene.frames = frames;
    mCutScenes.push(scene);
}

void Room::addActorStateCutScene(Actor* actor, const std::string& state)
{
	CutScene scene;
	scene.type = ACTOR_STATE;
	scene.text = state;
	scene.actor = actor;
	mCutScenes.push(scene);
}

void Room::addWaitForActorPostitionCutScene(Actor* actor, int x, int y, int width)
{
	CutScene scene;
	scene.type = WAIT_FOR_ACTOR_POSITION;
	scene.x = x;
	scene.y = y;
	scene.width = width;
	scene.actor = actor;
	mCutScenes.push(scene);
}

void Room::addChangeRoomCutScene(const std::string& dungeon, int level, bool zoom, int playerX, int playerY)
{
	CutScene scene;
	scene.type = CHANGE_ROOM;
	scene.text = dungeon;
	scene.level = level;
	scene.zoomIn = zoom;
	scene.x = playerX;
	scene.y = playerY;
	mCutScenes.push(scene);
}

void Room::addZoomCutScene(bool zoomIn)
{
	CutScene scene;
	scene.type = ZOOM;
	scene.zoomIn = zoomIn;
	mCutScenes.push(scene);	
}

void Room::addGameOverCutScene()
{
	CutScene scene;
	scene.type = GAME_OVER;
	mCutScenes.push(scene);	
}

void Room::addShopDialogCutScene()
{
	CutScene scene;
	scene.type = SHOP_DIALOG;
	mCutScenes.push(scene);	
}

void Room::addAddEntityCutScene(Entity *e)
{
	CutScene scene;
	scene.type = ADD_ENTITY;
	scene.entity = e;
	mCutScenes.push(scene);	
}

void Room::runCutScenes()
{
	if (mCutScenes.empty())
	{
		mCutScenesRunning = false;
		return;
	}

	CutScene &scene = mCutScenes.front();

    switch(scene.type)
    {
		case WAIT:
			runWaitCutScene(scene);
			return;
		case DIALOG:            
			runDialogCutScene(scene);
            return;
		case MUSIC:
			runMusicCutScene(scene);
			return;
		case ACTOR_STATE:
			runActorStateCutScene(scene);
			return;
		case WAIT_FOR_ACTOR_POSITION:
			runWaitForActorPositionCutScene(scene);
			return;
		case TEXT:
			runTextCutScene(scene);
			return;
		case STOP_MUSIC:
			runStopMusicCutScene(scene);
			return;
		case CHANGE_ROOM:
			runChangeRoomCutScene(scene);
			return;
		case ZOOM:
			runZoomCutScene(scene);
			return;
		case SHOP_DIALOG:
			runShopDialogCutScene(scene);
			return;
		case ADD_ENTITY:
			runAddEntityCutScene(scene);
			return;
		case GAME_OVER:
			runGameOverCutScene(scene);
			return;
		default:
			throw DB_EXCEPTION("Unknown cut scene type!");
	}
}

void Room::runMusicCutScene(CutScene& scene)
{
	playMusic(scene.text, scene.volym);
	popCutScene();
}

void Room::runStopMusicCutScene(CutScene& scene)
{
	stopMusic();
	popCutScene();
}

void Room::runActorStateCutScene(CutScene& scene)
{
	scene.actor->setState(scene.text);
	popCutScene();
}

void Room::runWaitForActorPositionCutScene(CutScene& scene)
{
	int ax = scene.actor->getX();
	int ay = scene.actor->getY() + scene.actor->getHeight() - 1;

	//std::cout << "X: " << ax << "/" << scene.x << " Y:" << ay << "/" << scene.y << std::endl;

	if (abs(ax - scene.x) <= scene.width &&
        abs(ay - scene.y) <= scene.width)
	{
		popCutScene();
	}
/*
	if (scene.actor->getX()  < (scene.x - scene.width / 2)
		&& (scene.actor->getX() + scene.actor->getWidth() - 1) > (scene.x + scene.width / 2)
		&& scene.actor->getBottomY() >= (scene.y - scene.width / 2)
		&& scene.actor->getBottomY() <= (scene.y + scene.width / 2))
	{
		popCutScene();
	}*/
}

void Room::runWaitCutScene(CutScene& scene)
{
	if (scene.totalFreeze)
		setTotalFreeze(true);

	scene.frames--;
                
    if (scene.frames <= 0)
    {
		if (scene.totalFreeze)
			setTotalFreeze(false);
        popCutScene();
    }
}

void Room::runGameOverCutScene(CutScene& scene)
{
	mGameOver = true;
	popCutScene();
}

void Room::runTextCutScene(CutScene& scene)
{
	if (!mTextRunning)
	{
		mTextLabel->setCaption(scene.text);
		mTextLabel->adjustSize();
		mTextLabel->setPosition(160 - mTextLabel->getWidth() / 2, 
								100 - mTextLabel->getHeight() / 2);
		mTextLabel->setVisible(true);
		mTextRunning = true;
	}

	scene.frames--;
                
    if (scene.frames <= 0)
    {
		mTextLabel->setVisible(false);
		mTextRunning = false;
        popCutScene();
    }
}

void Room::runDialogCutScene(CutScene& scene)
{
	if (!mDialogRunning)
	{
		mDialog->setText(scene.text);
		if (scene.dialogAtTop)
		{
			mDialog->setDimension(gcn::Rectangle(0, 16, 320, 75));
		}
		else
		{
			mDialog->setDimension(gcn::Rectangle(0, 240 - 75, 320, 75));
		}
		mDialog->setVisible(true);
		mDialog->requestFocus();
		mDialogRunning = true;
		setTotalFreeze(true);
	}
   
	if (mDialog->isDone())
	{
		mDialog->setVisible(false);
		mDialogRunning = false;
		setTotalFreeze(false);
		popCutScene();
	}
}

void Room::runShopDialogCutScene(CutScene& scene)
{
	if (!mShopDialogRunning)
	{
		mShopDialog->setVisible(true);
		mShopDialog->requestFocus();
		mShopDialogRunning = true;
		setTotalFreeze(true);
	}
   
	if (mShopDialog->isDone())
	{
		mShopDialog->setVisible(false);
		mShopDialogRunning = false;
		setTotalFreeze(false);
		popCutScene();
	}
}

void Room::runChangeRoomCutScene(CutScene& cutScene)
{
	mGame->changeRoom(cutScene.text, cutScene.level, cutScene.zoomIn, cutScene.x, cutScene.y);
}

void Room::runZoomCutScene(CutScene& cutScene)
{
	if (!zoomActive)
	{
		freeze(MAX_ZOOM);

		if (cutScene.zoomIn)
			zoomLevel = 0;
		else
			zoomLevel = MAX_ZOOM;

		zoomActive = true;
	}

	if (cutScene.zoomIn)
	{
		zoomLevel++;
		if (zoomLevel >= MAX_ZOOM)
			zoomActive = false;
	}
	else
	{
		zoomLevel--;
		if (zoomLevel <= 0)
			zoomActive = false;
	}

	if (!zoomActive)
	{
		popCutScene();
	}
}

void Room::runAddEntityCutScene(CutScene& cutScene)
{
	addEntity(cutScene.entity);
	popCutScene();
}

void Room::popCutScene()
{
	mCutScenes.pop();
	runCutScenes();
}

void Room::setGameOver(bool gameOver)
{
	mGameOver = true;
}

std::vector<Entity*> Room::collidesWith(Entity* entity, Entity::Type type, int padding)
{
	std::vector<Entity*> result;
	for (unsigned int i = 0; i < mEntitiesByType[type].size(); i++)
	{
		Entity* other = mEntitiesByType[type][i];

		if (entity->collidesWith(other, padding))
		{
			result.push_back(other);
		}
	}

	return result;
}

KeyState* Room::getKeyState()
{
	return &mKeyState;
}

void Room::setPlayer(Player *player)
{
	mPlayer = player;
	addEntity(player);

	initGui();
}

Door* Room::findDoor(const std::string &dungeonName, int dungeonLevel)
{
	Door *candidate = 0;

	for (int i = 0; i < (int)mEntities.size(); i++)
	{
		Entity *e = mEntities[i];
		Door *d = dynamic_cast<Door *>(e);
		if (d)
		{
			if (d->getTargetDungeon() == dungeonName)
			{
				candidate = d;
				
				if (d->getTargetLevel() == dungeonLevel)
				{
					return d;
				}
			}
		}
	}

	return candidate;
}

Door* Room::findUnboundDoor(bool down)
{
	for (int i = 0; i < (int)mEntities.size(); i++)
	{
		Entity *e = mEntities[i];
		Door *d = dynamic_cast<Door *>(e);
		if (d)
		{
			if (d->getTargetLevel() < 0 && d->isDown() == down)
			{
				return d;
			}
		}
	}

	return 0;
}

void Room::initGui()
{
	if (mGuiInitialised)
		return;

	if (mPlayer == 0 || mTop == 0)
		return;

	mGuiInitialised = true;

	mDialog = new Dialog();
	mDialog->setVisible(false);
	mCoinLabel = new gcn::Label("*0");
	mCoinLabel->adjustSize();
	mTextLabel = new gcn::Label("TEXT!");
	mTextLabel->adjustSize();
	mTextLabel->setVisible(false);
	mInventoryDialog = new InventoryDialog(mPlayer->getInventory());
	mInventoryDialog->setPosition(160 - mInventoryDialog->getWidth() / 2, 
								  120 - mInventoryDialog->getHeight() / 2);
	mInventoryDialog->setVisible(false);

	mShopDialog = new ShopDialog(mPlayer);
	mShopDialog->setPosition(160 - mShopDialog->getWidth() / 2, 
						     120 - mShopDialog->getHeight() / 2);
	mShopDialog->setVisible(false);
	mTop->add(mDialog);
	mTop->add(mCoinLabel, 10, 3);
	mTop->add(mTextLabel);
	mTop->add(mInventoryDialog);
	mTop->add(mShopDialog);
}

Actor* Room::getLordVapor()
{
	for(unsigned int i = 0; i < mEntities.size(); i++)
	{
		Actor *v = dynamic_cast<FriendlyVapor *>(mEntities[i]);
		if (v != 0)
			return v;
	}

	return 0;
}
