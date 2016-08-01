#include "dbcontainer.hpp"
#include "resourcehandler.hpp"

DbContainer::DbContainer()
{
	mCornerUL = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/dialog-cornerul.bmp"));
	mCornerUR = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/dialog-cornerur.bmp"));
	mCornerDL = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/dialog-cornerdl.bmp"));
	mCornerDR = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/dialog-cornerdr.bmp"));
	mHorizontal = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/dialog-horizontal.bmp"));
	mVertical = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/dialog-vertical.bmp"));
}

DbContainer::~DbContainer()
{
	delete mCornerUL;
    delete mCornerUR;
    delete mCornerDL;
    delete mCornerDR;
    delete mHorizontal;
    delete mVertical;
}

void DbContainer::draw(gcn::Graphics *graphics)
{
	int i;

	graphics->setColor(gcn::Color(0x000000));
    graphics->fillRectangle(gcn::Rectangle(4, 
                                           4, 
                                           getWidth() - 8, 
                                           getHeight() -8));
   

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
