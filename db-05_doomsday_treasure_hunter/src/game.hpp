#ifndef DB_GAME_HPP
#define DB_GAME_HPP

#include <allegro.h>

#include "map.hpp"
#include "level.hpp"
#include "splashscreen.hpp"

#include "guichan.hpp"
#include "guichan/allegro.hpp"
#include "gui/dblistbox.hpp"

class Game: public gcn::ActionListener, public gcn::KeyListener
{
public:
    Game();
    ~Game();
    void run();

private:
	void initGui();
    void logic();
	void draw();

protected:

	void action(const gcn::ActionEvent& actionEvent);
	void keyPressed(gcn::KeyEvent &keyEvent);
    void prepareNextLevel();
    void startNextLevel();

    enum State
    {
        SPLASHSCREEN,
		MENU,
		EXIT,
        LEVEL,
        PAUSE,
        MAP
    };

    void setState(State state);

    Level* mLevel;
    Map* mMap;

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
    gcn::Container* mCreditsContainer;
    gcn::Container* mLevelContainer;
    gcn::Container* mMapContainer;

    gcn::Image* mOlofImage;
    gcn::Icon* mOlofIcon;
    gcn::Label* mOlofLabel;

    gcn::Image* mTopBackgroundImage;
    gcn::Icon* mTopBackgroundIcon;
    gcn::Image* mLogoImage;
    gcn::Icon* mLogoIcon;
    gcn::Image* mGameInfoImage;
    gcn::Icon* mGameInfoIcon;

    gcn::TextBox* mCreditsText;
    DBListBox* mMainMenuListBox;

    bool mPauseButtonPressed;
    bool mShouldFade;
    std::string mNextLevel;

    class MainMenuListModel: public gcn::ListModel
    {
    public:
        int getNumberOfElements()
        {
            return 3;
        }

        std::string getElementAt(int i)
        {
            switch(i)
            {
            case 0:
                return std::string("PLAY");
            case 1:
                return std::string("CREDITS");
            case 2:
                return std::string("QUIT");
            default: // Just to keep warnings away
              return std::string("");
            }
        }
    };

    MainMenuListModel* mMainMenuListModel;

};

#endif
