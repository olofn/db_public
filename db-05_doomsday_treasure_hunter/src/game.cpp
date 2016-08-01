#include "game.hpp"

#include <allegro.h>

#include "resourcehandler.hpp"
#include "timer.hpp"
#include "exception.hpp"
#include "music.hpp"
#include "fading.hpp"

#include <iostream>

Game::Game()
:mPauseButtonPressed(false)
{
    mShouldFade = false;

    allegro_init();
    install_keyboard();
	
    set_window_title("Doomsday Treasure Hunter");

    //int driver = GFX_AUTODETECT_WINDOWED;
    int driver = GFX_AUTODETECT_FULLSCREEN;

    set_color_depth(32);
    if (set_gfx_mode(driver, 640, 480, 0, 0) < 0) {
	    set_color_depth(24);
	    if (set_gfx_mode(driver, 640, 480, 0, 0) < 0) {
		    set_color_depth(16);
		    if (set_gfx_mode(driver, 640, 480, 0, 0) < 0) {
			    set_color_depth(15);
			    if (set_gfx_mode(driver, 640, 480, 0, 0) < 0) 
                {
					throw DB_EXCEPTION("Unable to set graphics mode.");
			    }
		    }
	    }
    }

	install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);

    initTimer();

    mScreenBuffer = create_bitmap(640, 480);
	mBuffer = create_bitmap(320, 240);

    mSplashScreen = new SplashScreen();
	initGui();
	initMusic();

    

    mLevel = NULL;
    mMap = new Map(mMapContainer, "map.txt");


    // IMPORTANT, has to be called last.
    setState(SPLASHSCREEN);
}

Game::~Game()
{
	stopMusic();
 
    ResourceHandler::getInstance()->destroy();

    delete mSplashScreen;
	destroy_bitmap(mBuffer);

    delete mGui;
    delete mAllegroGraphics;
    delete mAllegroImageLoader;
    delete mAllegroInput;
    delete mImageFont;
    delete mTop;

    delete mGameInfoImage;
    delete mGameInfoIcon;
    delete mLogoImage;
    delete mLogoIcon;

    delete mOlofImage;
    delete mOlofIcon;

    delete mMainMenuListModel;
    delete mMainMenuListBox;

    delete mMap;
}

void Game::logic()
{
	pollMusic();

    switch (mState) 
    {
        case SPLASHSCREEN:
            mSplashScreen->logic();
            if (mSplashScreen->isDrawingDone())
            {
				clear_keybuf();
                setState(MENU);
            }
            break;
        case MENU:
			break;
        case MAP:
            mMap->logic();

            if (mMap->isLevelSelected())
            {
                mNextLevel = mMap->getLevelFilename();
                setState(LEVEL);
            }

            break;
        case LEVEL:
            mLevel->logic();
          
            if (mLevel->isGameOver())
            {
                mShouldFade = true;
                setState(MAP);
            }
            else if (mLevel->isGoalReached())
            {
                mShouldFade = true;
                mMap->setStarsCollected(mNextLevel, mLevel->getCollectedStars());
                setState(MAP);
            }
			
            break;
        case PAUSE:
            break;
        case EXIT:
            break;
   	    default:
			throw DB_EXCEPTION("Unknown game state.");
   }
   
    mGui->logic();

    if (key[KEY_F10]) 
    {
        setState(EXIT);
    }

    if (key[KEY_P] && !mPauseButtonPressed && mState == PAUSE)
    {
        setState(LEVEL);
    }
    else if (key[KEY_P] && !mPauseButtonPressed && mState == LEVEL)
    {
        setState(PAUSE);
    }

    mPauseButtonPressed = key[KEY_P] != 0;
}

void Game::draw()
{
	acquire_bitmap(mBuffer);

    switch (mState) 
    {
    case SPLASHSCREEN:
        mSplashScreen->draw(mBuffer);
        break;
	case MENU:
        mAllegroGraphics->setTarget(mBuffer);
        mGui->draw();
		break;
    case MAP:
        clear_to_color(mBuffer, makecol(0, 0, 0));
        mMap->draw(mBuffer);
        mAllegroGraphics->setTarget(mBuffer);
        mGui->draw();
        break;
    case LEVEL:
        clear_to_color(mBuffer, makecol(0, 0, 0));
        mLevel->draw(mBuffer);
        mAllegroGraphics->setTarget(mBuffer);
        mGui->draw();
        // Draw level
        break;
    case PAUSE:
        break;
	case EXIT:
		break;
	default:
		throw DB_EXCEPTION("Unknown game state.");
   }
	release_bitmap(mBuffer);
}

void Game::run()
{
	long frame = getTick();
	int graphicframes = 0;
	int second = getTick() / TICKS_PER_SECOND;
	
	while (mState != EXIT) 
    {
		logic();

        if (mShouldFade) 
        {
			fadeOut(mBuffer, rand() % MAX_FADE_TYPE);
			frame = getTick();
			clear_keybuf();
			mShouldFade = false;
		}

		if (getTick() - frame > 20)
        {
			frame = getTick();
			std::cout << "Logic frame drop! =(" << std::endl;
		}

		frame++;

		if (frame > getTick())
		{
			draw();
			stretch_blit(mBuffer, screen, 0, 0, 320, 240, 0, 0, 640, 480);

			graphicframes++;
		}

		while (frame > getTick()) 
        {
			rest(1);
		}

		if (second != getTick() / TICKS_PER_SECOND) 
        {			
			std::cout << "FPS: " << graphicframes << std::endl;
			std::cout << "State: " << mState << std::endl;

			second = getTick() / TICKS_PER_SECOND;
			graphicframes = 0;
		}
	}
}

void Game::initGui()
{
	mGui = new gcn::Gui();
	mGui->addGlobalKeyListener(this);
	mAllegroGraphics = new gcn::AllegroGraphics();
	mAllegroImageLoader = new gcn::AllegroImageLoader();
	mAllegroInput = new gcn::AllegroInput();

	mGui->setGraphics(mAllegroGraphics);
	mGui->setInput(mAllegroInput);
	gcn::Image::setImageLoader(mAllegroImageLoader);

	mImageFont = new gcn::ImageFont(ResourceHandler::getInstance()->getRealFilename("font.bmp"), 32, 131);
	mImageFont->setGlyphSpacing(-1);
	gcn::Widget::setGlobalFont(mImageFont);

	mTop = new gcn::Container();
	mTop->setSize(320, 240);
	mTop->setOpaque(false);
	mGui->setTop(mTop);

	mTopBackgroundImage = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("menubackground.bmp"));
	mTopBackgroundIcon = new gcn::Icon(mTopBackgroundImage);
	mTop->add(mTopBackgroundIcon);
   
    mMainMenuContainer = new gcn::Container();
	mMainMenuContainer->setSize(320, 240);
	mMainMenuContainer->setOpaque(false);
	mTop->add(mMainMenuContainer);

    mLevelContainer = new gcn::Container();
    mLevelContainer->setSize(320, 240);
	mLevelContainer->setOpaque(false);
    mLevelContainer->setVisible(false);
	mTop->add(mLevelContainer);

    mMapContainer = new gcn::Container();
    mMapContainer->setSize(320, 240);
	mMapContainer->setOpaque(false);
    mMapContainer->setVisible(false);
	mTop->add(mMapContainer);

	mLogoImage = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("logo.bmp"));
	mLogoIcon = new gcn::Icon(mLogoImage);
	mMainMenuContainer->add(mLogoIcon, 0, 30);

    mGameInfoImage = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gameinfo.bmp"));
    mGameInfoIcon = new gcn::Icon(mGameInfoImage);
    mMainMenuContainer->add(mGameInfoIcon, 
                            160 - mGameInfoIcon->getWidth() / 2, 
                            240 - mGameInfoIcon->getHeight() - 2);

	mCreditsContainer = new gcn::Container();
	mCreditsContainer->setSize(320, 240);
	mCreditsContainer->setOpaque(false);
	mCreditsContainer->setVisible(false);
	mTop->add(mCreditsContainer);

	mOlofImage = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("olof.bmp"));
	mOlofIcon = new gcn::Icon(mOlofImage);
    mCreditsContainer->add(mOlofIcon, 160 - mOlofIcon->getWidth() / 2, 85);
	mOlofLabel = new gcn::Label("OLOF NAESSEN");
	mCreditsContainer->add(mOlofLabel, 160 - mOlofLabel->getWidth() / 2, 155);

	mCreditsText = new gcn::TextBox("I was alone this year. But I managed\n"
                                    "to complete a game, so that's nice.\n"
                                    "Thanks Tomas for helping out with a\n"
                                    "couple of levels.  And thanks Per for\n"
                                    "the awesome music!\n"
                                    "I need a shower now...");
	mCreditsText->setOpaque(false);
	mCreditsText->setFrameSize(0);
	mCreditsContainer->add(mCreditsText, 160 - mCreditsText->getWidth() / 2, 170);

    mMainMenuListModel = new MainMenuListModel();
    mMainMenuListBox = new DBListBox();
    mMainMenuListBox->setListModel(mMainMenuListModel);
    mMainMenuListBox->setTabOutEnabled(false);
    mMainMenuListBox->setSelected(0);
    mMainMenuContainer->add(mMainMenuListBox, 125, 150);
    mMainMenuListBox->requestFocus();
    mMainMenuListBox->addActionListener(this);
}

void Game::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getSource() == mMainMenuListBox)
    {
        if (mMainMenuListBox->getSelected() == 0)
        {
            setState(MAP);
        }

        if (mMainMenuListBox->getSelected() == 1)
        {
            mMainMenuContainer->setVisible(false);
            mCreditsContainer->setVisible(true);
            mTopBackgroundIcon->setVisible(true);
        }

        if (mMainMenuListBox->getSelected() == 2)
        {
            setState(EXIT);
        }
    }
}

void Game::keyPressed(gcn::KeyEvent &keyEvent)
{
    if (keyEvent.getKey().getValue() == gcn::Key::Escape)
    {
        if (mCreditsContainer->isVisible())
        {
            mCreditsContainer->setVisible(false);
            mMainMenuContainer->setVisible(true);
            mMainMenuListBox->requestFocus();
        }
        else if (mState == MAP)
        {
           setState(MENU);
        }
        else if (mState == LEVEL)
        {

        }
        else
        {
            setState(EXIT);
        }
    }
}

void Game::setState(State state)
{
    clear_keybuf();
	
    if (state == MENU)
    {
        mMapContainer->setVisible(false);
        mMainMenuContainer->setVisible(true);
        mCreditsContainer->setVisible(false);
        mTopBackgroundIcon->setVisible(true);
        mLevelContainer->setVisible(false);
		playMusic("tuff.xm", 1.0f);
        mMainMenuListBox->requestFocus();
    }
    else if (state == LEVEL)
    {
        // IMPORTANT, we have to make the level container
        // visible before initialising a level.
        mTopBackgroundIcon->setVisible(false);
        mMainMenuContainer->setVisible(false);
        mCreditsContainer->setVisible(false);
        mMapContainer->setVisible(false);
        mLevelContainer->setVisible(true);

        if (mLevel != NULL)
            delete mLevel;
        mLevel = new Level(mLevelContainer, mNextLevel, mMap->getTotalStarsCollected());       
    }
    else if (state == MAP)
    {
        mMapContainer->setVisible(true);
        mTopBackgroundIcon->setVisible(false);
        mMainMenuContainer->setVisible(false);
        mCreditsContainer->setVisible(false);
        mLevelContainer->setVisible(false);
        mMap->init();
        playMusic("map.xm", 0.7f);
    }
    else
    {
        mTopBackgroundIcon->setVisible(false);
        mMainMenuContainer->setVisible(false);
        mCreditsContainer->setVisible(false);
        mLevelContainer->setVisible(false);
        mMapContainer->setVisible(false);
    }

    mState = state; 
}

void Game::prepareNextLevel()
{
  
}

void Game::startNextLevel()
{
  
}


