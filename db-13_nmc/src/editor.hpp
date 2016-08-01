#ifndef NMC_EDITOR_HPP
#define NMC_EDITOR_HPP

#include <allegro.h>

#include "guichan.hpp"
#include "guichan/allegro.hpp"
#include "gui/entityselector.hpp"
#include "gui/imagecheckbox.hpp"
#include "gui/imagebutton.hpp"
#include "gui/inttextfield.hpp"
#include "gui/roomselector.hpp"
#include "gui/tileeditor.hpp"
#include "gui/tiletoolbox.hpp"
#include "gui/worldeditor.hpp"
#include "gui/worldpiece.hpp"

namespace nmc
{
    class Editor : public gcn::ActionListener
    {
    public:
        enum State
        {
            ROOM,
            WORLD
        };
        Editor();
        ~Editor();
        void setState(State state);
        void logic();
        void save();
        void draw(BITMAP* dest);
        void setRoomNumber(int roomNumber);
        int getRoomNumber();
        void action(const gcn::ActionEvent& actionEvent);

    protected:
        gcn::Gui* mGui;
        gcn::AllegroGraphics* mAllegroGraphics;
        gcn::AllegroImageLoader* mAllegroImageLoader;
        gcn::AllegroInput* mAllegroInput;
        gcn::ImageFont* mFixedFont;

        gcn::Container* mTop;
        
        ImageButton* mNewButton;
        ImageButton* mOpenButton;
        ImageButton* mSaveRoomButton;
        ImageButton* mSaveWorldButton;
        ImageCheckBox* mRoomCheckBox;
        ImageCheckBox* mWorldCheckBox;
        ImageCheckBox* mSolidityCheckBox;
        ImageCheckBox* mBackgroundLayerCheckBox;
        ImageCheckBox* mForegroundLayerCheckBox;
        ImageCheckBox* mEntityCheckBox;
        ImageCheckBox* mEntityLayerCheckBox;
        ImageCheckBox* mTileCheckBox;
        ImageCheckBox* mNormalModeCheckBox;
        ImageCheckBox* mFillModeCheckBox;

        gcn::Container* mToolBarContainer;
        gcn::Container* mRoomToolBarContainer;
        gcn::Container* mWorldToolBarContainer;

        gcn::Window* mSaveRoomDialogWindow;
        gcn::TextBox* mSaveRoomDialogTextBox;
        gcn::Button* mSaveRoomDialogOKButton;
        gcn::Button* mSaveRoomDialogCancelButton;

        gcn::Window* mSaveWorldDialogWindow;
        gcn::TextBox* mSaveWorldDialogTextBox;
        gcn::Button* mSaveWorldDialogOKButton;
        gcn::Button* mSaveWorldDialogCancelButton;

        gcn::Window* mNewRoomDialogWindow;
        gcn::Label* mNewRoomDialogWidthLabel;
        gcn::Label* mNewRoomDialogHeightLabel;
        gcn::Label* mNewRoomDialogNameLabel;
        IntTextField* mNewRoomDialogWidthTextField;
        IntTextField* mNewRoomDialogHeightTextField;
        gcn::TextField* mNewRoomDialogNameTextField;
        gcn::Button* mNewRoomDialogOKButton;
        gcn::Button* mNewRoomDialogCancelButton;

        TileEditor* mTileEditor;
        gcn::ScrollArea* mTileEditorScrollArea;

        gcn::Window* mTileToolBoxWindow;
        TileToolBox* mTileToolBox;

        gcn::Window* mRoomSelectorWindow;
        gcn::ScrollArea* mRoomSelectorScrollArea;
        RoomSelector* mRoomSelector;

        gcn::Window* mEntitySelectorWindow;
        gcn::ScrollArea* mEntitySelectorScrollArea;
        EntitySelector* mEntitySelector;

        WorldEditor* mWorldEditor;
        gcn::ScrollArea* mWorldEditorScrollArea;

        int mRoomNumber;
    };
}

#endif