#ifndef DBSH07_GAME_HPP
#define DBSH07_GAME_HPP

#include <allegro.h>

#include "splashscreen.hpp"
#include "ending.hpp"
#include "level.hpp"

#include "gui/dbsh07listbox.hpp"
//#include "gui/levelselector.hpp"
#include "guichan.hpp"
#include "guichan/allegro.hpp"
#include "gui/dbsh07button.hpp"
#include "gui/extendedallegroinput.hpp"
#include "gui/shop.hpp"
#include "gui/optionaldialog.hpp"
#include "gui/dialog.hpp"
#include "gui/highscorecontainer.hpp"

class Game: public gcn::ActionListener, public gcn::KeyListener
{
public:
    Game();
    ~Game();

	void logic();
	void draw();
    void run();
private:
	void initGui();
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
        SHOP,
        BONUS_LEVEL_OR_SHOP,
        END,
        HIGH_SCORE
    };

    void setState(State state);

   

    State mState;
    BITMAP* mBuffer;
    BITMAP* mScreenBuffer;
    SplashScreen* mSplashScreen;
	Ending* mEnding;
    
    Level* mLevel;

	gcn::AllegroGraphics* mAllegroGraphics;
    gcn::AllegroImageLoader* mAllegroImageLoader;
    gcn::ExtendedAllegroInput* mAllegroInput;
    gcn::ImageFont* mImageFont;
	gcn::Gui* mGui;

	gcn::Container* mTop;

    gcn::Container* mMainMenuContainer;

    gcn::Container* mCreditsContainer;
	//gcn::Container* mHighScoreContainer;

    gcn::Image* mOlofImage;
    gcn::Icon* mOlofIcon;
    gcn::Label* mOlofLabel;
    gcn::Image* mPerImage;
    gcn::Icon* mPerIcon;
    gcn::Label* mPerLabel;
    gcn::Image* mTedImage;
	gcn::Icon* mTedIcon;
    gcn::Label* mTedLabel;

	HighScoreContainer* mHighScoreContainer;

//    gcn::Container* mLevelsContainer;
//    LevelSelector* mLevelSelector;
//    BallzScrollArea* mLevelSelectorScrollArea;

//    gcn::TextBox* mInfoText;
//    gcn::ImageFont* mInfoTextFont;

    gcn::Image* mTopBackgroundImage;
    gcn::Icon* mTopBackgroundIcon;
    gcn::Image* mLogoImage;
    gcn::Icon* mLogoIcon;
    gcn::Image* mGameInfoImage;
    gcn::Icon* mGameInfoIcon;
    //gcn::Label* mCollectedStars;

    gcn::TextBox* mCreditsText;

    DBSH07Button* mStartButton;
    DBSH07Button* mCreditsButton;
	DBSH07Button* mHighScoreButton;
    DBSH07Button* mExitButton;

    bool mPauseButtonPressed;

    Shop* mShop;
    OptionalDialog* mOptionalDialog;
    Dialog* mDialog;
};

#endif