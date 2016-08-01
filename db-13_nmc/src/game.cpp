#include "game.hpp"

#include <allegro.h>

#include "exception.hpp"
#include "gamestatemanager.hpp"
#include "resourcehandler.hpp"
#include "timer.hpp"
#include "world.hpp"

#include <iostream>

namespace nmc
{
    Game::Game()
    {
        allegro_init();
	    install_keyboard();
        install_mouse();
    	
	    set_window_title("Darkbits - Nodajo's Mechanical Castle");

	    int driver = GFX_AUTODETECT_WINDOWED;
	    set_color_depth(16);
	    if (set_gfx_mode(driver, 640, 480, 0, 0) < 0) {
		    set_color_depth(24);
		    if (set_gfx_mode(driver, 640, 480, 0, 0) < 0) {
			    set_color_depth(16);
			    if (set_gfx_mode(driver, 640, 480, 0, 0) < 0) {
				    set_color_depth(15);
				    if (set_gfx_mode(driver, 640, 480, 0, 0) < 0) 
                    {
					    throw NMC_EXCEPTION("Unable to set graphics mode.");
				    }
			    }
		    }
	    }

	    initTimer();
	    mState = MENU;

        mScreenBuffer = create_bitmap(640, 480);
		mBuffer = create_bitmap(320, 240);

        mEditor = new Editor();

        mGui = new gcn::Gui();
        mAllegroGraphics = new gcn::AllegroGraphics();
        mGui->setGraphics(mAllegroGraphics);
        mAllegroInput = new gcn::AllegroInput();
        mGui->setInput(mAllegroInput);
        mAllegroImageLoader = new gcn::AllegroImageLoader();
        gcn::Image::setImageLoader(mAllegroImageLoader);
        mGui->addGlobalKeyListener(this);
        mTop = new gcn::Container();
        mTop->setSize(320, 240);
        mTop->setOpaque(false);
        mGui->setTop(mTop);
        mMenu = new Menu();
        mMenu->addActionListener(this);
        mTop->add(mMenu);
        mMenu->init();

        mRoom = new Room(mGui);
        mSplashScreen = new SplashScreen();

		if (mState == CRACKINTRO)
		{
			mCrackIntro = new CrackIntro();
		}
    }

    Game::~Game()
    {
        ResourceHandler::getInstance()->destroy();
    
        delete mSplashScreen;
        delete mEditor;
        delete mRoom;
        delete mMenu;
        delete mTop;
        delete mAllegroImageLoader;
        delete mAllegroInput;
        delete mAllegroGraphics;
        delete mGui;
    }

	void Game::logic()
	{
        switch (mState) 
        {
			case CRACKINTRO:
                mCrackIntro->logic();

                if (mCrackIntro->isDrawingDone())
                {
					delete mCrackIntro;
                    mState = SPLASHSCREEN;
                }
                break;

            case SPLASHSCREEN:
                mSplashScreen->logic();

                if (mSplashScreen->isDrawingDone())
                {
					clear_keybuf();
                    mState = MENU;
                }
                break;

            case GAME:
                mGui->logic();
				mRoom->logic();
                break;
            case MENU:
                mGui->logic();
                mMenu->logic();
               break;
            case EDIT:
                mEditor->logic();
                break;
            case EXIT:
                break;
       	    default:
                throw NMC_EXCEPTION("Unknown game state.");
	   }
       
        if (key[KEY_Q]) 
        {
	        mState = EXIT;
	    }
        else if (key[KEY_F1] && mState == EDIT)
        {
            mState = GAME;
            mEditor->save();
            mRoom->load(mEditor->getRoomNumber());
        }
        else if (key[KEY_F2] && mState != EDIT)
        {
            mState = EDIT;
            mEditor->setState(Editor::ROOM);
            mEditor->setRoomNumber(GameStateManager::getInstance()->getCurrent()->getInt("roomNumber"));
        }
	}

	void Game::draw()
	{
         // TODO Remove the clear line. 

        clear_to_color(mBuffer, makecol(120, 160, 160));

        switch (mState) 
        {
        case CRACKINTRO:
            mCrackIntro->draw(mScreenBuffer);
            break;
        case SPLASHSCREEN:
            mSplashScreen->draw(mBuffer);
            stretch_blit(mBuffer, mScreenBuffer, 0, 0, 320, 240, 0, 0, 640, 480);
            break;
		case GAME:
			acquire_bitmap(mBuffer);
			mRoom->draw(mBuffer);
			release_bitmap(mBuffer);
            mAllegroGraphics->setTarget(mBuffer);
            mGui->draw();
			stretch_blit(mBuffer, mScreenBuffer, 0, 0, 320, 240, 0, 0, 640, 480);
			break;
		case MENU:
            mAllegroGraphics->setTarget(mBuffer);
            mGui->draw();
			stretch_blit(mBuffer, mScreenBuffer, 0, 0, 320, 240, 0, 0, 640, 480);
			break;
		case EDIT:
			mEditor->draw(mScreenBuffer);
			draw_sprite(mScreenBuffer, mouse_sprite, mouse_x, mouse_y);
			break;
		case EXIT:
			break;
		default:
			throw NMC_EXCEPTION("Unknown game state.");
	   }
	}

    void Game::run()
    {
      
		long frame = getTick();
		int graphicframes = 0;
		int second = getTick() / TICKS_PER_SECOND;
		
		if (World::getInstance()->getRoomNumberList().empty())
		{
			mState = EDIT;
			//mEditor->set
		}

		while (mState != EXIT) 
        {
			logic();
           
			/*
			if (fadeRequested) {
				fadeOut(buffer, rand() % MAX_FADE_TYPE);
				frame = getTick();
				clear_keybuf();
				fadeRequested = false;
			}*/

			if (getTick() - frame > 20)
            {
				frame = getTick();
				std::cout << "Logic frame drop! =(" << std::endl;
			}

			frame++;

			if (frame > getTick())
			{
				draw();
                blit(mScreenBuffer, screen, 0, 0, 0, 0, 640, 480); 

				graphicframes++;
			}

			while (frame > getTick()) 
            {
				rest(1);
			}

			if (second != getTick() / TICKS_PER_SECOND) 
            {			
				std::cout << "FPS: " << graphicframes << std::endl;
				second = getTick() / TICKS_PER_SECOND;
				graphicframes = 0;
			}
		}

		destroy_bitmap(mBuffer);
        destroy_bitmap(mScreenBuffer);
    }

    void Game::action(const gcn::ActionEvent& actionEvent)
    {
        if (actionEvent.getSource() == mMenu)
        {
            mMenu->setVisible(false);
            mMenu->setEnabled(false);
            mRoom->load(GameStateManager::getInstance()->getCurrent()->getInt("roomNumber"));
            mState = GAME;
        }
    }

    void Game::keyPressed(gcn::KeyEvent& keyEvent)
    {
        if (keyEvent.getKey().getValue() == gcn::Key::ESCAPE)
        {

        }
    }
}