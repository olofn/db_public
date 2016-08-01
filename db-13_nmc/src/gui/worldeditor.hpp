#ifndef NMC_WORLDEDITOR_HPP
#define NMC_WORLDEDITOR_HPP

#include "guichan.hpp"
#include "gui/roomselector.hpp"
#include "gui/worldpiece.hpp"

#include <map>

namespace nmc
{
    class WorldEditor: public gcn::BasicContainer, 
                       public gcn::MouseListener, 
                       public gcn::ActionListener
    {
    public:
        WorldEditor(RoomSelector* roomSelector);
        ~WorldEditor();
        void draw(gcn::Graphics* graphics);
        void mousePressed(gcn::MouseEvent& mouseEvent);
        void mouseReleased(gcn::MouseEvent& mouseEvent);
        void mouseDragged(gcn::MouseEvent& mouseEvent);
        void action(const gcn::ActionEvent& actionEvent);
        void save();

    protected:
        void resizeToContent();

        RoomSelector* mRoomSelector;
        bool mDrawingNewRoom;
        int mNewRoomX;
        int mNewRoomY;
        int mNewRoomWidth;
        int mNewRoomHeight;

        gcn::Window* mNewRoomDialogWindow;
        gcn::Label* mNewRoomDialogWidthLabel;
        gcn::Label* mNewRoomDialogHeightLabel;
        gcn::Label* mNewRoomDialogNameLabel;
        gcn::TextField* mNewRoomDialogNameTextField;
        gcn::Button* mNewRoomDialogOKButton;
        gcn::Button* mNewRoomDialogCancelButton;

        std::map<int, WorldPiece*> mWorldPieces;
    };
}

#endif