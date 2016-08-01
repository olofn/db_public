#include "roomselector.hpp"

#include <iostream>
#include "resourcehandler.hpp"

namespace nmc
{
    RoomSelector::RoomSelector()
    {
        setListModel(&mRoomSelectorListModel);
    }

    void RoomSelector::setSelected(int selected)
    {
        gcn::ListBox::setSelected(selected);
        generateAction();
    }

    int RoomSelector::getSelectedRoom()
    {
        return ResourceHandler::getInstance()->getRoomNumberList()[getSelected()];
    }
        
    void RoomSelector::setSelectedRoom(int selectedRoom)
    {
        unsigned int i;
        for (i = 0; i < ResourceHandler::getInstance()->getRoomNumberList().size(); i++)
        {
            if (selectedRoom == ResourceHandler::getInstance()->getRoomNumberList()[i])
            {
                setSelected(i);
                return;
            }
        }
    }
    
    std::string RoomSelector::RoomSelectorListModel::getElementAt(int i)
    {
        int roomNumber = ResourceHandler::getInstance()->getRoomNumberList()[i];
        return ResourceHandler::getInstance()->getRoomName(roomNumber);
    }
            
    int RoomSelector::RoomSelectorListModel::getNumberOfElements()
    {
        return ResourceHandler::getInstance()->getRoomNumberList().size();
    }
}