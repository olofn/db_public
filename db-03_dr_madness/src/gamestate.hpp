#ifndef DBSH07_GAMESTATE_HPP
#define DBSH07_GAMESTATE_HPP

#include <map>
#include <vector>

class GameState
{
public:
    class HighScorePair
	{
    public:
		//HighScorePair(const std::string& name, int points) : name(name), points(points); }
		std::string name;
		unsigned int points;
		static bool compareScore(const HighScorePair& a, const HighScorePair& b) { return a.points > b.points; };
		//HighScorePair operator-(const HighScorePair& a) { return HighScorePair(); };
	};

    static GameState* getInstance();
    unsigned int getLives();
    void setLives(unsigned int lives);
    unsigned int getLevel();
    void setLevel(unsigned int level);
    void setEnergyOrbs(unsigned int energyOrbs);
    unsigned int getEnergyOrbs();
    void setPods(unsigned int pods);
    unsigned int getPods();
	unsigned int getPoints() {return mPoints; };
	void setPoints(unsigned int points) {mPoints = points; };
	void addPoints(unsigned int points) {mPoints += points; };
	void setCannonLevel(unsigned int cannonLevel);
	unsigned int getCannonLevel();
    void setMegaBlasts(unsigned int megaBlasts);
    unsigned int getMegaBlasts();

    const std::string& getLevelFilename(unsigned int level);
    bool isLevelBonusLevel(unsigned int level);
    const std::string& getLevelDesignation(unsigned int level);
    unsigned int getNumberOfLevels();
    void reset();
	void addHighScore(const std::string& name, int score);
	unsigned int getMinHighScore();
	void saveHighScore();
    std::vector<HighScorePair>& getHighScores();

private:
    GameState();
    void loadLevelsData();
    void loadHighScore();

    static GameState* mInstance;
    unsigned int mLives;
    unsigned int mLevel;
    unsigned int mEnergyOrbs;
    unsigned int mPods;

	unsigned int mPoints;
	
	unsigned int mCannonLevel;
    unsigned int mMegaBlasts;

    class LevelData
    {
    public:
        LevelData(const std::string& filename_, 
                  bool bonus_, 
                  const std::string& designation_)
                  :filename(filename_),
                  bonus(bonus_),
                  designation(designation_)
        {}
        std::string filename;
        bool bonus;
        std::string designation;
    };
    std::vector<LevelData> mLevelsData;
    std::vector<HighScorePair> mHighScore;
};
#endif