#include "menu.hpp"

#include "resourcehandler.hpp"
#include "guichan/allegro.hpp"
#include "gamestatemanager.hpp"

namespace nmc
{
    Menu::Menu()
        : mFrameCounter(0)
    {
        setOpaque(false);
        setSize(320, 240);
        addKeyListener(this);
        setFocusable(true);

        mBackgroundBitmap = create_bitmap(320, 240);
        int y;

        int r1 = 236;
        int g1 = 94;
        int b1 = 96;
        int r2 = 20;
        int g2 = 20;
        int b2 = 10;

        for (y = 0; y < 240; y += 16)
        {
            int r = (r1 * (240 - y) + r2 * y) / 240;
            int g = (g1 * (240 - y) + g2 * y) / 240;
            int b = (b1 * (240 - y) + b2 * y) / 240;
            
            int pixel = makecol(r, g, b);

            rectfill(mBackgroundBitmap, 0, y, 320, y + 15, pixel); 
        }

        mBackgroundImage = new gcn::AllegroImage(mBackgroundBitmap, true);
        mBackgroundIcon = new gcn::Icon(mBackgroundImage);
        add(mBackgroundIcon);

        mStartContainer = new gcn::Container();
        mStartContainer->setSize(320, 240);
        mStartContainer->setOpaque(false);
        add(mStartContainer);

        mCastleImage = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("menu-background.bmp"));
        mCastleIcon = new gcn::Icon(mCastleImage);
        mStartContainer->add(mCastleIcon);
        mPressStartLabel = new gcn::Label("Press Start");
        mPressStartLabel->adjustSize();
        mStartContainer->add(mPressStartLabel, 
                             160 - mPressStartLabel->getWidth() / 2, 
                             170);
        mLogoImage = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("menu-logo.bmp"));
        mLogoIcon = new gcn::Icon(mLogoImage);
        mStartContainer->add(mLogoIcon);

        mInfoFont = new gcn::ImageFont(ResourceHandler::getInstance()->getRealFilename("gamefont-menu-info.bmp"), 
                                       32, 
                                       126);
        mFont = new gcn::ImageFont(ResourceHandler::getInstance()->getRealFilename("gamefont2.bmp"), 
                                       32, 
                                       126);
        mFont->setGlyphSpacing(-2);

        mInfoFont->setGlyphSpacing(1);
        mInfoTextBox = new gcn::TextBox("Copyright (C) Darkbits 2007");
        mInfoTextBox->setBorderSize(0);
        mInfoTextBox->setOpaque(false);
        mInfoTextBox->setFocusable(false);
        mInfoTextBox->setEditable(false);
        mInfoTextBox->setFont(mInfoFont);
        mStartContainer->add(mInfoTextBox, 
                             160 - mInfoTextBox->getWidth() / 2, 
                             240 - mInfoTextBox->getHeight() - 10);

        mGameSelectContainer = new gcn::Container();
        mGameSelectContainer->setOpaque(false);
        mGameSelectContainer->setSize(320, 240);
        mGameSelectContainer->setVisible(false);
        add(mGameSelectContainer);

        mSelectGameLabel = new gcn::Label("SELECT GAME");
        mSelectGameLabel->setFont(mFont);
        mSelectGameLabel->adjustSize();
        mGameSelectContainer->add(mSelectGameLabel, 
                                  160 - mSelectGameLabel->getWidth() / 2,
                                  30);
        mEraseGameLabel = new gcn::Label("ERASE GAME");
        mEraseGameLabel->setFont(mFont);
        mEraseGameLabel->adjustSize();
        mEraseGameLabel->setVisible(false);
        mGameSelectContainer->add(mEraseGameLabel, 
                                  160 - mEraseGameLabel->getWidth() / 2,
                                  30);
        mGameSlotOne = new GameSlot();
        mGameSelectContainer->add(mGameSlotOne, 
                                  160 - mGameSlotOne->getWidth() / 2, 
                                  40);
        mGameSlotTwo = new GameSlot();
        mGameSelectContainer->add(mGameSlotTwo, 
                                  160 - mGameSlotTwo->getWidth() / 2, 
                                  40 + mGameSlotOne->getHeight());

        mGameSlotThree = new GameSlot();
        mGameSelectContainer->add(mGameSlotThree, 
                                  160 - mGameSlotThree->getWidth() / 2, 
                                  40 + mGameSlotOne->getHeight() * 2);
        mGameSlotOne->update(0);
        mGameSlotTwo->update(1);
        mGameSlotThree->update(2);

        mEraseLabel = new gcn::Label("ERASE GAME");
        mEraseLabel->setFont(mFont);
        mEraseLabel->adjustSize();
        mGameSelectContainer->add(mEraseLabel, 
                                  160 - mGameSlotThree->getWidth() / 2,
                                  40 + mGameSlotOne->getHeight() * 3 + 5);

        mCancelLabel = new gcn::Label("CANCEL");
        mCancelLabel->setFont(mFont);
        mCancelLabel->adjustSize();
        mCancelLabel->setVisible(false);
        mGameSelectContainer->add(mCancelLabel, 
                                  160 - mGameSlotThree->getWidth() / 2,
                                  40 + mGameSlotOne->getHeight() * 3 + 5);
        mQueryEraseLabel = new gcn::Label("ARE YOU SURE YOU WANT TO ERASE GAME?");
        mQueryEraseLabel->setFont(mFont);
        mQueryEraseLabel->adjustSize();
        mQueryEraseLabel->setVisible(false);
        mGameSelectContainer->add(mQueryEraseLabel, 
                                  160 - mGameSlotThree->getWidth() / 2,
                                  40 + mGameSlotOne->getHeight() * 3 + 5);

        mNoLabel = new gcn::Label("NO");
        mNoLabel->setFont(mFont);
        mNoLabel->adjustSize();
        mNoLabel->setVisible(false);
        mGameSelectContainer->add(mNoLabel, 
                                  160 - mGameSlotThree->getWidth() / 2,
                                  40 + mGameSlotOne->getHeight() * 3 + 5 
                                  + mQueryEraseLabel->getHeight());
        mYesLabel = new gcn::Label("YES");
        mYesLabel->setFont(mFont);
        mYesLabel->adjustSize();
        mYesLabel->setVisible(false);
        mGameSelectContainer->add(mYesLabel, 
                                  160 - mGameSlotThree->getWidth() / 2,
                                  40 + mGameSlotOne->getHeight() * 3 + 5 
                                  + mQueryEraseLabel->getHeight() + mNoLabel->getHeight());

        mMainMultiSelector = new MultiSelector();
        mMainMultiSelector->setSize(320, 240);
        mMainMultiSelector->addActionListener(this);
        mMainMultiSelector->addSelection(40, 
                                     mGameSlotOne->getY() + mGameSlotOne->getHeight() / 2 
                                     - mMainMultiSelector->getSelectorHeight() / 2);
        mMainMultiSelector->addSelection(40, 
                                     mGameSlotTwo->getY() + mGameSlotTwo->getHeight() / 2 
                                     - mMainMultiSelector->getSelectorHeight() / 2);
        mMainMultiSelector->addSelection(40, 
                                     mGameSlotThree->getY() + mGameSlotThree->getHeight() / 2 
                                     - mMainMultiSelector->getSelectorHeight() / 2);
        mMainMultiSelector->addSelection(40, 
                                     mEraseLabel->getY() + mEraseLabel->getHeight() / 2 
                                     - mMainMultiSelector->getSelectorHeight() / 2);

        mGameSelectContainer->add(mMainMultiSelector);

        mQueryMultiSelector = new MultiSelector();
        mQueryMultiSelector->setSize(320, 240);
        mQueryMultiSelector->addActionListener(this);
        mQueryMultiSelector->setVisible(false);
        mQueryMultiSelector->addSelection(40,
                                          mNoLabel->getY() + mNoLabel->getHeight() / 2
                                          - mQueryMultiSelector->getSelectorHeight() / 2);
        mQueryMultiSelector->addSelection(40,
                                          mYesLabel->getY() + mYesLabel->getHeight() / 2
                                          - mQueryMultiSelector->getSelectorHeight() / 2);
        mGameSelectContainer->add(mQueryMultiSelector);
    }

    Menu::~Menu()
    {
        delete mBackgroundIcon;
        delete mBackgroundImage;
        delete mInfoFont;
        delete mFont;
        delete mInfoTextBox;
        delete mLogoImage;
        delete mLogoIcon;
        delete mCastleImage;
        delete mCastleIcon;
        delete mPressStartLabel;
        delete mStartContainer;
        delete mGameSelectContainer;
        delete mGameSlotOne;
        delete mGameSlotTwo;
        delete mGameSlotThree;
        delete mSelectGameLabel;
        delete mEraseLabel;
        delete mCancelLabel;
        delete mMainMultiSelector;
        delete mEraseGameLabel;
        delete mQueryEraseLabel;
        delete mYesLabel;
        delete mNoLabel;
        delete mQueryMultiSelector;
    }

    void Menu::init()
    {
        mGameSelectContainer->setVisible(false);
        mEraseLabel->setVisible(true);
        mCancelLabel->setVisible(false);
        mEraseGameLabel->setVisible(false);
        mSelectGameLabel->setVisible(true);
        mMainMultiSelector->requestFocus();
        mQueryMultiSelector->setVisible(false);
        mQueryEraseLabel->setVisible(false);
        mNoLabel->setVisible(false);
        mYesLabel->setVisible(false);

        mStartContainer->setVisible(true);

        mMainMultiSelector->setSelected(0);
       
        requestFocus();
    }

    void Menu::logic()
    {
        Container::logic();

        mFrameCounter++;

        if (mFrameCounter % 60 == 0)
        {
            mPressStartLabel->setVisible(!mPressStartLabel->isVisible());
        }
    }

    void Menu::keyPressed(gcn::KeyEvent& keyEvent)
    {
        if (keyEvent.getKey().getValue() == gcn::Key::SPACE
            || keyEvent.getKey().getValue() == gcn::Key::LEFT_ALT
            || keyEvent.getKey().getValue() == gcn::Key::LEFT_CONTROL
            || keyEvent.getKey().getValue() == gcn::Key::ENTER
            && keyEvent.getSource() == this)
        {
            mGameSelectContainer->setVisible(true);
            mStartContainer->setVisible(false);
            mMainMultiSelector->requestFocus();

            //generateAction();
        }
        else if (keyEvent.getKey().getValue() == gcn::Key::ESCAPE)
        {
            init();

            //generateAction();
        }
    }

    void Menu::action(const gcn::ActionEvent& actionEvent)
    {
        if (actionEvent.getSource() == mMainMultiSelector)
        {
            if (!mCancelLabel->isVisible() 
                && mMainMultiSelector->getSelected() == 3)
            {
                // Erase selected
                mEraseLabel->setVisible(false);
                mCancelLabel->setVisible(true);
                mEraseGameLabel->setVisible(true);
                mSelectGameLabel->setVisible(false);
                mMainMultiSelector->setSelected(0);
            }
            else if (mCancelLabel->isVisible() 
                     && mMainMultiSelector->getSelected() == 3)
            {
                // Cancel selected
                mEraseLabel->setVisible(true);
                mCancelLabel->setVisible(false);
                mEraseGameLabel->setVisible(false);
                mSelectGameLabel->setVisible(true);
                mMainMultiSelector->setSelected(0);
            }
            else if (!mCancelLabel->isVisible() 
                     && mMainMultiSelector->getSelected() != 3)
            {
                GameStateManager::getInstance()->loadSlot(mMainMultiSelector->getSelected());
                generateAction();
            }
            else if (mCancelLabel->isVisible() 
                     && mMainMultiSelector->getSelected() != 3)
            {
                mCancelLabel->setVisible(false);
                mQueryEraseLabel->setVisible(true);
                mNoLabel->setVisible(true);
                mYesLabel->setVisible(true);
                mQueryMultiSelector->setVisible(true);
                mQueryMultiSelector->requestFocus();
            }
        }
        else if (actionEvent.getSource() == mQueryMultiSelector)
        {
            if (mQueryMultiSelector->getSelected() == 0)
            {  
                // No selected
                mEraseLabel->setVisible(true);
                mCancelLabel->setVisible(false);
                mEraseGameLabel->setVisible(false);
                mSelectGameLabel->setVisible(true);
                mMainMultiSelector->requestFocus();
                mQueryMultiSelector->setVisible(false);
                mQueryEraseLabel->setVisible(false);
                mNoLabel->setVisible(false);
                mYesLabel->setVisible(false);
            }
            else if (mQueryMultiSelector->getSelected() == 1)
            {
                // Yes selected, slot should be erased
                mEraseLabel->setVisible(true);
                mCancelLabel->setVisible(false);
                mEraseGameLabel->setVisible(false);
                mSelectGameLabel->setVisible(true);
                mMainMultiSelector->requestFocus();
                mQueryMultiSelector->setVisible(false);
                mQueryEraseLabel->setVisible(false);
                mNoLabel->setVisible(false);
                mYesLabel->setVisible(false);
                GameStateManager::getInstance()->erase(mMainMultiSelector->getSelected());
                mGameSlotOne->update(0);
                mGameSlotTwo->update(1);
                mGameSlotThree->update(2);
            }
        }
    }
}