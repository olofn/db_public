#include "level.hpp"

#include "resourcehandler.hpp"
#include "fileutil.hpp"
#include "music.hpp"
#include "exception.hpp"
#include "stringutil.hpp"
#include "util.hpp"
#include "entities/snow.hpp"
#include "entities/star.hpp"
#include "entities/light.hpp"
#include "entities/gradientbackground.hpp"
#include "entities/goal.hpp"
#include "entities/fly.hpp"
#include "entities/movingspikes.hpp"
#include "entities/cloudsbackground.hpp"
#include "entities/bomb.hpp"
#include "entities/particles.hpp"
#include "entities/explodabletile.hpp"
#include "entities/breakingtile.hpp"
#include "entities/disappearingtile.hpp"
#include "entities/spikes.hpp"
#include "entities/patrol.hpp"
#include "entities/rollingspikes.hpp"
#include "entities/laserbeam.hpp"
#include "entities/button.hpp"
#include "entities/doortile.hpp"
#include "entities/bubbles.hpp"
#include "fading.hpp"

#include <iostream>

// Predicate function used to remove entities.
static bool isNull(Entity *e) 
{
	return e == NULL;
}

Level::Level(gcn::Container* top, const std::string& filename, int totalStarsCollected)
: mCountdownAnimation("countdown.bmp"),
  mReadySteadyGoAnimation("readysteadygo.bmp")
{
    mShakeAmount = 0;
    mFrameCounter = -50;
    mTop = top;

    mDialog = new Dialog();
    mDialog->setSize(320, 75);
    mTop->add(mDialog, 0, 240 - 75);
    mDialog->setVisible(false);

    mTimeLabel = new gcn::Label("0000");
    mTimeLabel->adjustSize();
    mTop->add(mTimeLabel, 160 - mTimeLabel->getWidth() / 2, 3);

    mStarsLabel = new gcn::Label("~x0");
    mStarsLabel->adjustSize();
    mTop->add(mStarsLabel, 320 - mStarsLabel->getWidth(), 3);

    mEscapePressed = false;
    mGoalReached = false;
    mCollectedStars = 0;

    load(filename);

    mPlayer->setTotalStarsCollected(totalStarsCollected);
    mTotalStarsCollected = totalStarsCollected;
}

Level::~Level()
{
    std::list<Entity *>::iterator it;
    for (it = mEntities.begin(); it != mEntities.end(); it++)
        delete (*it);

    delete mTileMap;

    mTop->clear();
    delete mTimeLabel;
    delete mDialog;
    delete mStarsLabel;
}

void Level::setCollectedStars(int collectedStars)
{
    mCollectedStars = collectedStars;
}

int Level::getCollectedStars()
{
    return mCollectedStars;
}

bool Level::isGameOver()
{
    return mPlayer->isDead();
}

bool Level::isGoalReached()
{
    return mGoalReached;
}

void Level::setGoalReached(bool reached)
{
    mGoalReached = true;
}

void Level::draw(BITMAP* dest)
{
    int scrollx = mCamera->getX();
    int scrolly = mCamera->getY();

    int oldscrolly = scrolly;

    int xOffs = 0, yOffs = 0;
	if (mShakeAmount > 100)
	{
		int shakeAmount = ((mShakeAmount - 100) / 25.0f);
		if (shakeAmount > 60) 
            shakeAmount = 60;

		xOffs = shakeAmount*(frand()-0.5f);
		yOffs = shakeAmount*(frand()-0.5f);
		scrolly += yOffs;
	}

	BITMAP* subdest = create_sub_bitmap(dest, xOffs, 16, 320, 224); 

    std::list<Entity *>::iterator it;
    for (it = mEntities.begin(); it != mEntities.end(); it++)
    {
        Entity* entity = (*it);
        if (entity->drawInLayer(Entity::BACKGROUND_LAYER))
            entity->draw(subdest, scrollx, scrolly, Entity::BACKGROUND_LAYER);
    }
    for (it = mEntities.begin(); it != mEntities.end(); it++)
    {
        Entity* entity = (*it);
        if (entity->drawInLayer(Entity::PLAYER_LAYER))
            entity->draw(subdest, scrollx, scrolly, Entity::PLAYER_LAYER);
    }

    for (it = mEntities.begin(); it != mEntities.end(); it++)
    {
        Entity* entity = (*it);
        if (entity->drawInLayer(Entity::BEFORE_TILES_LAYER))
            entity->draw(subdest, scrollx, scrolly, Entity::BEFORE_TILES_LAYER);
    }

    mTileMap->draw(subdest, scrollx, scrolly);

    for (it = mEntities.begin(); it != mEntities.end(); it++)
    {
        Entity* entity = (*it);
        if (entity->drawInLayer(Entity::AFTER_TILES_LAYER))
            entity->draw(subdest, scrollx, scrolly, Entity::AFTER_TILES_LAYER);
    }

    for (it = mEntities.begin(); it != mEntities.end(); it++)
    {
        Entity* entity = (*it);
        if (entity->drawInLayer(Entity::FOREGROUND_LAYER))
            entity->draw(subdest, scrollx, scrolly, Entity::FOREGROUND_LAYER);
    }

    if (mLevelTime <= 500 && mFrameCounter % 50 < 25 || mLevelTime < 50)
        mCountdownAnimation.drawFrame(dest, 
                                      mLevelTime / 50, 
                                      160 - mCountdownAnimation.getFrameWidth() / 2,
                                      120 - mCountdownAnimation.getFrameHeight() / 2,
                                      false,
                                      false,
                                      Animation::ADD);

    if (mState == GAME && mFrameCounter < 150 && mFrameCounter > 0 && (mFrameCounter % 50 < 25 || mFrameCounter > 100))
    {
        mReadySteadyGoAnimation.drawFrame(dest, 
                                          mFrameCounter / 50,
                                          160 - mReadySteadyGoAnimation.getFrameWidth() / 2,
                                          120 - mReadySteadyGoAnimation.getFrameHeight() / 2,
                                          false,
                                          false,
                                          Animation::ADD);
    }

    hline(dest, 0, 16, 320, makecol(255, 255, 255));

    rectfill(dest, 7, 7, 6 + mPlayer->getLaserShieldStatus(), 8, 
             mPlayer->isLaserShielded()? makecol(217, 0, 85): makecol(128, 128, 128));
	rect(dest, 5, 5, 108, 10, makecol(255, 255, 255));

    destroy_bitmap(subdest);
}
   
void Level::logic()
{
    if (mState == DIALOG)
    {
        logicDialog();
    }
    else
    {
        logicGame();
    }
}

void Level::logicDialog()
{
    if ((key[KEY_ESC] != 0) && !mEscapePressed)
    {
        mDialog->setVisible(false);
        mState = GAME;
    }
    else if (mDialog->isDone() && mDialogText.empty())
    {
        mState = GAME;
        mDialog->setVisible(false);
    }
    else if (mDialog->isDone())
    {
        mDialog->setText(mDialogText.front());
        mDialogText.pop_front();
    } 

    logicEntities();
    logicShakes();

    mEscapePressed = key[KEY_ESC] != 0;
}

void Level::logicGame()
{
    if (mPlayer->isDead())
    {
        return;    
    }

    if (keypressed() && (readkey() >> 8) == KEY_ESC)
    {
        mPlayer->kill();    
    }

    mFrameCounter++;

    if (mFrameCounter >100 && mPlayer->isFreezed())
    {
        mPlayer->unfreeze();
    }

    logicTime();
    logicStars();
    logicEntities();
    logicShakes();
}

void Level::logicShakes()
{
    if (mShakeAmount > 0) 
        mShakeAmount /= 1.045;
  
   
    if (mLevelTime < 500)
    {
        if (frand() * 100 < 30)
        {
            mShakeAmount += 75;
        }
    }
    else if ( mLevelTime < 1000)
    {
        if (frand() * 100 < 25)
        {
            mShakeAmount += 60;
        }
    }
    else if (mLevelTime < 3000)
    {
        if (frand() * 100 < 5)
        {
            mShakeAmount += 105;
        }
    }
    else
    {
        if (frand() * 100 < 2)
            mShakeAmount += 150;
    }
}

void Level::logicTime()
{
    if (mFrameCounter > 150)
        mLevelTime--;

    if (mLevelTime < 0)
    {
        mLevelTime = 0; 
        mPlayer->kill();
    }

    std::string time = "";
    int minutes = (mLevelTime / 50) / 60;
    int seconds = (mLevelTime / 50) % 60;
        
    if (minutes < 0)
    {
        time += "0:";
    }
    else
    {
        time += toString(minutes) + ":";
    }

    if (seconds < 10)
    {
        time += "0";
    }

    time += toString(seconds);

    mTimeLabel->setCaption(time);
    mTimeLabel->adjustSize();
}

void Level::logicStars()
{
    std::string stars = "~x" + toString(mCollectedStars);
    mStarsLabel->setCaption(stars);
    mStarsLabel->adjustSize();
}

void Level::logicEntities()
{
    std::list<Entity *>::iterator it;
    for (it = mEntities.begin(); it != mEntities.end(); it++)
    {
        if ((*it)->isToBeDeleted())
            (*it) = NULL;
        else
            (*it)->logic(this);
    }

     mEntities.remove_if(isNull);

    for (it = mEntities.begin(); it != mEntities.end(); it++)
    {
        Entity* entity = (*it);
        if (!entity->isCollidable())
            continue;

        if (entity->collidesWith(mPlayer))
        {
            entity->handleCollision(mPlayer, this);
            mPlayer->handleCollision(entity, this);
        }
    }
}

TileMap* Level::getTileMap()
{
    return mTileMap;
}

Player* Level::getPlayer()
{
    return mPlayer;
}

Camera* Level::getCamera()
{
    return mCamera;
}
void Level::load(const std::string& filename)
{
    mTileMap = new TileMap(filename);

    std::cout << "Loading entities " + filename + "...";
    std::vector<std::string> data = tokenize(loadFile(filename), "\n");

    mPlayer = new Player(0, 0);
    mEntities.push_back(mPlayer);
    mCamera = new Camera();
    mCamera->setTarget(mPlayer);
    mEntities.push_back(mCamera);

    data.erase(data.begin()); // Discard level name
    data.erase(data.begin()); // Discard stars to unlock

    mLevelTime = fromString<int>(data[0]);
    mLevelTime++;
    logicTime();
    data.erase(data.begin());
    
    std::string levelMusic = data[0];
    playMusic(levelMusic, 0.5f);
    data.erase(data.begin());

    unsigned int row;
    unsigned int col;

    int width = 0;
    for (row = 0; row < data.size(); row++)
    {
		pollMusic();
       
        if (row == 0)
            width = data[row].size();

        if (data[row] == "DIALOG")
        {

            break;
        }

        if ((int)data[row].size() < width)
        {
            throw DB_EXCEPTION("Row number " + toString(row) + " is to short in file " + filename + ".");
        }
        else if ((int)data[row].size() > width)
        {
            throw DB_EXCEPTION("Row number " + toString(row) + " is to long in file " + filename + ".");
        }

        for (col = 0; col < data[row].size(); col++)
        {
            switch(data[row].at(col))
            {
                case 'q':
                    {
				    Snow* snow = new Snow();
                    mEntities.push_back(snow);
                    }
                    break;
                 case 'w':
                    {
				    CloudsBackground* c = new CloudsBackground();
                    mEntities.push_back(c);
                    }
                    break;
                case 'e':
                    {
				    GradientBackground* g = new GradientBackground(128,128,128,0,0,0);
                    mEntities.push_back(g);
                    }
                    break;
                  case 'r':
                    {
				    GradientBackground* g = new GradientBackground(50,50,50,0,0,0);
                    mEntities.push_back(g);
                    }
                    break;
                 case 't':
                    {
				    GradientBackground* g = new GradientBackground(0,0,0,157,2,61);
                    mEntities.push_back(g);
                    }
                    break;
                 case 'y':
                    {
				    Bubbles* g = new Bubbles();
                    mEntities.push_back(g);
                    }
                    break;
                case 'a':
                    {
				    Button* b = new Button(col*16, row*16);
                    mEntities.push_back(b);
                    }
                    break;
                case 's':
                    {
				    Star* star = new Star(col*16, row*16);
                    mEntities.push_back(star);
                    }
                    break;
                case 'd':
                    {
				    DoorTile* d = new DoorTile(col*16, row*16, false);
                    mEntities.push_back(d);
                    }
                    break;
                case 'f':
                    {
				    DoorTile* d = new DoorTile(col*16, row*16, true);
                    mEntities.push_back(d);
                    }
                    break;
                
                case 'l':
                    {
				    Light* light = new Light(col*16, row*16);
                    mEntities.push_back(light);
                    }
                    break;
                case 'g':
                    {
				    Goal* goal = new Goal(col*16, row*16);
                    mEntities.push_back(goal);
                    }
                    break;
                case 'h':
                    {
				    Fly* f = new Fly(col*16, row*16);
                    mEntities.push_back(f);
                    }
                    break;
                case 'x':
                    {
                    Spikes* s = new Spikes(col*16, row*16);
                    mEntities.push_back(s);
                    }
                    break;
                  case 'z':
                    {
                    Patrol* p = new Patrol(col*16, row*16);
                    mEntities.push_back(p);
                    }
                    break;
                 case 'c':
                    {
                        MovingSpikes* l = new MovingSpikes(col*16, row*16, MovingSpikes::FLOOR);
                     mEntities.push_back(l);
                    }
                    break;
                 case 'v':
                    {
                        MovingSpikes* l = new MovingSpikes(col*16, row*16, MovingSpikes::CEILING);
                     mEntities.push_back(l);
                    }
                    break;
                case 'b':
                    {
                        RollingSpikes* l = new RollingSpikes(col*16, row*16);
                     mEntities.push_back(l);
                    }
                    break;
                 case 'n':
                    {
                        LaserBeam* l = new LaserBeam(col*16, row*16, false);
                     mEntities.push_back(l);
                    }
                    break;
                  case 'm':
                    {
                        LaserBeam* l = new LaserBeam(col*16, row*16, true);
                     mEntities.push_back(l);
                    }
                    break;
                case 'p':
                    {
                        mPlayer->setPosition(col*16, row*16);
                        mCamera->setPosition(col*16 - 160, row*16 - 120);

                        // Ouch, this is ugly! We need the camera to be in position
                        // before the game starts.
                        for (int c = 0; c < 10; c++)
                        {
                            mCamera->logic(this);
                        }
                    }
                    break;
                case '2':
                    {
				    ExplodableTile* e = new ExplodableTile(col*16, row*16);
                    mEntities.push_back(e);
                    }
                    break;
                case '3':
                    {
				    BreakingTile* e = new BreakingTile(col*16, row*16);
                    mEntities.push_back(e);
                    }
                    break;
                case '4':
                    {
				    DisappearingTile* e = new DisappearingTile(col*16, row*16, 0);
                    mEntities.push_back(e);
                    }
                    break;
                case '5':
                    {
				    DisappearingTile* e = new DisappearingTile(col*16, row*16, 50);
                    mEntities.push_back(e);
                    }
                    break;
                case '6':
                    {
				    DisappearingTile* e = new DisappearingTile(col*16, row*16, 100);
                    mEntities.push_back(e);
                    }
                    break;
                case '7':
                    {
				    DisappearingTile* e = new DisappearingTile(col*16, row*16, 150);
                    mEntities.push_back(e);
                    }
                    break;
            }
        }
    }

    std::cout << " Done!" << std::endl;

    // Load dialog
    if (row < data.size() && data[row] == "DIALOG")
    {
        for (unsigned int i = row + 1; i < data.size(); i ++)
        {
            mDialogText.push_back(data[i]);
        }

        mState = DIALOG;

        if (mDialogText.size() > 0)
        {
            mDialog->setText(mDialogText.front());
            mDialogText.pop_front();
            mDialog->setVisible(true);
            mDialog->requestFocus();
        }
    }
    else
    {
        mState = GAME;
    }

    mPlayer->freeze();
}

void Level::distributeMessage(const std::string& message, Entity* distributor)
{
    std::list<Entity *>::iterator it;
    for (it = mEntities.begin(); it != mEntities.end(); it++)
        (*it)->message(message, distributor);
}

void Level::addEntity(Entity* entity)
{
    mEntities.push_back(entity);
}

void Level::spawnExplosions(int amount, int x, int y, int w, int h)
{
	for (int i = 0; i < amount; i++)
	{
		Particles *d = new Particles(x + rand() % w,
							   y + rand() % h,
							   (frand() - 0.5f) * 5.0f,
							   (frand() - 0.2f) * 10.0f,
							   "explosion.bmp", 
                               2 + rand() % 3, 
                               true);

		addEntity(d);
	}
}
