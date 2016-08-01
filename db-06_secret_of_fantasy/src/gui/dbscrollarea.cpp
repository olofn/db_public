#include <guichan.hpp>

#include "gui/dbscrollarea.hpp"

DbScrollArea::DbScrollArea()
{
	setScrollPolicy(SHOW_NEVER,	SHOW_ALWAYS);
	setFocusable(false);
}

void DbScrollArea::draw(gcn::Graphics *graphics)
{
    drawChildren(graphics);

	if (getVerticalMaxScroll() != 0)
	{
		int y = ((getHeight() - 32) * getVerticalScrollAmount()) /
			getVerticalMaxScroll();

		graphics->setColor(0x000000);
		graphics->drawRectangle(gcn::Rectangle(getWidth()-11, y, 8, 32));
		graphics->drawRectangle(gcn::Rectangle(getWidth()-10, y+1, 8, 32));

		graphics->setColor(0xffffff);

		graphics->fillRectangle(gcn::Rectangle(getWidth()-10, y+1, 6, 30));
	}
}