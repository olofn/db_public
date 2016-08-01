#include "game.hpp"

#include <allegro.h>

#include "resourcehandler.hpp"
#include "timer.hpp"
#include "exception.hpp"
#include "music.hpp"

#include "tilemap.hpp"
#include "roomgenerator.hpp"
#include "random.hpp"
#include "gamestate.hpp"
#include "roomloader.hpp"
#include "entities/door.hpp"
#include "entities/player.hpp"
#include "fileutil.hpp"

#include <iostream>

Game::Game()
:mPauseButtonPressed(false),
mHeroicModeUnlocked(false),
mPlayer(0),
mRoom(0),
mHeroicMode(false)
{
    allegro_init();
    install_keyboard();
	
    set_window_title("db - Secret Of Fantasy - The Calcium Crystals");

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

	// Preloads the music
	playMusic("music/olof.xm");
	playMusic("music/olof2.xm");
	playMusic("music/olof3.xm");
	playMusic("music/olof4.xm");
	playMusic("music/chiptunen.xm");
	playMusic("music/emil.xm");
	playMusic("music/odyssey.xm");
	playMusic("music/gameover.xm");
	playMusic("music/xazzy.xm");
	playMusic("music/menu.xm");
	playMusic("music/splash.xm");
	ResourceHandler::getInstance()->getBitmap("gui/darkbitslogo_by_haiko.bmp"); // Preloads splash
    mGameState = new GameState();
    // IMPORTANT, has to be called last.
	setState(SPLASHSCREEN);
	rest(10);
	resetTimer();
}

Game::~Game()
{
	stopMusic();
 
    ResourceHandler::getInstance()->destroy();

	delete mGameState;
	delete mPlayer;
    delete mSplashScreen;
	destroy_bitmap(mBuffer);

    delete mGui;
    delete mAllegroGraphics;
    delete mAllegroImageLoader;
    delete mAllegroInput;
    delete mImageFont;
    delete mTop;

    delete mLogoImage;
    delete mLogoIcon;

	delete mMainMenuContainer;
	delete mGameContainer;
    delete mMainMenuListModel;
    delete mMainMenuListBox;
	delete mGameOverContainer;
	delete mGameOverLabel;
	delete mInfoLabel;
	delete mSpeedhackLabel;
}

GameState* Game::getGameState() 
{ 
	return mGameState;
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
		case CONTINUE:
		case HEROIC:
        case GAME:
            mRoom->logic();
			if (mRoom->isGameOver())
			{
				setState(GAMEOVER);
			}
			else if (mRoom->isLoadAtOverworld() && mGameState->getInt("heroicseed") != 0)
			{
				setState(GAMEOVER);
			}
			else if (mRoom->isLoadAtOverworld())
			{
				load();
			}
            break;
        case PAUSE:
            break;
        case EXIT:
            break;
		case GAMEOVER:
			break;
   	    default:
			throw DB_EXCEPTION("Unknown game state.");
   }
   
    mGui->logic();

	if (key[KEY_ESC]) 
    {
        setState(EXIT);
    }

#ifdef _DEBUG

	if (key[KEY_F10]) 
    {
        setState(EXIT);
    }

	if (key[KEY_F5]) 
    {
		changeRoom(mRoom->getDungeonName(), mRoom->getDungeonLevel(), false);
    }

    if (key[KEY_P] && !mPauseButtonPressed && mState == PAUSE)
    {
        setState(GAME);
    }
#endif

	/*
    else if (key[KEY_P] && !mPauseButtonPressed && mState == LEVEL)
    {
        setState(PAUSE);
    }*/

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
    case HEROIC:
	case CONTINUE:
	case GAME:
        clear_to_color(mBuffer, makecol(0, 0, 0));
        mRoom->draw(mBuffer);
        mAllegroGraphics->setTarget(mBuffer);
        mGui->draw();
        break;
    case PAUSE:
        break;
	case EXIT:
		break;
 	case GAMEOVER:
		 //clear_to_color(mBuffer, makecol(0, 0, 0));
		 mAllegroGraphics->setTarget(mBuffer);
		 mGui->draw();
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

	mImageFont = new gcn::ImageFont(ResourceHandler::getInstance()->getRealFilename("gui/nesfont.bmp"), "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.!?:;_()-*&$");
	mImageFont->setRowSpacing(3);
	gcn::Widget::setGlobalFont(mImageFont);

	mTop = new gcn::Container();
	mTop->setSize(320, 240);
	mTop->setOpaque(false);
	mGui->setTop(mTop);
   
    mMainMenuContainer = new gcn::Container();
	mMainMenuContainer->setSize(320, 240);
	mMainMenuContainer->setBaseColor(gcn::Color(0x000000));
	mTop->add(mMainMenuContainer);

    mGameContainer = new gcn::Container();
    mGameContainer->setSize(320, 240);
	mGameContainer->setOpaque(false);
    mGameContainer->setVisible(false);
	mTop->add(mGameContainer);

	mGameOverContainer = new gcn::Container();
	mGameOverContainer->setSize(320, 240);
	mGameOverContainer->setBaseColor(gcn::Color(0x000000));
	mGameOverContainer->setVisible(false);
	mTop->add(mGameOverContainer);

	mGameOverLabel = new gcn::Label("GAME OVER");
	mGameOverLabel->adjustSize();
	mGameOverContainer->add(mGameOverLabel, 
						160 - mGameOverLabel->getWidth() / 2,
						120 - mGameOverLabel->getHeight() / 2);

	mLogoImage = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/logo.bmp"));
	mLogoIcon = new gcn::Icon(mLogoImage);
	mMainMenuContainer->add(mLogoIcon, 0, 30);

    mMainMenuListModel = new MainMenuListModel();
    mMainMenuListBox = new DBListBox();
    mMainMenuListBox->setListModel(mMainMenuListModel);
    mMainMenuListBox->setTabOutEnabled(false);
    mMainMenuListBox->setSelected(0);
    mMainMenuContainer->add(mMainMenuListBox, 128, 167);
    mMainMenuListBox->requestFocus();
    mMainMenuListBox->addActionListener(this);

	mInfoLabel = new gcn::Label("DARKBITS (C) 1989");
	mInfoLabel->adjustSize();
	mMainMenuContainer->add(mInfoLabel,
							160 - mInfoLabel->getWidth() / 2,
							215);
	mSpeedhackLabel = new gcn::Label("SPEEDHACK 10");
	mSpeedhackLabel->adjustSize();
	mMainMenuContainer->add(mSpeedhackLabel,
							160 - mSpeedhackLabel->getWidth() / 2,
							225);
}

void Game::action(const gcn::ActionEvent& actionEvent)
{
    if (actionEvent.getSource() == mMainMenuListBox)
    {
		if (mMainMenuListModel->heroicMode && mMainMenuListModel->continuePresent)
		{
			switch(mMainMenuListBox->getSelected())
			{
			case 0:
				setState(GAME);
				break;
			case 1:
				setState(HEROIC);
				break;
			case 2:
				setState(CONTINUE);
				break;
			case 3:
				setState(EXIT);
				break;
			}
		}
		else if (mMainMenuListModel->heroicMode)
		{
			switch(mMainMenuListBox->getSelected())
			{
			case 0:
				setState(GAME);
				break;
			case 1:
				setState(HEROIC);
				break;
			case 2:
				setState(EXIT);
				break;
			}
		}
		else if (mMainMenuListModel->continuePresent)
		{
			switch(mMainMenuListBox->getSelected())
			{
			case 0:
				setState(GAME);
				break;
			case 1:
				setState(CONTINUE);
				break;
			case 2:
				setState(EXIT);
				break;
			}
		}
		else
		{
			switch(mMainMenuListBox->getSelected())
			{
			case 0:
				setState(GAME);
				break;
			case 1:
				setState(EXIT);
				break;
			}
		}
    }
}

void Game::keyPressed(gcn::KeyEvent &keyEvent)
{
    if (mState == GAMEOVER 
		&& (keyEvent.getKey().getValue() == gcn::Key::ESCAPE
			|| keyEvent.getKey().getValue() == gcn::Key::LEFT_CONTROL
			|| keyEvent.getKey().getValue() == gcn::Key::SPACE
			|| keyEvent.getKey().getValue() == gcn::Key::ENTER
			|| keyEvent.getKey().getValue() == gcn::Key::LEFT_ALT))
	{
		setState(MENU);
		keyEvent.consume();
	}
}

void Game::setState(State state)
{
    clear_keybuf();
	
	
    if (state == MENU)
    {
		if (loadFile("hero.dat", false, true) == "petersuger")
		{
			mHeroicMode = true;
			mMainMenuListModel->heroicMode = true;
		}

		if (GameState::isSavePresent() && Inventory::isSavePresent())
		{
			mMainMenuListModel->continuePresent = true;
		}
		else
		{
			mMainMenuListModel->continuePresent = false;
		}

		mMainMenuContainer->setVisible(true);
        mGameContainer->setVisible(false);
		mGameOverContainer->setVisible(false);
        mMainMenuListBox->requestFocus();
		playMusic("music/menu.xm", 1.0f);
    }
	else if (state == HEROIC)
	{
		mGameState->clear();
		mGameState->put("heroicseed",Random::get().getInt(1, 1000));  
		setState(GAME);
		return;
	}
	else if (state == CONTINUE)
	{
		if (mGameState->getInt("heroicseed") == 0)
			world.load(59);
		else
			world.load(mGameState->getInt("heroicseed"));

		if (mRoom)
			delete mRoom;
		mRoom = 0;

		if (mPlayer)
			delete mPlayer;
		mPlayer = new Player();

		load();
		changeRoom("overworld.txt", 0, false, 307, 142);

       // IMPORTANT, we have to make the level container
        // visible before initialising a level.
        mMainMenuContainer->setVisible(false);
        mGameContainer->setVisible(true);   
		mGameOverContainer->setVisible(false);
	}
    else if (state == GAME)
    {
		if (mGameState->getInt("heroicseed") == 0)
			world.load(59);
		else
			world.load(mGameState->getInt("heroicseed"));

		if (mRoom)
			delete mRoom;
		mRoom = 0;

		if (mPlayer)
			delete mPlayer;
		mPlayer = new Player();
		changeRoom("realworld.txt", 0, false, 200, 200);

        // IMPORTANT, we have to make the level container
        // visible before initialising a level.
        mMainMenuContainer->setVisible(false);
        mGameContainer->setVisible(true);   
		mGameOverContainer->setVisible(false);
    }
	else if (state == GAMEOVER)
    {
        // IMPORTANT, we have to make the level container
        // visible before initialising a level.
        mMainMenuContainer->setVisible(false);
        mGameContainer->setVisible(false); 
		mGameOverContainer->setVisible(true);
		playMusic("music/menu.xm", 1.0f);
    }
	else if (state == EXIT)
	{
		if (mRoom && mRoom->getDungeonName() == "overworld.txt")
		{
			save();
		}
        mMainMenuContainer->setVisible(false);
        mGameContainer->setVisible(false);
		mGameOverContainer->setVisible(false);
	}
    else
    {
        mMainMenuContainer->setVisible(false);
        mGameContainer->setVisible(false);
		mGameOverContainer->setVisible(false);
	}

    mState = state; 
}

void Game::changeRoom(const std::string &dungeon, int level, bool zoom, int playerX, int playerY)
{
	Room *oldRoom = mRoom;
	mRoom = world.getRoom(dungeon, level);

	mRoom->setGame(this);
	mRoom->setPlayer(mPlayer);
	mRoom->setTop(mGameContainer);

	if (oldRoom)
	{
		Door *door = mRoom->findDoor(oldRoom->getDungeonName(), oldRoom->getDungeonLevel());
		
		if (door)
		{
			mPlayer->setX(door->getX());
			mPlayer->setY(door->getY() + 16);
		}
		if (oldRoom->getDungeonName() == "tower.txt"
			&& dungeon == "overworld.txt")
		{
			mPlayer->setX(1604);
			mPlayer->setY(80);
		}
	}
	
	if (playerX >= 0)
	{
		mPlayer->setX(playerX);
		mPlayer->setY(playerY);
	}

	mPlayer->setState("walkdown");
	mPlayer->setState("pause");

	if (zoom)
	{
		mRoom->addZoomCutScene(false);
		
		if (dungeon == "realworld.txt" && level == 1)
		{
			mRoom->addTextCutScene("THE GROCERY STORE", 50);
		}

		mRoom->startCutScenes();
	}

	mPlayer->setInvincible(50);

	if (dungeon == "overworld.txt")
	{
		mGameState->put("playerpositionx", playerX); 
		mGameState->put("playerpositiony", playerY); 
		save();
	}

	if (oldRoom)
		delete oldRoom;
}

void Game::save()
{
	mGameState->put("playerhealth", mPlayer->getHealth());
	mGameState->put("playermaxhealth", mPlayer->getMaxHealth());
	mGameState->put("playercoins", mPlayer->getCoins());
	mGameState->saveToFile();
	mPlayer->getInventory()->save();
}

void Game::load()
{
	mGameState->loadFromFile();
	mPlayer->setHealth(mGameState->getInt("playerhealth"));
	mPlayer->setMaxHealth(mGameState->getInt("playermaxhealth"));
	mPlayer->setCoins(mGameState->getInt("playercoins"));
	mPlayer->getInventory()->clear();
	mPlayer->getInventory()->load();
	
	changeRoom("overworld.txt", 
			   0, 
			   false, 
			   mGameState->getInt("playerpositionx"), 
			   mGameState->getInt("playerpositiony"));
}

bool Game::unlockHeroicMode()
{
	if (!mHeroicModeUnlocked)
	{
		mHeroicModeUnlocked = true;
		storeFile("hero.dat", "petersuger");
		mMainMenuListModel->heroicMode = true;
		return true;
	}
	return false;
}
