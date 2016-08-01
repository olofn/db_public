#include "gui/inttextfield.hpp"
#include "stringutil.hpp"

namespace nmc
{
    int IntTextField::getIntValue()
    {
        return fromString<int>(getText());
    }

    void IntTextField::keyPressed(gcn::KeyEvent& keyEvent)
    {
        gcn::Key key = keyEvent.getKey();

        if (key.getValue() == gcn::Key::LEFT && mCaretPosition > 0)
        {
            --mCaretPosition;
        }

        else if (key.getValue() == gcn::Key::RIGHT && mCaretPosition < mText.size())
        {
            ++mCaretPosition;
        }

        else if (key.getValue() == gcn::Key::DELETE && mCaretPosition < mText.size())
        {
            mText.erase(mCaretPosition, 1);
        }

        else if (key.getValue() == gcn::Key::BACKSPACE && mCaretPosition > 0)
        {
            mText.erase(mCaretPosition - 1, 1);
            --mCaretPosition;
        }

        else if (key.getValue() == gcn::Key::ENTER)
        {
            generateAction();
        }

        else if (key.getValue() == gcn::Key::HOME)
        {
            mCaretPosition = 0;
        }

        else if (key.getValue() == gcn::Key::END)
        {
            mCaretPosition = mText.size();
        }

        else if (key.isNumber())
        {
            mText.insert(mCaretPosition, std::string(1,(char)key.getValue()));
            ++mCaretPosition;
        }

        if (key.getValue() != gcn::Key::TAB)
        {
            keyEvent.consume();
        }
        
        fixScroll();
    }

}