#include "area.hpp"
#include "room.hpp"
#include "gamestatemanager.hpp"
#include "entities/text.hpp"

namespace nmc
{
    Area::Area(const std::string& name)
        :mName(name),
        mFrameCounter(0)
    {

    }

    void Area::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
    {

    }

    void Area::logic(Room *room)
    {
        mFrameCounter++;

        if (mFrameCounter >= 50)
        {
            if (GameStateManager::getInstance()->getCurrent()->getString("area") != mName)
            {
                Text* text = new Text(mName);
                room->addEntity(text);
                GameStateManager::getInstance()->getCurrent()->setString("area", mName);
            }
        }
    }

    bool Area::isToBeDeleted()
    {
        return mFrameCounter > 50;
    }
}