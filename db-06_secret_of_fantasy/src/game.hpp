#ifndef DB_GAME_HPP
#define DB_GAME_HPP

#include <allegro.h>

#include "splashscreen.hpp"

#include "guichan.hpp"
#include "guichan/allegro.hpp"
#include "gui/dblistbox.hpp"
#include "room.hpp"
#include "world.hpp"
#include "gamestate.hpp"

class Game: public gcn::ActionListener, public gcn::KeyListener
{
public:
    Game();
    ~Game();
    void run();
	GameState* getGameState();
	void changeRoom(const std::string &dungeon, int level, bool zoom, int playerX = -1, int playerY = -1);
	void save();
	void load();
	bool unlockHeroicMode();

	bool isHeroicMode() { return mHeroicMode; }

private:
	void initGui();
    void logic();
	void draw();


protected:
	void action(const gcn::ActionEvent& actionEvent);
	void keyPressed(gcn::KeyEvent &keyEvent);
    
    enum State
    {
        SPLASHSCREEN,
		MENU,
		EXIT,
        GAME,
        PAUSE,
		GAMEOVER,
		CONTINUE,
		HEROIC
    };

    void setState(State state);

    State mState;
    BITMAP* mBuffer;
    BITMAP* mScreenBuffer;
    SplashScreen* mSplashScreen;

	gcn::AllegroGraphics* mAllegroGraphics;
    gcn::AllegroImageLoader* mAllegroImageLoader;
    gcn::AllegroInput* mAllegroInput;
    gcn::ImageFont* mImageFont;
	gcn::Gui* mGui;

	gcn::Container* mTop;
    gcn::Container* mMainMenuContainer;
    gcn::Container* mGameContainer;
	gcn::Container* mGameOverContainer;
	gcn::Label* mGameOverLabel;
    gcn::Image* mLogoImage;
    gcn::Icon* mLogoIcon;
	gcn::Label* mInfoLabel;
	gcn::Label* mSpeedhackLabel;

    DBListBox* mMainMenuListBox;

    bool mPauseButtonPressed;

    class MainMenuListModel: public gcn::ListModel
    {
    public:
		MainMenuListModel() { heroicMode = false; continuePresent = false; }
		bool heroicMode;
		bool continuePresent;
        int getNumberOfElements()
        {
			if (heroicMode && continuePresent)
				return 4;
			if (heroicMode || continuePresent)
				return 3;
            return 2;
        }

        std::string getElementAt(int i)
        {
			if (heroicMode && continuePresent)
			{
				switch(i)
				{
				case 0:
					return std::string("START");
				case 1:
					return std::string("HEROIC");
				case 2:
					return std::string("CONTINUE");
				case 3:
					return std::string("EXIT");
				default: // Just to keep warnings away
				  return std::string("");
				}
			}
			else if (continuePresent)
			{
				switch(i)
				{
				case 0:
					return std::string("START");
				case 1:
					return std::string("CONTINUE");
				case 2:
					return std::string("EXIT");
				default: // Just to keep warnings away
				  return std::string("");
				}
			}
			else if (heroicMode)
			{
				switch(i)
				{
				case 0:
					return std::string("START");
				case 1:
					return std::string("HEROIC");
				case 2:
					return std::string("EXIT");
				default: // Just to keep warnings away
				  return std::string("");
				}
			}
			else
			{
				switch(i)
				{
				case 0:
					return std::string("START");
				case 1:
					return std::string("EXIT");
				default: // Just to keep warnings away
				  return std::string("");
				}
			}
        }
    };

	bool mHeroicMode;
	bool mHeroicModeUnlocked;

    MainMenuListModel* mMainMenuListModel;
	Player* mPlayer;
	Room* mRoom;
	GameState* mGameState;

	World world;
};

#endif