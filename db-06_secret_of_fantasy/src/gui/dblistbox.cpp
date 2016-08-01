#include <guichan.hpp>

#include "gui/dblistbox.hpp"
#include "resourcehandler.hpp"
#include "guichan/allegro.hpp"

DBListBox::DBListBox()
{
	setFrameSize(0);
    mSelectedImage = ResourceHandler::getInstance()->getBitmap("gui/hand.bmp");
}

DBListBox::~DBListBox()
{

}

void DBListBox::draw(gcn::Graphics* graphics)
{
    gcn::AllegroGraphics* allegroGraphics = static_cast<gcn::AllegroGraphics*>(graphics);

	if (mListModel == NULL)
	{
		return;
	}

	allegroGraphics->setColor(getForegroundColor());
	allegroGraphics->setFont(getFont());

	int i, fontHeight;
	int y = 0;

	fontHeight = getFont()->getHeight();

	for (i = 0; i < mListModel->getNumberOfElements(); ++i)
	{
		allegroGraphics->drawText(mListModel->getElementAt(i), 10, y);

		if (i == mSelected)
		{
			if (isFocused())
			{
				allegroGraphics->drawBitmap(mSelectedImage, 0, y + 1);
			}
		}

		y += fontHeight;
	}
}

void DBListBox::setSelected(int i)
{
    gcn::ListBox::setSelected(i);
}

void DBListBox::keyPressed(gcn::KeyEvent& keyEvent)
{
	gcn::Key key = keyEvent.getKey();

	if (key.getValue() == gcn::Key::LEFT_ALT)
    {
        distributeActionEvent();
        keyEvent.consume();
    }
    else if (key.getValue() == gcn::Key::UP)
    {
        setSelected(mSelected - 1);

        if (mSelected == -1)
        {
            if (mWrappingEnabled)
            {
                setSelected(getListModel()->getNumberOfElements() - 1);
            }
            else
            {
                setSelected(0);
            }
        }
        
        keyEvent.consume();
    }
    else if (key.getValue() == gcn::Key::DOWN)
    {
        if (mWrappingEnabled
            && getSelected() == getListModel()->getNumberOfElements() - 1)
        {
            setSelected(0);
        }
        else
        {
            setSelected(getSelected() + 1);
        }
        
        keyEvent.consume();
    }
    else if (key.getValue() == gcn::Key::HOME)
    {
        setSelected(0);
        keyEvent.consume();
    }
    else if (key.getValue() == gcn::Key::END)
    {
        setSelected(getListModel()->getNumberOfElements() - 1);
        keyEvent.consume();
    }
}
