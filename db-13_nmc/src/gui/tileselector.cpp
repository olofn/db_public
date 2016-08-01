#include "gui/tileselector.hpp"       

#include "resourcehandler.hpp"
#include "guichan/allegro.hpp"

namespace nmc
{
    TileSelector::TileSelector()
        : mSelectedTile(0),
          mDrawMouseHoverTile(false)
    {
        mTileSetBitmap = ResourceHandler::getInstance()->getBitmap("tileset.bmp");
        setWidth(mTileSetBitmap->w);
        setHeight(mTileSetBitmap->h);

        addMouseListener(this);
    }

    void TileSelector::draw(gcn::Graphics* graphics)
    {
        gcn::AllegroGraphics* allegroGraphics = static_cast<gcn::AllegroGraphics*>(graphics);

        allegroGraphics->drawBitmap(mTileSetBitmap, 0, 0);

        graphics->setColor(gcn::Color(0x0000ff));
        graphics->drawRectangle(gcn::Rectangle((mSelectedTile % (mTileSetBitmap->w / 16)) * 16,
                                               (mSelectedTile / (mTileSetBitmap->w / 16)) * 16,
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

    void TileSelector::logic()
    {

    }

    void TileSelector::mouseMoved(gcn::MouseEvent& mouseEvent)
    {
        if (mouseEvent.getX() <= mTileSetBitmap->w
            && mouseEvent.getY() <= mTileSetBitmap->h)
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

    void TileSelector::mouseEntered(gcn::MouseEvent& mouseEvent)
    {
        mDrawMouseHoverTile = true;
    }

    void TileSelector::mouseExited(gcn::MouseEvent& mouseEvent)
    {
        mDrawMouseHoverTile = false;
    }

    void TileSelector::mousePressed(gcn::MouseEvent& mouseEvent)
    {
       if (mouseEvent.getX() <= mTileSetBitmap->w
            && mouseEvent.getY() <= mTileSetBitmap->h)
        {
            mSelectedTile = mouseEvent.getX() / 16
                          + (mouseEvent.getY() / 16) * mTileSetBitmap->w / 16;
            generateAction();
        }
    }

    int TileSelector::getSelectedTile()
    {
        return mSelectedTile;
    }

    void TileSelector::setSelectedTile(int selectedTile)
    {
        mSelectedTile = selectedTile;
    }
}