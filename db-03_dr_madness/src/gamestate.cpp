#include "gamestate.hpp"
#include "fileutil.hpp"
#include "exception.hpp"
#include "stringutil.hpp"
#include <fstream>
#include <algorithm>
#include "resourcehandler.hpp"
#include "os.hpp"
#ifndef DB_WIN32
#include <stdlib.h>
#endif

GameState* GameState::mInstance = 0;

GameState* GameState::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new GameState();
        mInstance->loadLevelsData();
        mInstance->loadHighScore();
    }

    return mInstance;
}

GameState::GameState()
{
    reset();
}

void GameState::reset()
{
    mLives = 5;
    mLevel = 0;
    mPoints = 0;
    mEnergyOrbs = 0;
    mPods = 1;
    mCannonLevel = 1;
    mMegaBlasts = 3;
}

unsigned int GameState::getLives()
{
    return mLives;
}

void GameState::setLives(unsigned int lives)
{
    mLives = lives;
}

unsigned int GameState::getLevel()
{
    return mLevel;
}

void GameState::setLevel(unsigned int level)
{
    mLevel = level;
}

void GameState::setEnergyOrbs(unsigned int energyOrbs)
{
    mEnergyOrbs = energyOrbs;
}

unsigned int GameState::getEnergyOrbs()
{
    return mEnergyOrbs;
}

void GameState::setPods(unsigned int pods)
{
    mPods = pods;
}

unsigned int GameState::getPods()
{
    return mPods;
}

void GameState::setCannonLevel(unsigned int cannonLevel)
{
	mCannonLevel = cannonLevel;
}

unsigned int GameState::getCannonLevel()
{
	return mCannonLevel;
}

void GameState::setMegaBlasts(unsigned int megaBlasts)
{
	mMegaBlasts = megaBlasts;
}

unsigned int GameState::getMegaBlasts()
{
	return mMegaBlasts;
}

void GameState::loadLevelsData()
{
    std::vector<std::string> data = tokenize(loadFile("levels.txt"), "\n", true);

    if (data.size() == 0)
    {
        throw DBSH07_EXCEPTION("levels.txt is empty!");
    }

    int numberOfLevels = 0;
    int numberOfBonusLevels = 0;
    for (unsigned int i = 0; i < data.size(); i++)
    {
        std::vector<std::string> row = tokenize(data[i], " ");

        if (row.size() < 2)
        {
            throw DBSH07_EXCEPTION("Corrupt levels.txt file at row " + toString(i) + ".");
        }

        if (row[0] == "N")
        {
            numberOfLevels++;
            mLevelsData.push_back(LevelData(row[1], false, "LEVEL " + toString(numberOfLevels)));
        }
        else if (row[0] == "B")
        {
            numberOfBonusLevels++;
            mLevelsData.push_back(LevelData(row[1], true, "BONUS LEVEL " + toString(numberOfBonusLevels)));
        }
        else
        {
            throw DBSH07_EXCEPTION("Corrupt levels.txt file at row " 
                                    + toString(i) +". Unknown token " + row[0] + ".");
        }
    }
}

const std::string& GameState::getLevelFilename(unsigned int level)
{
    return mLevelsData[level - 1].filename;
}

bool GameState::isLevelBonusLevel(unsigned int level)
{
    return mLevelsData[level - 1].bonus;
}

const std::string& GameState::getLevelDesignation(unsigned int level)
{
    return mLevelsData[level - 1].designation;
}

unsigned int GameState::getNumberOfLevels()
{
    return mLevelsData.size();
}

void GameState::loadHighScore()
{
    std::string saveFilename;
#if defined (DB_WIN32)
    saveFilename = "data/dr.madness.highscore.txt";
#else
    saveFilename = std::string(getenv("HOME")) + "/.dr.madness.highscore.txt";
#endif

#if defined (DB_WIN32)    
    if (!exists(saveFilename.c_str()))
#else
    if (!file_exists(saveFilename.c_str(), FA_HIDDEN, NULL))
#endif
    {
        throw DBSH07_EXCEPTION("Unable to open " + saveFilename);
    }

    std::vector<std::string> data = tokenize(loadFile(saveFilename, true), "\n");
	
	mHighScore.clear();
	for (unsigned int row = 0; row < data.size(); row++)
    {
		std::vector<std::string> stringPair = tokenize(data[row], ",");

        if (stringPair.size() == 2)
        {
	        HighScorePair p;
	        p.name = stringPair[0];
	        p.points = fromString<int>(stringPair[1]);
	        mHighScore.push_back(p);
        }
	}

    while (mHighScore.size() > 10)
    {
        mHighScore.pop_back();
    }
}

void GameState::addHighScore(const std::string& name, int score)
{
	HighScorePair p = HighScorePair();
	p.name = name;
	p.points = score;

	mHighScore.push_back(p);
	std::sort(mHighScore.begin(), mHighScore.end(), &HighScorePair::compareScore);
    
    while (mHighScore.size() > 10)
    {
        mHighScore.pop_back();
    }
}

void GameState::saveHighScore()
{
    std::string saveFilename;
#if defined (DB_WIN32)
    saveFilename = ResourceHandler::getInstance()->getRealFilename("dr.madness.highscore.txt");
#else
    saveFilename = std::string(getenv("HOME")) + "/.dr.madness.highscore.txt";
#endif

#if defined (DB_WIN32)    
    if (!exists(saveFilename.c_str()))
#else
    if (!file_exists(saveFilename.c_str(), FA_HIDDEN, NULL))
#endif
    {
        throw DBSH07_EXCEPTION("Unable to open " + saveFilename);
    }

	std::ofstream os(saveFilename.c_str());
	if (!os.good())
	{
		throw DBSH07_EXCEPTION("Unable to open " + saveFilename);
	}

	for (int row = 0; row < mHighScore.size() && row < 10; row++)
    {
		HighScorePair p = mHighScore[row];

		os << p.name << "," << p.points << std::endl;
	}

    os.close();
}

unsigned int GameState::getMinHighScore()
{
	return mHighScore.end()->points;
}

std::vector<GameState::HighScorePair>& GameState::getHighScores()
{
    return mHighScore;
}