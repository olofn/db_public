#include "dbsh07button.hpp"

#include "resourcehandler.hpp"

DBSH07Button::DBSH07Button(const std::string& caption)
: Button(caption)
{
    setBorderSize(0);
    mNormalFont = new gcn::ImageFont(ResourceHandler::getInstance()->getRealFilename("font.bmp"), 32, 126);
	mNormalFont->setGlyphSpacing(-1);
    mHighLightFont = new gcn::ImageFont(ResourceHandler::getInstance()->getRealFilename("highlightfont.bmp"), 32, 126);
	mHighLightFont->setGlyphSpacing(-1);
}

void DBSH07Button::draw(gcn::Graphics* graphics)
{
    int textX = getWidth() / 2;
    int textY = getHeight() / 2 - getFont()->getHeight() / 2;

    if (mHasMouse)
    {
        graphics->setFont(mHighLightFont);
    }
    else
    {
        graphics->setFont(mNormalFont);
    }

    graphics->drawText(getCaption(), textX, textY, getAlignment());
}