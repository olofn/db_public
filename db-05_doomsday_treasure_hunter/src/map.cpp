#include "map.hpp"
#include <fstream>
#include <iostream>
#include "stringutil.hpp"
#include "exception.hpp"
#include "fileutil.hpp"
#include "music.hpp"
#include "resourcehandler.hpp"
#include "util.hpp"

Map::Map(gcn::Container* top, const std::string& filename)
:mMapAnimation("map.bmp"),
mPlayerAnimation("playermap.bmp")
{
    mPlayerX = -1;
    mPlayerY = -1;
    mLevelSelected = false;
    mTop = top;
    mTotalStarsCollected = 0;
    mTotalStars = 0;

    mMapLabel = new gcn::Label("Map of the galaxy Dooms Way");
    mMapLabel->adjustSize();
    mTop->add(mMapLabel, 160 - mMapLabel->getWidth() / 2, 3);

    mTotalStarsCollectedLabel = new gcn::Label();
    mTop->add(mTotalStarsCollectedLabel);

    mLevelInfo = new gcn::Label();
    mTop->add(mLevelInfo);

    mMoveSample = ResourceHandler::getInstance()->getSample("jump.wav");
    mBackground = ResourceHandler::getInstance()->getBitmap("menubackground.bmp");

    load(filename);
    loadSave();

    for (int i = 0; i < 200; i++)
    {
        mParticles.push_back(new Particle(frand() * 320, frand()* 240, frand()* 3 + 1));
    }

    mFrameCounter = 0;
}

Map::~Map()
{
    writeSave();
    for (int i = 0; i < mLocations.size(); i++)
        delete mLocations[i];

    delete mMapLabel;
    delete mTotalStarsCollectedLabel;
    delete mLevelInfo;

    for (int i = 0; i < mParticles.size(); i++)
        delete mParticles[i];
}

bool Map::isLevelSelected()
{
    return mLevelSelected;
}

void Map::init()
{
    mLevelSelected = false;
}

void Map::setStarsCollected(const std::string& filename, int stars)
{   
    for (int i = 0; i < mLocations.size(); i++)
    {
        if (mLocations[i]->level
            && mLocations[i]->levelfilename == filename
            && mLocations[i]->starsCollected < stars)
        {
            mLocations[i]->starsCollected = stars;
        }
    }

    mTotalStarsCollected = 0;
    for (int i = 0; i < mLocations.size(); i++)
    {
          if (mLocations[i]->level)
            mTotalStarsCollected += mLocations[i]->starsCollected;
    }
}

void Map::draw(BITMAP* dest)
{
    draw_sprite(dest, mBackground, 0, 0);

    for (int i = 0; i < mParticles.size(); i++)
        putpixel(dest, mParticles[i]->x, mParticles[i]->y, makecol(255 / mParticles[i]->z, 255 / mParticles[i]->z, 255 / mParticles[i]->z) );

    for (int y = 0; y < 12; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            Location* l = mLocations[x + y * 20];
            if (l->road)
            {
                mMapAnimation.drawFrame(dest, l->roadType, l->x, l->y + 32);
            }
            // It should never be greater, but what the hell...
            else if (l->level && l->stars <= l->starsCollected)
            {
                mMapAnimation.drawFrame(dest, 13, l->x, l->y + 32);
            }
            else if (l->level && mTotalStarsCollected >= l->starsToUnlock)
            {
                mMapAnimation.drawFrame(dest, 11, l->x, l->y + 32);
            }
            else if (l->level && mTotalStarsCollected < l->starsToUnlock)
            {
                mMapAnimation.drawFrame(dest, 12, l->x, l->y + 32);
            }
        }
    }

    mPlayerAnimation.drawFrame(dest, mFrameCounter / 20, mPlayerX, mPlayerY + 32);

    rectfill(dest, 0, 0, 320, 30, 0);
    hline(dest, 0, 30, 320, makecol(255, 255, 255));

    rectfill(dest, 0, 226, 320, 240, 0);
    hline(dest, 0, 226, 320, makecol(255, 255, 255));
   
}

bool Map::isSolidRight()
{
    int x = mPlayerX / 16;
    int y = mPlayerY / 16;

    x++;

    if (x > 19)
        return true;

    return mLocations[x + y * 20]->solid;
}

bool Map::isLevel()
{
    int x = mPlayerX / 16;
    int y = mPlayerY / 16;

    return mLocations[x + y * 20]->level;
}

bool Map::isSolidLeft()
{
    int x = mPlayerX / 16;
    int y = mPlayerY / 16;

    x--;

    if (x < 0)
        return true;

    return mLocations[x + y * 20]->solid;
}

bool Map::isSolidUp()
{
    int x = mPlayerX / 16;
    int y = mPlayerY / 16;

    y--;

    if (y < 0)
        return true;

    return mLocations[x + y * 20]->solid;
}

bool Map::isSolidDown()
{
    int x = mPlayerX / 16;
    int y = mPlayerY / 16;

    y++;

    if (y > 11)
        return true;

    return mLocations[x + y * 20]->solid;
}

std::string Map::getLevelFilename()
{
    int x = mPlayerX / 16;
    int y = mPlayerY / 16;


   return mLocations[x + y * 20]->levelfilename;
}

std::string Map::getLevelName()
{
    int x = mPlayerX / 16;
    int y = mPlayerY / 16;


   return mLocations[x + y * 20]->levelName;
}

int Map::getLevelStars()
{
    int x = mPlayerX / 16;
    int y = mPlayerY / 16;


   return mLocations[x + y * 20]->stars;
}

int Map::getLevelStarsCollected()
{
    int x = mPlayerX / 16;
    int y = mPlayerY / 16;

   return mLocations[x + y * 20]->starsCollected;
}

int Map::getLevelStarsToUnlock()
{
    int x = mPlayerX / 16;
    int y = mPlayerY / 16;


   return mLocations[x + y * 20]->starsToUnlock;
}

void Map::logic()
{
    mFrameCounter++;

    for (int i = 0; i < mParticles.size(); i++)
    {
        mParticles[i]->x -= mParticles[i]->z;

        if (mParticles[i]->x < 0)
        {
            mParticles[i]->x = 320;
            mParticles[i]->y = frand()* 240;
            mParticles[i]->z = frand()* 3 + 1;
        }
    }

    mTotalStarsCollectedLabel->setCaption("~x" + toString(mTotalStarsCollected) + " collected");
    mTotalStarsCollectedLabel->adjustSize();
    mTotalStarsCollectedLabel->setPosition(160 - mTotalStarsCollectedLabel->getWidth() / 2, 16);

    if (isLevel() && getLevelStarsToUnlock() <= mTotalStarsCollected)
    {
        mLevelInfo->setCaption(getLevelName() + " " + toString(getLevelStarsCollected()) + "/" + toString(getLevelStars()) + "~");
        mLevelInfo->adjustSize();
        mLevelInfo->setPosition(160 - mLevelInfo->getWidth() / 2, 228);
    }
    else if (isLevel() && getLevelStarsToUnlock() > mTotalStarsCollected)
    {
        mLevelInfo->setCaption(getLevelName() + " LOCKED! " + toString(getLevelStarsToUnlock())+ "~ to unlock");
        mLevelInfo->adjustSize();
        mLevelInfo->setPosition(160 - mLevelInfo->getWidth() / 2, 228);
    }
    else
    {
        mLevelInfo->setCaption("");
    }

     mKeyState.setKeys(key[KEY_UP], 
                      key[KEY_DOWN], 
                      key[KEY_LEFT], 
                      key[KEY_RIGHT],
		              key[KEY_LCONTROL], 
                      key[KEY_ALT], 
                      key[KEY_LSHIFT],
                      key[KEY_I],
                      key[KEY_SPACE]);

     if (mKeyState.isRightPressed()
         && !isSolidRight())
     {
        mPlayerX += 16;
        play_sample(mMoveSample, 100, 128, 1000, 0);
        return;
     }

      if (mKeyState.isLeftPressed()
         && !isSolidLeft())
     {
        mPlayerX -= 16;
        play_sample(mMoveSample, 100, 128, 1000, 0);
        return;
     }

    if (mKeyState.isUpPressed()
     && !isSolidUp())
    {
        mPlayerY -= 16;
        play_sample(mMoveSample, 100, 128, 1000, 0);
        return;
    }

    if (mKeyState.isDownPressed()
     && !isSolidDown())
    {
        mPlayerY += 16;
        play_sample(mMoveSample, 100, 128, 1000, 0);
        return;
    }

    if ((mKeyState.isJumpPressed() || mKeyState.isSpecialPressed() || mKeyState.isLaserShieldPressed()
        || key[KEY_ENTER])
     && isLevel() && getLevelStarsToUnlock() <= mTotalStarsCollected)
    {
        mLevelSelected = true;
        return;
    }
}

void Map::load(const std::string& filename)
{
    std::cout << "Loading map " + filename + "...";
    std::vector<std::string> data = tokenize(loadFile(filename), "\n");
    unsigned int row;
    unsigned int col;

    for (row = 0; row < 12; row++)
    {
		pollMusic();

        if ((int)data[row].size() < 20)
        {
            throw DB_EXCEPTION("Row number " + toString(row) + " is to short in file " + filename + ".");
        }
        else if ((int)data[row].size() > 20)
        {
            throw DB_EXCEPTION("Row number " + toString(row) + " is to long in file " + filename + ".");
        }

        for (col = 0; col < 20; col++)
        {
            switch(data[row].at(col))
            {
                case '.':
                    {
					Location* l = new Location();
                    l->solid = true;
                    l->road = false;
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
                    break;
                case '<':
                    {
                    Location* l = new Location();
                    l->road = true;
                    l->roadType = 0;
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
                   break;
                  case '>':
                    {
                    Location* l = new Location();
                    l->road = true;
                    l->roadType = 1;
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
                   break;
                  case '|':
                    {
                    Location* l = new Location();
                    l->road = true;
                    l->roadType = 2;
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
                   break;
                 case 'z':
                    {
                    Location* l = new Location();
                    l->road = true;
                    l->roadType = 3;
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
                   break;
                 case 'x':
                    {
                    Location* l = new Location();
                    l->road = true;
                    l->roadType = 4;
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
                   break;
                  case 'c':
                    {
                    Location* l = new Location();
                    l->road = true;
                    l->roadType = 5;
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
                   break;
                   case 'v':
                    {
                    Location* l = new Location();
                    l->road = true;
                    l->roadType = 6;
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
                   break;
                   case 'b':
                    {
                    Location* l = new Location();
                    l->road = true;
                    l->roadType = 7;
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
                   break;
                  case 'n':
                    {
                    Location* l = new Location();
                    l->road = true;
                    l->roadType = 8;
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
                   break;
                  case 'm':
                    {
                    Location* l = new Location();
                    l->road = true;
                    l->roadType = 9;
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
                   break;
                  case ',':
                    {
                    Location* l = new Location();
                    l->road = true;
                    l->roadType = 10;
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
                   break;
                case 'p':
                    {
                    Location* l = new Location();
                    l->road = true;
                    l->roadType = 0;
                    l->x = col * 16;
                    l->y = row * 16;
                    mPlayerX = col * 16;
                    mPlayerY = row * 16;
                    mLocations.push_back(l);
                    }
                   break;
                default:
                    {
					Location* l = new Location();
                    l->level = true;
                    l->levelcharacter = data[row].at(col);
                    l->x = col * 16;
                    l->y = row * 16;
                    mLocations.push_back(l);
                    }
            }
        }
    }

    if (mPlayerX == -1 || mPlayerY == -1)
        throw DB_EXCEPTION("No player start point in map!");


    // Connect levels with level files.
    for (row = 12; row < data.size(); row++)
    {
        std::string col = data[row];
        char levelcharacter = col.at(0);
        std::string levelfilename  = col.substr(2, col.size() - 2);

        for (int i = 0; i < mLocations.size(); i++)
        {
            if (mLocations[i]->levelcharacter == levelcharacter)
            {
                mLocations[i]->levelfilename = levelfilename;
                mLocations[i]->stars = getStarsInLevel(levelfilename);
                mLocations[i]->levelName = getNameInLevel(levelfilename);
                mLocations[i]->starsToUnlock = getStarsToUnlockInLevel(levelfilename);
            }
        }
    }

    std::cout << " Done!" << std::endl;
}

int Map::getStarsInLevel(const std::string& filename)
{
    std::cout << "Getting stars in " + filename + "...";
    std::vector<std::string> data = tokenize(loadFile(filename), "\n");

    data.erase(data.begin()); // Discard level name
    data.erase(data.begin()); // Discard stars to unlock
    data.erase(data.begin()); // Discard level time
    data.erase(data.begin()); // Discard level music

    unsigned int row;
    unsigned int col;
    
    int stars = 0;

    // Load entities
    for (row = 0; row < data.size(); row++)
    {
		pollMusic();

        if (data[row] == "DIALOG")
        {
            break;
        }

        for (col = 0; col < data[row].size(); col++)
        {
            if (data[row].at(col) == 's')
                 stars++;
        }
    }

    std::cout << " Done!" << std::endl;

    return stars;
}

std::string Map::getNameInLevel(const std::string& filename)
{
    std::vector<std::string> data = tokenize(loadFile(filename), "\n");   
    return data[0];
}

int Map::getStarsToUnlockInLevel(const std::string& filename)
{
    std::vector<std::string> data = tokenize(loadFile(filename), "\n");   
    return fromString<int>(data[1]);
}

void Map::loadSave()
{
    try
    {
        std::vector<std::string> data = tokenize(loadFile("save.txt"), "\n"); 

        for (int row = 0; row < data.size(); row++)
        {
            if (data[row].size() == 0)
                break;

           
            char levelCharacter = data[row].at(0);
            std::string starsCollectedString = data[row].substr(2, data[row].size() - 2);
            int starsCollected = fromString<int>(starsCollectedString);

            for (int i = 0; i < mLocations.size(); i++)
            {       
                if (mLocations[i]->level && mLocations[i]->levelcharacter == levelCharacter)
                    mLocations[i]->starsCollected = starsCollected;
            }   
        }

        for (int i = 0; i < mLocations.size(); i++)
            mTotalStarsCollected += mLocations[i]->starsCollected;
    }
    catch (Exception e)
    {
        // File not found, ignore.
    }
}

int Map::getTotalStarsCollected()
{
    return mTotalStarsCollected;
}

void Map::writeSave()
{
    std::ofstream file;
    std::string saveFilename;
    saveFilename = "data/save.txt";

    file.open(saveFilename.c_str(), std::ios::out);
        
    if (!file.is_open())
    {
        throw DB_EXCEPTION("Saves file could not be opened for save! " + saveFilename);
    }
    
    unsigned int i;
    for (i = 0; i < mLocations.size(); i++)
    {
        if (mLocations[i]->level)
            file << mLocations[i]->levelcharacter << " " << mLocations[i]->starsCollected << std::endl;
    }
    
    file.close();
}
