#ifndef NMC_ROOMSELECTOR_HPP
#define NMC_ROOMSELECTOR_HPP

#include "guichan.hpp"

namespace nmc
{
    class RoomSelector: public gcn::ListBox
    {
    public:
        RoomSelector();
        int getSelectedRoom();
        void setSelectedRoom(int selectedRoom);
        void setSelected(int selected);

    protected:
        class RoomSelectorListModel: public gcn::ListModel
        {
        public:
            std::string getElementAt(int i);
            int getNumberOfElements();

        protected:
        };

        RoomSelectorListModel mRoomSelectorListModel;
    };
}

#endif