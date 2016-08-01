#ifndef DB_MAP_HPP
#define DB_MAP_HPP

#include <string>
#include <vector>
#include <allegro.h>
#include "animation.hpp"
#include "keystate.hpp"

#include "guichan.hpp"

class Map
{
public:
    Map(gcn::Container* top, const std::string& filename);
    ~Map();
    void init();
    void draw(BITMAP* dest);
    void logic();
    bool isLevelSelected();
    std::string getLevelFilename();
    void setStarsCollected(const std::string& filename, int stars);
    int getTotalStarsCollected();
protected:
    void loadSave();
    void writeSave();
    bool isSolidRight();
    bool isSolidLeft();
    bool isSolidUp();
    bool isSolidDown();
    bool isLevel();
    int getLevelStarsToUnlock();
    std::string getLevelName();
    int getLevelStars();
    int getLevelStarsCollected();
    void load(const std::string& filename);
    int getStarsInLevel(const std::string& filename);
    int getStarsToUnlockInLevel(const std::string& filename);
    std::string getNameInLevel(const std::string& filename);
    class Location
    {
    public:
        Location()
        {
            solid = false;
            road = false;
            level = false;
            stars = 0;
            starsCollected = 0;
            starsToUnlock = 0;
        }

        bool solid;
        bool road;
        int roadType;
        int x;
        int y;
        bool level;
        char levelcharacter;
        int stars;
        int starsCollected;
        int starsToUnlock;
        std::string levelfilename;
        std::string levelName;
    };

    int mPlayerX;
    int mPlayerY;
    std::vector<Location*> mLocations;
    Animation mMapAnimation;
    Animation mPlayerAnimation;
    KeyState mKeyState;
    bool mLevelSelected;
    int mTotalStarsCollected;
    int mTotalStars;
    int mFrameCounter;

    gcn::Container* mTop;
    gcn::Label* mMapLabel;
    gcn::Label* mTotalStarsCollectedLabel;
    gcn::Label* mLevelInfo;
    SAMPLE* mMoveSample;
    BITMAP* mBackground;

    class Particle
    {
    public:
        Particle(float x_, float y_, float z_)
            :x(x_), y(y_),z(z_)
        {
            
        }

        float x;
        float y;
        float z;
    };

    std::vector<Particle*> mParticles;
};
#endif

