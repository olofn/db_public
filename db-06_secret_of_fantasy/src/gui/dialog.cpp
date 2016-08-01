#include "gui/dialog.hpp"

#include "resourcehandler.hpp"
#include "stringutil.hpp"
#include "allegro.h"

#include <iostream>

Dialog::Dialog()
    :mWriteSpeed(3),
    mWriteFast(false),
    mFrameCounter(0),
    mDone(false)
{
    //mBeepSample = ResourceHandler::getInstance()->getSample("beep.wav");
    mCornerUL = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/dialog-cornerul.bmp"));
	mCornerUR = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/dialog-cornerur.bmp"));
	mCornerDL = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/dialog-cornerdl.bmp"));
	mCornerDR = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/dialog-cornerdr.bmp"));
	mHorizontal = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/dialog-horizontal.bmp"));
	mVertical = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("gui/dialog-vertical.bmp"));

    mFont = new gcn::ImageFont(ResourceHandler::getInstance()->getRealFilename("gui/nesfont.bmp"), "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.!?:;_()-");
	mFont->setRowSpacing(3);
    setFocusable(true);
    addKeyListener(this);
}

Dialog::~Dialog()
{
    delete mCornerUL;
    delete mCornerUR;
    delete mCornerDL;
    delete mCornerDR;
    delete mHorizontal;
    delete mVertical;
    delete mFont;
}

bool Dialog::isDone()
{
    return mDone;
}

void Dialog::draw(gcn::Graphics *graphics)
{
    int i;

	graphics->setColor(gcn::Color(0x0000aa));
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

    if (mText.length() == 0) 
    {
	    return;
    }

    graphics->pushClipArea(gcn::Rectangle(5, 5, getWidth() - 10, getHeight() - 10));

    graphics->setFont(mFont);

    std::string textLeft = mText.substr(0, mLettersWritten);
    int rownum = 0;

    while (true) 
    {
	    int i = mFont->getStringIndexAt(textLeft, getWidth() - 84);
	    int end = textLeft.length();
	   
        if (i < end - 1) 
        {
		    end = textLeft.rfind(" ", i);
	    }
	    
        int x = 5;

        std::string row = textLeft.substr(0, end);
	    if (end != textLeft.length()) 
        {
            graphics->drawText(row, x, mFont->getHeight() * rownum + 8);
	    } 
        else
        {
            graphics->drawText(row, x, mFont->getHeight() * rownum + 8);

	    }
	    rownum++;
	    
        if (end == textLeft.length()) 
        {
		    break;
	    }

	    textLeft = textLeft.substr(end + 1, textLeft.length() - end - 1);
    }


    if (mLettersWritten == mText.size() && mFrameCounter % 20 < 10)
    {
        graphics->drawText(std::string("") + char(127),
                           getWidth() - 15 - mFont->getWidth(std::string("") + char(127)), 
                           getHeight() - 15 - mFont->getHeight());
    }

    graphics->popClipArea();
}

void Dialog::setText(const std::string &text)
{
	mText = toUpperCase(text);
    mWriteFast = false;
    mLettersWritten = 0;
    mWriteSpeed = 3; 
    mDone = false;
}

const std::string &Dialog::getText()
{
    return mText;
}

void Dialog::keyPressed(gcn::KeyEvent& keyEvent)
{
    if (keyEvent.getKey().getValue() == gcn::Key::LEFT_ALT)
    {
        if (mLettersWritten == mText.size() && !mWriteFast)
        {
            mDone = true;
        }

        mWriteFast = true;
        mWriteSpeed = 1;
    }
}

void Dialog::keyReleased(gcn::KeyEvent& keyEvent)
{
    if (keyEvent.getKey().getValue() == gcn::Key::LEFT_ALT
         || keyEvent.getKey().getValue() == gcn::Key::SPACE
        || keyEvent.getKey().getValue() == gcn::Key::ENTER)
    {
        mWriteFast = false;
        mWriteSpeed = 3;
    }
}

void Dialog::logic()
{
    if (!isVisible() || mDone)
    {
        return;
    }

    mFrameCounter++;

    if (mLettersWritten < mText.size() && ((mFrameCounter % mWriteSpeed) == 0))
    {
        mLettersWritten++;
        //play_sample(mBeepSample, 100, 128, 800, 0);
    }
}