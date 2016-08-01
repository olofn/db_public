#include "gui/dialog.hpp"

#include "resourcehandler.hpp"
#include "allegro.h"

#include <iostream>

Dialog::Dialog()
    :mWriteSpeed(3),
    mWriteFast(false),
    mFrameCounter(0),
    mCharacter(NONE)
{
    mBeepSample = ResourceHandler::getInstance()->getSample("beep.wav");
    mCornerUL = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("dialog-cornerul.bmp"));
	mCornerUR = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("dialog-cornerur.bmp"));
	mCornerDL = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("dialog-cornerdl.bmp"));
	mCornerDR = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("dialog-cornerdr.bmp"));
	mHorizontal = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("dialog-horizontal.bmp"));
	mVertical = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("dialog-vertical.bmp"));
    mBomb = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("bomb.bmp"));
    mFluffyLove = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("fluffylove.bmp"));
    mFluffyLoveAngry = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("fluffylove2.bmp"));
    mCuddelz= gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("cuddelz.bmp"));
    mDoctorMad = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("doctormad.bmp"));

    mFont = new gcn::ImageFont(ResourceHandler::getInstance()->getRealFilename("font.bmp"), 32, 127);
    mFont->setGlyphSpacing(-2);

    setFocusable(true);
    addKeyListener(this);
    addMouseListener(this);
}

Dialog::~Dialog()
{
    delete mFluffyLoveAngry;
    delete mDoctorMad;
    delete mCuddelz;
    delete mFluffyLove;
    delete mBomb;
    delete mCornerUL;
    delete mCornerUR;
    delete mCornerDL;
    delete mCornerDR;
    delete mHorizontal;
    delete mVertical;
    delete mFont;
}

void Dialog::draw(gcn::Graphics *graphics)
{
    int i;
    double height = (getHeight() - 8) / 8.0;
    gcn::Color c(0x7070FF);

    for (i = 0; i < 8; ++i)
    {
	    graphics->setColor(c * (1.0 - i / 9.0));
	    graphics->fillRectangle(gcn::Rectangle(4, 
                                               (int)(i*height+4), 
                                               getWidth()-8, 
                                               (int)((i*height)+height)));
    }

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
	    
        int x;
        if (mCharacter == NONE)
        {
            x = 5;
        }
        else
        {
            x = 64;
        }

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

    if (mCharacter == BOMB)
    {
        graphics->drawImage(mBomb, 5, 8);
    }
    else if (mCharacter == FLUFFY_LOVE)
    {
        graphics->drawImage(mFluffyLove, 5, 8);
    }
    else if (mCharacter == FLUFFY_LOVE_ANGRY)
    {
        graphics->drawImage(mFluffyLoveAngry, 5, 8);
    }
    else if (mCharacter == CUDDELZ)
    {
        graphics->drawImage(mCuddelz, 5, 8);
    }
    else if (mCharacter == DOCTOR_MAD)
    {
        graphics->drawImage(mDoctorMad, 5, 8);
    }

    graphics->popClipArea();
}

void Dialog::setText(const std::string &text)
{
    if (text.size() > 2 && text.at(0) == 'B')
    {
        mCharacter = BOMB;
        mText = text.substr(2, text.size() - 2);
    }
    else if (text.size() > 2 && text.at(0) == 'F')
    {
        mCharacter = FLUFFY_LOVE;
        mText = text.substr(2, text.size() - 2);
    }
    else if (text.size() > 2 && text.at(0) == 'A')
    {
        mCharacter = FLUFFY_LOVE_ANGRY;
        mText = text.substr(2, text.size() - 2);
    }
    else if (text.size() > 2 && text.at(0) == 'C')
    {
        mCharacter = CUDDELZ;
        mText = text.substr(2, text.size() - 2);
    }
    else if (text.size() > 2 && text.at(0) == 'D')
    {
        mCharacter = DOCTOR_MAD;
        mText = text.substr(2, text.size() - 2);
    }
    else
    {
        mCharacter = NONE;
       mText = text;
    }

    mWriteFast = false;
    mLettersWritten = 0;
    mWriteSpeed = 3;  
}

const std::string &Dialog::getText()
{
    return mText;
}

void Dialog::setVisible(bool visible)
{
    Widget::setVisible(visible);

    if (visible)
    {
        requestFocus();
        requestModalMouseInputFocus();
    }
    else
    {
        releaseModalMouseInputFocus();
    }
}

void Dialog::keyPressed(gcn::KeyEvent& keyEvent)
{
    if (keyEvent.getKey().getValue() == gcn::Key::LEFT_ALT)
    {
        if (mLettersWritten == mText.size() && !mWriteFast)
        {
            setVisible(false);
        }

        mWriteFast = true;
        mWriteSpeed = 1;
    }
}

void Dialog::mousePressed(gcn::MouseEvent& mouseEvent)
{
    if (mouseEvent.getButton() == gcn::MouseEvent::LEFT)
    {
        if (mLettersWritten == mText.size() && !mWriteFast)
        {
            setVisible(false);
        }

        mWriteFast = true;
        mWriteSpeed = 1;
    }
}

void Dialog::keyReleased(gcn::KeyEvent& keyEvent)
{
    if (keyEvent.getKey().getValue() == gcn::Key::LEFT_ALT)
    {
        mWriteFast = false;
        mWriteSpeed = 3;
    }
}

void Dialog::mouseReleased(gcn::MouseEvent& mouseEvent)
{
    if (mouseEvent.getButton() == gcn::MouseEvent::LEFT)
    {
        mWriteFast = false;
        mWriteSpeed = 3;
    }
}

void Dialog::logic()
{
    if (!isVisible())
    {
        return;
    }

    mFrameCounter++;

    if (mLettersWritten < mText.size() && ((mFrameCounter % mWriteSpeed) == 0))
    {
        mLettersWritten++;
        play_sample(mBeepSample, 128, 128, 1500, 0);
    }
}