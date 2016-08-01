#include "gui/imagecheckbox.hpp"

#include "resourcehandler.hpp"

namespace nmc
{
    ImageCheckBox::ImageCheckBox(const std::string& filename)
    {
        mImage = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename(filename));

        setWidth(mImage->getWidth() + mImage->getWidth() / 2);
        setHeight(mImage->getHeight() + mImage->getHeight() / 2);
    }

    ImageCheckBox::~ImageCheckBox()
    {
        delete mImage;
    }

    void ImageCheckBox::draw(gcn::Graphics* graphics)
    {
        gcn::Color faceColor = getBaseColor();
        gcn::Color highlightColor, shadowColor;
        int alpha = getBaseColor().a;

        if (isMarked())
        {
            faceColor = faceColor - 0x303030;
            faceColor.a = alpha;
            highlightColor = faceColor - 0x303030;
            highlightColor.a = alpha;
            shadowColor = faceColor + 0x303030;
            shadowColor.a = alpha;
        }
        else
        {
            highlightColor = faceColor + 0x303030;
            highlightColor.a = alpha;
            shadowColor = faceColor - 0x303030;
            shadowColor.a = alpha;
        }

        graphics->setColor(faceColor);
        graphics->fillRectangle(gcn::Rectangle(1, 1, getDimension().width-1, getHeight() - 1));

        graphics->setColor(highlightColor);
        graphics->drawLine(0, 0, getWidth() - 1, 0);
        graphics->drawLine(0, 1, 0, getHeight() - 1);

        graphics->setColor(shadowColor);
        graphics->drawLine(getWidth() - 1, 1, getWidth() - 1, getHeight() - 1);
        graphics->drawLine(1, getHeight() - 1, getWidth() - 1, getHeight() - 1);

        graphics->setColor(getForegroundColor());

        int textX = getWidth() / 2 - mImage->getWidth() / 2;
        int textY = getHeight() / 2 - mImage->getHeight() / 2;

        if (isMarked())
        {
            graphics->drawImage(mImage, textX + 1, textY + 1);
        }
        else
        {
            graphics->drawImage(mImage, textX, textY);
           
            if (isFocused())
            {
                graphics->drawRectangle(gcn::Rectangle(2, 
                                                       2, 
                                                       getWidth() - 4,
                                                       getHeight() - 4));
            }
        }
    }
     
    void ImageCheckBox::drawBorder(gcn::Graphics* graphics)
    {
        gcn::Color faceColor = getBaseColor();
        gcn::Color highlightColor, shadowColor;
        int alpha = getBaseColor().a;
        int width = getWidth() + getBorderSize() * 2 - 1;
        int height = getHeight() + getBorderSize() * 2 - 1;
        highlightColor = faceColor + 0x303030;
        highlightColor.a = alpha;
        shadowColor = faceColor - 0x303030;
        shadowColor.a = alpha;

        unsigned int i;
        for (i = 0; i < getBorderSize(); ++i)
        {
            graphics->setColor(shadowColor);
            graphics->drawLine(i,i, width - i, i);
            graphics->drawLine(i,i + 1, i, height - i - 1);
            graphics->setColor(highlightColor);
            graphics->drawLine(width - i,i + 1, width - i, height - i);
            graphics->drawLine(i,height - i, width - i - 1, height - i);
        }
    }
}