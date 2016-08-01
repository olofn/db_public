#ifndef NMC_GAME_HPP
#define NMC_GAME_HPP

#include <allegro.h>

#include "editor.hpp"
#include "guichan.hpp"
#include "room.hpp"
#include "splashscreen.hpp"
#include "crackintro.hpp"
#include "gui/menu.hpp"

namespace nmc
{
    class Game: public gcn::ActionListener, public gcn::KeyListener
    {
    public:
        Game();
        ~Game();

		void logic();
		void draw();
        void run();
        void action(const gcn::ActionEvent& actionEvent);
        void keyPressed(gcn::KeyEvent& keyEvent);

    protected:

        enum State
        {
            MENU,
            GAME,
            EDIT,
            EXIT,
            SPLASHSCREEN,
			CRACKINTRO
        };

        State mState;
        Room* mRoom;
        BITMAP* mBuffer;
        BITMAP* mScreenBuffer;
        Editor* mEditor;
        gcn::Gui* mGui;
        Menu* mMenu;
        gcn::AllegroGraphics* mAllegroGraphics;
        gcn::AllegroInput* mAllegroInput;
        gcn::AllegroImageLoader* mAllegroImageLoader;
        gcn::Container* mTop;
        SplashScreen* mSplashScreen;
		CrackIntro* mCrackIntro;
    };
}
#endif