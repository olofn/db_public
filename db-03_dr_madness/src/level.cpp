#include "level.hpp"

#include "exception.hpp"
#include "fileutil.hpp"
#include "stringutil.hpp"
#include "block.hpp"
#include "mine.hpp"
#include "turret.hpp"
#include "floater.hpp"
#include "waterbackground.hpp"
#include "starsbackground.hpp"
#include "resourcehandler.hpp"
#include "gamestate.hpp"
#include "planet.hpp"
#include "energyorb.hpp"
#include "music.hpp"
#include "util.hpp"
#include "debris.hpp"
#include "electro.hpp"
#include "bonusbackground.hpp"
#include "skybackground.hpp"
#include "cavebackground.hpp"
#include "vulcano.hpp"



#include <iostream>

Level::Level(const std::string& filename)
: mGameScrollY(0),
  mBackgroundScrollY(0),
  mScrollSpeed(0.0f),
  mGameScrollFloat(0.0f),
  mFrameCounter(0),
  mLogicDoneOnce(false),
  mLevelLength(0),
  mShakeAmount(0),
  mTimeCounter(0),
  mAirResistance(1),
  mKilledEnemies(0),
  mDestroyedBlocks(0),
  mNumberOfEnemies(0),
  mNumberOfBlocks(0),
  mEscapePressed(false),
  mQuit(false)
{
    load(filename);
	mPlayer = new Player();
	addEntity(mPlayer);

    initGui();
}

Level::~Level()
{
    delete mGui;
    delete mImageLoader;
    delete mGraphics;
    delete mInput;
    delete mTop;
    delete mDialog;
    delete mLivesLabel;
    delete mEnergyOrbsLabel;
    delete mGameOverLabel;
    delete mTimeLabel;
	delete mPointLabel;
    delete mLevelCompleteLabel;
    delete mLevelNameLabel;
    delete mLevelNumberLabel;
    delete mMegaBlastsLabel;

    std::list<Entity *>::iterator it;

    for (it = mEntities.begin(); it != mEntities.end(); it++)
    {
        delete (*it);
    }
}

bool Level::isGameOver()
{
    return mState == GAMEOVER && mFrameCounter > 200;
}

bool Level::isLevelComplete()
{
    return mState == LEAVE_LEVEL;
}

bool Level::isQuit()
{
    return mQuit;
}

void Level::initGui()
{
    mGui = new gcn::Gui();
    mGraphics = new gcn::AllegroGraphics();
    mInput = new gcn::ExtendedAllegroInput();
    mImageLoader = new gcn::AllegroImageLoader();
    gcn::Image::setImageLoader(mImageLoader);
    mGui->setInput(mInput);
    mGui->setGraphics(mGraphics);
    mTop = new gcn::Container();
    mTop->setSize(320, 240);
    mTop->setOpaque(false);
    mGui->setTop(mTop);
    mDialog = new Dialog();
    mDialog->setSize(240, 75);
    mDialog->setVisible(false);
    mTop->add(mDialog, 60, 240 - 75);

    if (GameState::getInstance()->getLives() < 10)
    {
        mLivesLabel = new gcn::Label("0"+toString(GameState::getInstance()->getLives())+"x~");
    }
    else
    {
        mLivesLabel = new gcn::Label(toString(GameState::getInstance()->getLives())+"x~");
    }
    mTop->add(mLivesLabel, 5, 3);

    if (GameState::getInstance()->getEnergyOrbs() < 100)
    {
        mEnergyOrbsLabel = new gcn::Label("00"+toString(GameState::getInstance()->getEnergyOrbs())+"x}");
    }
    else if (GameState::getInstance()->getEnergyOrbs() < 10)
    {
        mEnergyOrbsLabel = new gcn::Label("0"+toString(GameState::getInstance()->getEnergyOrbs())+"x}");
    }
    else
    {
        mEnergyOrbsLabel = new gcn::Label(toString(GameState::getInstance()->getEnergyOrbs())+"x}");
    }

    mTop->add(mEnergyOrbsLabel, 5, mLivesLabel->getHeight() + 3);

    if (GameState::getInstance()->getMegaBlasts() < 10)
    {
        mMegaBlastsLabel = new gcn::Label("0"+toString(GameState::getInstance()->getMegaBlasts())+"x[");
    }
    else
    {
        mMegaBlastsLabel = new gcn::Label(toString(GameState::getInstance()->getMegaBlasts())+"x[");
    }

    mTop->add(mMegaBlastsLabel, 5, mLivesLabel->getHeight() * 2 + 3);

    mTimeLabel = new gcn::Label("000.00");
    mTop->add(mTimeLabel, 5, mLivesLabel->getHeight()*5 + 3);
	
	mPointLabel = new gcn::Label("0");
	mTop->add(mPointLabel, 5, mLivesLabel->getHeight()*10);

    mTimeCaptionLabel = new gcn::Label("TIME");
    mTop->add(mTimeCaptionLabel, 5, mLivesLabel->getHeight() * 6 + 3);

	mPointsCaptionLabel = new gcn::Label("POINTS");
    mTop->add(mPointsCaptionLabel, 5, mLivesLabel->getHeight() * 9);

    mGameOverLabel = new gcn::Label("GAME OVER");
    mGameOverLabel->setVisible(false);
    mTop->add(mGameOverLabel, 
              160 - mGameOverLabel->getWidth() / 2 + 20,
              120 - mGameOverLabel->getHeight() / 2);

    mLevelCompleteLabel = new gcn::Label(GameState::getInstance()->getLevelDesignation(GameState::getInstance()->getLevel()) + " COMPLETE!!");
    mLevelCompleteLabel->setVisible(false);
    mTop->add(mLevelCompleteLabel,
              160 - mLevelCompleteLabel->getWidth() / 2 + 20,
              50 - mLevelCompleteLabel->getHeight() / 2);

    mLevelNameLabel = new gcn::Label();
    mLevelNameLabel->setVisible(false);
    mTop->add(mLevelNameLabel);

    mLevelNumberLabel = new gcn::Label();
    mLevelNumberLabel->setVisible(false);
    mTop->add(mLevelNumberLabel);

}
// Predicate function used to remove entities.
static bool isNull(Entity *e) 
{
	return e == NULL;
}

void Level::draw(BITMAP* dest)
{
	if (!mLogicDoneOnce)
	{
		logic();
	}

	int xOffs = 0, yOffs = 0;
	int oldGameScrollY = mGameScrollY;

	if(mShakeAmount > 100)
	{
		int shakeAmount = ((mShakeAmount - 100)/25.0f);
		if(shakeAmount > 60) shakeAmount = 60;

		xOffs = shakeAmount*(frand()-0.5f);
		yOffs = shakeAmount*(frand()-0.5f);
		mGameScrollY += yOffs;
	}

	BITMAP* subdest = create_sub_bitmap(dest, 60+xOffs, 0, 240, 240); 	

    mBackground->draw(subdest, mBackgroundScrollY + mGameScrollY, Entity::BACKGROUND_LAYER);

    std::list<Entity *>::iterator it;

	for (int layer = 0; layer < Entity::NUM_LAYERS; layer++)
	{
		for (it = mEntities.begin(); it != mEntities.end(); it++)
		{
			if ((*it)->drawInLayer(layer))
			{
				(*it)->draw(subdest, mGameScrollY, layer);
			}
		}
	}

	if (mBackground->drawInLayer(Entity::FOREGROUND_LAYER))
	{
		mBackground->draw(subdest, mBackgroundScrollY + mGameScrollY, Entity::FOREGROUND_LAYER);
	}

	drawMousePointer(subdest);
    vline(subdest, 0, 0, 239, makecol(100, 100, 100));
    vline(subdest, 239, 0, 239, makecol(100, 100, 100));

    destroy_bitmap(subdest);

    mGraphics->setTarget(dest);
    mGui->draw();
	mGameScrollY = oldGameScrollY;
}

void Level::drawMousePointer(BITMAP *dest)
{
	int mx = getMouseX();
	int my = getMouseY()- mGameScrollY;
	circle(dest, mx, my, 6, makecol(130, 130, 130));
	arc(dest, mx, my, itofix(mGameScrollY * 3), itofix(mGameScrollY * 3 + 120), 6, makecol(255, 255, 255));
	arc(dest, mx, my, itofix(mGameScrollY * 3), itofix(mGameScrollY * 3 + 120), 8, makecol(200, 200, 200));

	hline(dest, mx - 4, my, mx - 2, makecol(255,255,255));
	hline(dest, mx - 4, my-1, mx - 2, makecol(0,0,0));
	hline(dest, mx - 4, my+1, mx - 2, makecol(0,0,0));

	hline(dest, mx + 2, my, mx + 4, makecol(255,255,255));
	hline(dest, mx + 2, my-1, mx + 4, makecol(0,0,0));
	hline(dest, mx + 2, my+1, mx + 4, makecol(0,0,0));

	vline(dest, mx, my - 4, my - 2, makecol(255,255,255));
	vline(dest, mx-1, my - 4, my - 2, makecol(0,0,0));
	vline(dest, mx+1, my - 4, my - 2, makecol(0,0,0));

	vline(dest, mx, my + 2, my + 4, makecol(255,255,255));
	vline(dest, mx-1, my + 2, my + 4, makecol(0,0,0));
	vline(dest, mx+1, my + 2, my + 4, makecol(0,0,0));
}

void Level::logic()
{
	mLogicDoneOnce = true;
	if(mShakeAmount > 0) mShakeAmount /= 1.045;


    if (mState == DIALOG)
    {
        mPlayer->setState(Player::IDLE);
        mBackground->logic(this);
        mPlayer->logic(this);
        mGui->logic();

        if ((key[KEY_ESC] != 0) && !mEscapePressed)
        {
            mDialog->setVisible(false);
            mState = GAME;
            mPlayer->setState(Player::NEW);
            mFrameCounter = 0;
        }
        else if (!mDialog->isVisible() && mDialogText.empty())
        {
            mState = GAME;
            mPlayer->setState(Player::NEW);
            mFrameCounter = 0;
        }
        else if (!mDialog->isVisible())
        {
            mDialog->setText(mDialogText.front());
            mDialog->setVisible(true);
            mDialogText.pop_front();
        } 

        mBackgroundScrollY++;
    }
    else if (mState == GAMEOVER)
    {
		mBackground->logic(this);
        std::list<Entity *>::iterator it;

        for (it = mEntities.begin(); it != mEntities.end(); it++)
        {
	        (*it)->logic(this);
        }
    }
	else if (mState == LEVEL_COMPLETE)
	{
        mBackground->logic(this);
        std::list<Entity *>::iterator it;

        for (it = mEntities.begin(); it != mEntities.end(); it++)
        {
	        (*it)->logic(this);
        }

		mPointSummary->logic();
		if(mPointSummary->isDone()) {
			delete(mPointSummary);
			mState = LEAVE_LEVEL;
		}
	}
    else if (mState == GAME)
    {
        if ((key[KEY_ESC] != 0) && !mEscapePressed)
        {
            mQuit = true;
        }

        if (mFrameCounter < 200)
        {
            mLevelNumberLabel->setCaption(GameState::getInstance()->getLevelDesignation(GameState::getInstance()->getLevel()) + ":");
            mLevelNumberLabel->adjustSize();
            mLevelNumberLabel->setPosition(160 - mLevelNumberLabel->getWidth() / 2 + 20,
                120 - mLevelNumberLabel->getHeight());
            mLevelNumberLabel->setVisible(true);
            mLevelNameLabel->setCaption(mLevelName);
            mLevelNameLabel->adjustSize();
            mLevelNameLabel->setPosition(160 - mLevelNameLabel->getWidth() / 2 + 20,
                                         120);
            mLevelNameLabel->setVisible(true);
        }
        else if (mFrameCounter >= 200)
        {
            mLevelNumberLabel->setVisible(false);
            mLevelNameLabel->setVisible(false);
        }

        if (mLevelLength - 240 <= mGameScrollY)
        {
			mState = LEVEL_COMPLETE;
            mFrameCounter = 0;
            mLevelCompleteLabel->setVisible(true);			
			mPointSummary = new PointSummary(mTop, 
                                             mDestroyedBlocks, 
                                             mNumberOfBlocks, 
                                             mKilledEnemies, 
                                             mNumberOfEnemies, 
                                             GameState::getInstance()->getEnergyOrbs(), 
                                             mTimeCounter,
                                             mLevelParTime);
            return;
        }

        checkCollision(mEnemyEntities, mPlayerBulletEntities);
        checkCollision(mPlayerEntities, mEnemyBulletEntities);
        checkCollision(mEnemyEntities, mPlayerEntities);
        checkCollision(mPowerUpEntities, mPlayerEntities);
        checkCollision(mEnemyEntities, mEnemyEntities);
        checkStaticCollision(mPlayerEntities);
        checkStaticCollision(mPlayerBulletEntities);
		checkStaticCollision(mEnemyBulletEntities);
     
		mBackground->logic(this);
        std::list<Entity *>::iterator it;

        while (!mHibernatingEntities.empty() 
                && mHibernatingEntities.front()->getY() <= mGameScrollY + 240 + 20)
        {
            addEntity(mHibernatingEntities.front());
            mHibernatingEntities.pop_front();
        }

        for (it = mEntities.begin(); it != mEntities.end(); it++)
        {
	        (*it)->logic(this);
        }

        for (it = mEntities.begin(); it != mEntities.end(); it++)
        {
	        if ((*it)->isToBeDeleted()) 
            {
                if ((*it)->getType() == Entity::BLOCK_TYPE)
                {
                    mStaticEntities[(*it)->getX() / BLOCK_SIZE + (*it)->getY() / BLOCK_SIZE * BLOCK_WIDTH] = NULL;
                }

                mPlayerEntities.remove((*it));
                mPlayerBulletEntities.remove((*it));
                mEnemyEntities.remove((*it));
                mEnemyBulletEntities.remove((*it));
                mPowerUpEntities.remove((*it));

		        delete (*it);

		        *it = NULL;
	        }
        }

        mEntities.remove_if(isNull);

	    updateScrolling();

        if (GameState::getInstance()->getLives() > 9)
        {
            mLivesLabel->setCaption(toString(GameState::getInstance()->getLives()) + "x~");
        }
        else
        {
            mLivesLabel->setCaption("0" + toString(GameState::getInstance()->getLives()) + "x~");
        }
        
        mLivesLabel->adjustSize();

        if (GameState::getInstance()->getEnergyOrbs() > 9)
        {
            mEnergyOrbsLabel->setCaption(toString(GameState::getInstance()->getEnergyOrbs()) + "x}");
        }
        else
        {
            mEnergyOrbsLabel->setCaption("0" + toString(GameState::getInstance()->getEnergyOrbs()) + "x}");
        }
        
        mMegaBlastsLabel->adjustSize();

        if (GameState::getInstance()->getMegaBlasts() > 9)
        {
            mMegaBlastsLabel->setCaption(toString(GameState::getInstance()->getMegaBlasts()) + "x[");
        }
        else
        {
            mMegaBlastsLabel->setCaption("0" + toString(GameState::getInstance()->getMegaBlasts()) + "x[");
        }
        
        mMegaBlastsLabel->adjustSize();

        mGui->logic();

        mTimeCounter++;
	}

    std::string time = "";
    int hundredsOfSecond = (mTimeCounter * 2) % 100;
    int seconds = mTimeCounter / 50;
    
	if (seconds < 10)
    {
        time += "00";
    }
    else if (seconds < 100)
    {
        time += "0";
    }
   

    time += toString(seconds) + ".";

    if (hundredsOfSecond < 10)
    {
        time += "0";
    }

    time += toString(hundredsOfSecond);
    mTimeLabel->setCaption(time);
    mTimeLabel->adjustSize();

	mPointLabel->setCaption(toString(GameState::getInstance()->getPoints()));
    mPointLabel->adjustSize();
    mFrameCounter++;

    mEscapePressed = key[KEY_ESC] != 0;
}

void Level::spawnNewPlayer()
{
    if (GameState::getInstance()->getLives() >= 1)
    {
        mPlayer->reset();
        mPlayer->setY(mGameScrollY);

        GameState::getInstance()->setLives(GameState::getInstance()->getLives() - 1);
    }
    else
    {
        mState = GAMEOVER;
        mGameOverLabel->setVisible(true);
        mFrameCounter = 0;
    }
}

void Level::updateScrolling()
{
    if (mPlayer->getState() == Player::KILLED ||
		mState == LEVEL_COMPLETE ||
		mState == GAMEOVER )
    {
		return;
    }
    
	if (isBurnPressed())
    {
	    float wantedScroll = mPlayer->getY() - 40.0f + mPlayer->getSpeed();
	    float scrollAmount = wantedScroll - mGameScrollFloat;
	    float wantedSpeed = mPlayer->getSpeed();
	    float speedAdjust = wantedSpeed - mScrollSpeed;
        mScrollSpeed += speedAdjust / 40.0f;
        mGameScrollFloat += mScrollSpeed + scrollAmount / 20.0f;
    	
	    mGameScrollY = (int)mGameScrollFloat;
    }
    else
    {
	    float wantedScroll = mPlayer->getY() - 40.0f + mPlayer->getSpeed() * 5.0f;
	    float scrollAmount = wantedScroll - mGameScrollFloat;
	    float wantedSpeed = mPlayer->getSpeed();
	    float speedAdjust = wantedSpeed - mScrollSpeed;
        
        mScrollSpeed += speedAdjust / 20.0f;
        mGameScrollFloat += mScrollSpeed + scrollAmount / 10.0f;
    	
        if ((int)mGameScrollFloat > mGameScrollY)
        {
	       mGameScrollY = (int)mGameScrollFloat;
        }
    }

	if (mGameScrollY + 240 > mLevelLength)
	{
		mGameScrollY = mLevelLength - 240;
	}
}

void Level::load(const std::string& filename)
{
    std::vector<std::string> data = tokenize(loadFile(filename), "\n");

    unsigned int row;
    unsigned int col;

    mLevelName = data[0];
    data.erase(data.begin());

    std::string motifName = data[0];

    if (motifName == "SPACE")
    {
        mMotif = SPACE_MOTIF;
        mBackground = new StarsBackground();
		playMusic("greaty.xm", 1.0f);
		mAirResistance = Player::AIR_RESISTANCE_LOW;
    }
    else if (motifName == "WATER")
    {
        mMotif = WATER_MOTIF;
        mBackground = new WaterBackground();
		playMusic("greaty.xm", 1.0f);
		mAirResistance = Player::AIR_RESISTANCE_HIGH;
    }
    else if (motifName == "SKY")
    {
        mMotif = SKY_MOTIF;
        mBackground = new SkyBackground();
		playMusic("world_on_fire.xm", 1.0f);
        mAirResistance = Player::AIR_RESISTANCE_MEDIUM;
    }
    else if (motifName == "CAVE")
    {
        mMotif = CAVE_MOTIF;
        mBackground = new CaveBackground();
		playMusic("world_on_fire.xm", 1.0f);
        mAirResistance = Player::AIR_RESISTANCE_MEDIUM;
    }
    else if (motifName == "BONUS")
    {
        mMotif = BONUS_MOTIF;
        mBackground = new BonusBackground();
		playMusic("finalman-quickie.xm", 1.4f);
        mAirResistance = Player::AIR_RESISTANCE_LOW;
    }
	else
    {
        throw DBSH07_EXCEPTION("Unknown motif (Available is SPACE, SKY, WATER, CAVE and BONUS)!");
    }

    data.erase(data.begin());

    mLevelParTime = fromString<int>(data[0]);
    data.erase(data.begin());

    // Load entities
    for (row = 0; row < data.size(); row++)
    {
		pollMusic();

        if (data[row] == "DIALOG")
        {
            break;
        }

        if (data[row].size() < BLOCK_WIDTH)
        {
            throw DBSH07_EXCEPTION("Row number " + toString(row) + " is to short in file " + filename + ".");
        }
        else if (data[row].size() > BLOCK_WIDTH)
        {
            throw DBSH07_EXCEPTION("Row number " + toString(row) + " is to long in file " + filename + ".");
        }

		mLevelLength = row * BLOCK_SIZE + BLOCK_SIZE;

        for (col = 0; col < data[row].size(); col++)
        {
            Entity* staticEntity = NULL;
			Entity* entity = NULL;

            switch(data[row].at(col))
            {
                case '.':
					// Ignore
                    break;
				case 'Z':					
					switch (mMotif)
					{
					case SPACE_MOTIF:
						mEntities.push_back(new Planet("planet.bmp"));
						break;
					case WATER_MOTIF:
						mEntities.push_back(new Planet("seabed.bmp"));
						break;
					default:
						break;
					}
					break;
                case '1':
				case '2':
				case '3':
                case '4':
				case '5':
				case '6':
                    mNumberOfBlocks++;
                    if (mMotif == SPACE_MOTIF || mMotif == CAVE_MOTIF || mMotif == BONUS_MOTIF)
                    {
                        staticEntity = new Block(col * BLOCK_SIZE,
                                                 row * BLOCK_SIZE, 
                                                 BLOCK_SIZE,
                                                 BLOCK_SIZE, 
                                                 "spaceblock.bmp", data[row].at(col) - '0');                        
                    }
					else if (mMotif == WATER_MOTIF || mMotif == SKY_MOTIF)
                    {
                        staticEntity = new Block(col * BLOCK_SIZE,
                                                 row * BLOCK_SIZE, 
                                                 BLOCK_SIZE,
                                                 BLOCK_SIZE, 
                                                 "waterblock.bmp", data[row].at(col) - '0');                        
                    }

					mHibernatingEntities.push_back(staticEntity);
                   break;
                case 'M':
                    entity = new Mine(col*BLOCK_SIZE,row*BLOCK_SIZE, false);
                    mHibernatingEntities.push_back(entity);
                   break;
                case 'm':
                    entity = new Mine(col*BLOCK_SIZE,row*BLOCK_SIZE, true);
                    mHibernatingEntities.push_back(entity);
                   break;
                case 'r':
					entity = new Turret(col*BLOCK_SIZE,row*BLOCK_SIZE, Turret::RIGHT, 1);
                    mHibernatingEntities.push_back(entity);
                   break;
				case 'l':
					entity = new Turret(col*BLOCK_SIZE,row*BLOCK_SIZE, Turret::LEFT, 1);
                    mHibernatingEntities.push_back(entity);
                   break;
                case 'u':
					entity = new Turret(col*BLOCK_SIZE,row*BLOCK_SIZE, Turret::UP, 1);
                    mHibernatingEntities.push_back(entity);
                   break;
				case 'd':
					entity = new Turret(col*BLOCK_SIZE,row*BLOCK_SIZE, Turret::DOWN, 1);
                    mHibernatingEntities.push_back(entity);
                   break;
                case 'R':
					entity = new Turret(col*BLOCK_SIZE,row*BLOCK_SIZE, Turret::RIGHT, 3);
                    mHibernatingEntities.push_back(entity);
                   break;
				case 'L':
					entity = new Turret(col*BLOCK_SIZE,row*BLOCK_SIZE, Turret::LEFT, 3);
                    mHibernatingEntities.push_back(entity);
                   break;
                case 'U':
					entity = new Turret(col*BLOCK_SIZE,row*BLOCK_SIZE, Turret::UP, 3);
                    mHibernatingEntities.push_back(entity);
                   break;
				case 'D':
					entity = new Turret(col*BLOCK_SIZE,row*BLOCK_SIZE, Turret::DOWN, 3);
                    mHibernatingEntities.push_back(entity);
                   break;
				case 'E':
				case 'e':
                    mNumberOfBlocks++;
					if (mMotif == SPACE_MOTIF || mMotif == CAVE_MOTIF || mMotif == BONUS_MOTIF)
                    {
                        staticEntity = new Block(col * BLOCK_SIZE,
                                                 row * BLOCK_SIZE, 
                                                 BLOCK_SIZE,
                                                 BLOCK_SIZE, 
                                                 "spaceblock_e.bmp",
												 data[row].at(col) == 'E' ? 6 : 3,
												 true);                        
                    }
					else if (mMotif == WATER_MOTIF || mMotif == SKY_MOTIF)
                    {
                        staticEntity = new Block(col * BLOCK_SIZE,
                                                 row * BLOCK_SIZE, 
                                                 BLOCK_SIZE,
                                                 BLOCK_SIZE, 
                                                 "spaceblock_e.bmp",
												 6,
												 true);                        
                    }

					mHibernatingEntities.push_back(staticEntity);
                    break;
				case 'f':
                    entity = new Floater(col*BLOCK_SIZE,row*BLOCK_SIZE, 2);
                    mHibernatingEntities.push_back(entity);
                    break;
				case 'V':
                    entity = new Vulcano(col*BLOCK_SIZE, row*BLOCK_SIZE);
                    mHibernatingEntities.push_back(entity);
                    break;
				case '~':
                    staticEntity = new Electro(col*BLOCK_SIZE, row*BLOCK_SIZE);
                    mHibernatingEntities.push_back(staticEntity);
                    break;
				case '0':
                    if (mMotif == SPACE_MOTIF || mMotif == SKY_MOTIF || mMotif == BONUS_MOTIF)
                    {
                        staticEntity = new Block(col * BLOCK_SIZE,
                                                 row * BLOCK_SIZE, 
                                                 BLOCK_SIZE,
                                                 BLOCK_SIZE, 
                                                 "spacesolidblock.bmp", -1);                     
                    }
					else if (mMotif == WATER_MOTIF || mMotif == CAVE_MOTIF)
                    {
                        staticEntity = new Block(col * BLOCK_SIZE,
                                                 row * BLOCK_SIZE, 
                                                 BLOCK_SIZE,
                                                 BLOCK_SIZE, 
                                                 "spacesolidblock.bmp", -1);
                    }
					
					mHibernatingEntities.push_back(staticEntity);
                   break;
                default:
                    throw DBSH07_EXCEPTION("Unknown entity " + toString(data[row].at(col)));
            }
            mStaticEntities.push_back(staticEntity);
        }
    }

    // Load dialog
    if (row < data.size() && data[row] == "DIALOG")
    {
        mState = DIALOG;

        for (unsigned int i = row + 1; i < data.size(); i ++)
        {
            mDialogText.push_back(data[i]);
        }
    }
    else
    {
        mState = GAME;
    }
}

void Level::addShakeAmount(int amount)
{
	mShakeAmount += amount;
}

void Level::addEntity(Entity* entity)
{
    switch (entity->getType())
    {
        case Entity::ENEMY_BULLET_TYPE:
            mEnemyBulletEntities.push_back(entity);
            break;
        case Entity::ENEMY_TYPE:
            mNumberOfEnemies++;
            mEnemyEntities.push_back(entity);
            break;
        case Entity::PLAYER_BULLET_TYPE:
            mPlayerBulletEntities.push_back(entity);
            break;
        case Entity::PLAYER_TYPE:
            mPlayerEntities.push_back(entity);
            break;
        case Entity::POWER_UP_TYPE:
            mPowerUpEntities.push_back(entity);
            break;
    }

    mEntities.push_back(entity);
}

int Level::getMouseX()
{
	return mouse_x / 2 - 60;
}

int Level::getMouseY()
{
	return mouse_y / 2 + mGameScrollY;
}

Player* Level::getPlayer()
{
	return mPlayer;
}

bool Level::isFirePressed()
{
	return (mouse_b & 1) != 0;
}

bool Level::isBrakePressed()
{
    return key[KEY_W] != 0 || key[KEY_UP] != 0;
}

bool Level::isBurnPressed()
{
    return key[KEY_S] != 0 || key[KEY_DOWN] != 0;
}

bool Level::isMegaBlastPressed()
{
    return (mouse_b & 2) != 0;
}

void Level::checkCollision(std::list<Entity*>& list1, std::list<Entity*>& list2)
{
    std::list<Entity *>::iterator it1;
    std::list<Entity *>::iterator it2;

    for (it1 = list1.begin(); it1 != list1.end(); it1++)
    {
        for (it2 = list2.begin(); it2 != list2.end(); it2++)
        {			
            Entity* entity1 = (*it1);
            Entity* entity2 = (*it2);

            if (entity1->collidesWith(entity2))
            {
                entity1->handleCollision(entity2, this);
                entity2->handleCollision(entity1, this);
            }
        }
    }
}

void Level::checkStaticCollision(std::list<Entity*>& list)
{
    std::list<Entity *>::iterator it;

    for (it = list.begin(); it != list.end(); it++)
    {
        Entity* entity = (*it);

        if (!entity->isCollidable())
        {
            continue;
        }
    
        int minx = entity->getX() / BLOCK_SIZE;
        int miny = entity->getY() / BLOCK_SIZE;
        int maxx = (entity->getX() + entity->getWidth() - 1) / BLOCK_SIZE;
        int maxy = (entity->getY() + entity->getHeight() - 1) / BLOCK_SIZE;

		if (minx >= BLOCK_WIDTH || maxx < 0)
		{
			continue;
		}

		if (minx < 0)
		{
			minx = 0;
		}

		if (miny < 0)
		{
			miny = 0;
		}

		if (maxx >= BLOCK_WIDTH)
		{
			maxx = BLOCK_WIDTH - 1;
		}

        for (int x = minx; x <= maxx; x++)
        {
            for (int y = miny; y <= maxy; y++)
            {
				unsigned int i = x + y * BLOCK_WIDTH;
				
				if (i >= mStaticEntities.size())
				{
					continue;
				}

                Entity* otherEntity = mStaticEntities[i];
      
                if (otherEntity != NULL 
                    && otherEntity->isCollidable())
                {
                    entity->handleCollision(otherEntity, this);
                    otherEntity->handleCollision(entity, this);
                }   
            }
        }
    }
}

void Level::spawnDebris(int amount, int x, int y, int w, int h)
{
	for (int i = 0; i < amount; i++)
	{
		Debris *d = new Debris(x + rand() % w,
							   y + rand() % h,
							   (frand() - 0.5f) * 5.0f,
							   (frand() - 0.2f) * 10.0f,
							   "debris.bmp", 
                               2);

		addEntity(d);
	}

	if (mMotif == WATER_MOTIF)
	{
		for (int i = 0; i < amount; i++)
		{
			Debris *d = new Debris(x + rand() % w,
								   y + rand() % h,
								   (frand() - 0.5f) * 5.0f,
								   (frand() - 0.5f) * 10.0f,
								   rand() & 1 ? "bubble.bmp" : "bubblesmall.bmp", 
								   2);

			addEntity(d);
		}
	}
}

void Level::spawnExplosions(int amount, int x, int y, int w, int h)
{
	for (int i = 0; i < amount; i++)
	{
		Debris *d = new Debris(x + rand() % w,
							   y + rand() % h,
							   (frand() - 0.5f) * 5.0f,
							   (frand() - 0.2f) * 10.0f,
							   "explosion.bmp", 
                               2 + rand() % 3, 
                               true);

		addEntity(d);
	}
}