#ifndef NMC_MENU_HPP
#define NMC_MENU_HPP

#include "guichan.hpp"

#include <allegro.h>
#include "gui/gameslot.hpp"
#include "gui/multiselector.hpp"

namespace nmc
{
    class Menu: public gcn::Container, 
                public gcn::KeyListener,
                public gcn::ActionListener
    {
    public:
        Menu();
        ~Menu();
        void logic();
        void create();
        void keyPressed(gcn::KeyEvent& keyEvent);
        void action(const gcn::ActionEvent& actionEvent);
        void init();

    protected:
        gcn::Icon* mCastleIcon;
        gcn::Image* mCastleImage;
        gcn::Icon* mLogoIcon;
        gcn::Image* mLogoImage;
        gcn::Label* mPressStartLabel;
        gcn::TextBox* mInfoTextBox;
        int mFrameCounter;
        gcn::ImageFont* mInfoFont;
        gcn::ImageFont* mFont;
        BITMAP* mBackgroundBitmap;
        gcn::Image* mBackgroundImage;
        gcn::Icon* mBackgroundIcon;
        gcn::Container* mGameSelectContainer;
        gcn::Container* mStartContainer;

        gcn::Label* mSelectGameLabel;
        gcn::Label* mEraseGameLabel;
        GameSlot* mGameSlotOne;
        GameSlot* mGameSlotTwo;
        GameSlot* mGameSlotThree;

        gcn::Label* mEraseLabel;
        gcn::Label* mCancelLabel;
        MultiSelector* mMainMultiSelector;
        MultiSelector* mQueryMultiSelector;
        gcn::Label* mQueryEraseLabel;
        gcn::Label* mNoLabel;
        gcn::Label* mYesLabel;
    };
}
#endif