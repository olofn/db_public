#include "gui/decoratedcontainer.hpp"

#include "resourcehandler.hpp"

namespace nmc
{
    DecoratedContainer::DecoratedContainer()
    {
        mCornerUL = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("dialog-cornerul.bmp"));
		mCornerUR = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("dialog-cornerur.bmp"));
		mCornerDL = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("dialog-cornerdl.bmp"));
		mCornerDR = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("dialog-cornerdr.bmp"));
		mHorizontal = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("dialog-horizontal.bmp"));
		mVertical = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("dialog-vertical.bmp"));
    }

    DecoratedContainer::~DecoratedContainer()
    {
        delete mCornerUL;
        delete mCornerUR;
        delete mCornerDL;
        delete mCornerDR;
        delete mHorizontal;
        delete mVertical;
    }

    void DecoratedContainer::draw(gcn::Graphics* graphics)
    {
        if (isOpaque())
        {
            graphics->setColor(getBackgroundColor());
            graphics->fillRectangle(gcn::Rectangle(2, 2, getWidth() - 4, getHeight() - 4));
        }

        int i;
        for (i = 5; i < getHeight()-10; i+=5)
	    {
		    graphics->drawImage(mVertical, 0, i);
		    graphics->drawImage(mVertical, getWidth()-4, i);
	    }
	    graphics->drawImage(mVertical, 0, 0, 0, i, 4, getHeight()-5-i);
	    graphics->drawImage(mVertical, 0, 0, getWidth()-4, i, 4, getHeight()-5-i);

	    for (i = 5; i < getWidth()-10; i+=5)
	    {
		    graphics->drawImage(mHorizontal, i, 0);
		    graphics->drawImage(mHorizontal, i, getHeight()-4);
	    }
	    graphics->drawImage(mHorizontal, 0, 0, i, 0, getWidth()-5-i, 4);
	    graphics->drawImage(mHorizontal, 0, 0, i, getHeight()-4, getWidth()-5-i, 4);

	    graphics->drawImage(mCornerUL, 0, 0);
	    graphics->drawImage(mCornerUR, getWidth()-5, 0);
	    graphics->drawImage(mCornerDL, 0, getHeight()-5);
	    graphics->drawImage(mCornerDR, getWidth()-5, getHeight()-5);

        drawChildren(graphics);
    }

    gcn::Rectangle DecoratedContainer::getChildrenArea()
    {
        return gcn::Rectangle(5, 5, getWidth() - 10, getHeight() - 10);
    }
}