#include "gui/entityselector.hpp"       

#include "resourcehandler.hpp"
#include "guichan/allegro.hpp"

namespace nmc
{
    EntitySelector::EntitySelector()
        : mSelectedEntity(0),
          mDrawMouseHoverTile(false)
    {
        mEntitySetBitmap = ResourceHandler::getInstance()->getBitmap("entityset.bmp");
        setWidth(mEntitySetBitmap->w);
        setHeight(mEntitySetBitmap->h);

        addMouseListener(this);
    }

    void EntitySelector::draw(gcn::Graphics* graphics)
    {
        gcn::AllegroGraphics* allegroGraphics = static_cast<gcn::AllegroGraphics*>(graphics);

        allegroGraphics->drawBitmap(mEntitySetBitmap, 0, 0);

        graphics->setColor(gcn::Color(0x0000ff));
        graphics->drawRectangle(gcn::Rectangle((mSelectedEntity % (mEntitySetBitmap->w / 16)) * 16,
                                               (mSelectedEntity / (mEntitySetBitmap->w / 16)) * 16,
                                               16,
                                               16));
        if (mDrawMouseHoverTile)
        {
            graphics->setColor(gcn::Color(0xff0000));
            graphics->drawRectangle(gcn::Rectangle(mCurrentMouseX - mCurrentMouseX % 16,
                                                   mCurrentMouseY - mCurrentMouseY % 16,
                                                   16,
                                                   16));
        }
    }

    void EntitySelector::logic()
    {

    }

    void EntitySelector::mouseMoved(gcn::MouseEvent& mouseEvent)
    {
        if (mouseEvent.getX() <= mEntitySetBitmap->w
            && mouseEvent.getY() <= mEntitySetBitmap->h)
        {
            mCurrentMouseX = mouseEvent.getX();
            mCurrentMouseY = mouseEvent.getY();
            mDrawMouseHoverTile = true;
        }
        else
        {
            mDrawMouseHoverTile = false;
        }
    }

    void EntitySelector::mouseEntered(gcn::MouseEvent& mouseEvent)
    {
        mDrawMouseHoverTile = true;
    }

    void EntitySelector::mouseExited(gcn::MouseEvent& mouseEvent)
    {
        mDrawMouseHoverTile = false;
    }

    void EntitySelector::mousePressed(gcn::MouseEvent& mouseEvent)
    {
       if (mouseEvent.getX() <= mEntitySetBitmap->w
            && mouseEvent.getY() <= mEntitySetBitmap->h)
        {
            mSelectedEntity = mouseEvent.getX() / 16
                            + (mouseEvent.getY() / 16) * mEntitySetBitmap->w / 16;
            generateAction();
        }
    }

    int EntitySelector::getSelectedEntity()
    {
        return mSelectedEntity;
    }

    void EntitySelector::setSelectedEntity(int selectedEntity)
    {
        mSelectedEntity = selectedEntity;
    }
}