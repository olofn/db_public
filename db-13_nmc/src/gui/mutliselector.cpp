#include "gui/multiselector.hpp"

#include "resourcehandler.hpp"

namespace nmc
{
    MultiSelector::MultiSelector()
        : mCurrentSelection(0),
        mFrameCounter(0)
    {
        setFocusable(true);
        mSelectorImage = gcn::Image::load(ResourceHandler::getInstance()->getRealFilename("menu-selector.bmp"));

        addKeyListener(this);
    }

    MultiSelector::~MultiSelector()
    {
        delete mSelectorImage;
    }

    void MultiSelector::draw(gcn::Graphics* graphics)
    {
        if (mSelections.empty())
        {
            return;
        }

        if (isFocused() || (!isFocused() && (mFrameCounter % 20 < 10)))
        {
            Selection selection = mSelections[mCurrentSelection];
            graphics->drawImage(mSelectorImage, 
                                selection.x,
                                selection.y);
        }
    }

    void MultiSelector::logic()
    {
        mFrameCounter++;
    }

    void MultiSelector::addSelection(int x, int y)
    {
        mSelections.push_back(Selection(x, y));
    }

    int MultiSelector::getSelectorHeight()
    {
        return mSelectorImage->getHeight();
    }

    int MultiSelector::getSelectorWidth()
    {
        return mSelectorImage->getWidth();
    }

    void MultiSelector::keyPressed(gcn::KeyEvent& keyEvent)
    {
        if (keyEvent.getKey().getValue() == gcn::Key::DOWN)
        {
            setSelected(getSelected() + 1);
        }
        else if (keyEvent.getKey().getValue() == gcn::Key::UP)
        {
            setSelected(getSelected() - 1);
        }
        else if (keyEvent.getKey().getValue() == gcn::Key::SPACE
            || keyEvent.getKey().getValue() == gcn::Key::LEFT_ALT
            || keyEvent.getKey().getValue() == gcn::Key::LEFT_CONTROL
            || keyEvent.getKey().getValue() == gcn::Key::ENTER)
        {
            generateAction();
        }
    }

    int MultiSelector::getSelected()
    {
        return mCurrentSelection;
    }

    void MultiSelector::setSelected(int selected)
    {
        mCurrentSelection = selected;

        if (mCurrentSelection < 0)
        {
            mCurrentSelection = 0;
            return;
        }

        if (mCurrentSelection >= mSelections.size())
        {
            mCurrentSelection = mSelections.size() - 1;
            
        }
    }   
}