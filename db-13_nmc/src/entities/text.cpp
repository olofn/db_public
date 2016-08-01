#include "entities/text.hpp"
#include "room.hpp"

namespace nmc
{
    Text::Text(const std::string& text, int timeToShowText)
        : mText(text),
        mFrameCounter(0),
        mTimeToShowText(timeToShowText)
    {

    }

    void Text::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
    {

    }

    void Text::logic(Room *room)
    {
        mFrameCounter++;

        if (mTimeToShowText > mFrameCounter
            &&  !room->getTextBox()->isVisible())
        {
            room->getTextBox()->setText(mText);
            room->getTextBox()->setVisible(true);
            room->getTextBox()->setPosition(160 - room->getTextBox()->getWidth() / 2,
                                            120 - room->getTextBox()->getHeight() / 2);
        }

        if (mTimeToShowText <= mFrameCounter)
        {
            room->getTextBox()->setVisible(false);
        }
    }

    bool Text::isToBeDeleted()
    {
        return mFrameCounter > mTimeToShowText;
    }
}