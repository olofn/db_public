#include "gui/dbsh07textfield.hpp"

DBSH07TextField::DBSH07TextField(const std::string& text)
:TextField(text),
mFrameCounter(0)
{
    setBorderSize(0);
}
    
void DBSH07TextField::draw(gcn::Graphics* graphics)
{
    graphics->setFont(getFont());
    graphics->drawText(mText, 1 - mXScroll, 1);
    drawCaret(graphics, getFont()->getWidth(mText.substr(0, mCaretPosition)) - mXScroll);
}

void DBSH07TextField::drawCaret(gcn::Graphics* graphics, int x)
{   
    if (mFrameCounter % 40 < 20)
    {
        graphics->drawText("\x7f", x, 1);
    }
}

void DBSH07TextField::logic()
{
    mFrameCounter++;
}

void DBSH07TextField::keyPressed(gcn::KeyEvent &keyEvent)
{
	if (keyEvent.getKey().getValue() != ',')
	{
		if (getText().size() < 10 || keyEvent.getKey().getValue() == gcn::Key::BACKSPACE || keyEvent.getKey().getValue() == gcn::Key::ENTER)
		{
			gcn::TextField::keyPressed(keyEvent);
		}
	}
}