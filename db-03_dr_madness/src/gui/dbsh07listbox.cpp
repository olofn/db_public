#include <guichan.hpp>

#include "gui/dbsh07listbox.hpp"
#include "resourcehandler.hpp"
#include "guichan/allegro.hpp"

DBSH07ListBox::DBSH07ListBox()
{
	setBorderSize(0);
    mSelectedImage = ResourceHandler::getInstance()->getBitmap("hand.bmp");
}

DBSH07ListBox::~DBSH07ListBox()
{

}

void DBSH07ListBox::draw(gcn::Graphics* graphics)
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

void DBSH07ListBox::setSelected(int i)
{
    /*
	if (i >= 0 &&
			i < getListModel()->getNumberOfElements() &&
			getListModel()->getElementAt(i) == "")
	{
		if (i < getSelected())
		{
			i--;
		}
		else
		{
			i++;
		}
	}
    */
	
    gcn::ListBox::setSelected(i);
}
