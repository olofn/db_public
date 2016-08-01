#include "worldpiece.hpp"

#include "resourcehandler.hpp"
#include "guichan/allegro.hpp"

namespace nmc
{
    WorldPiece::WorldPiece(int roomNumber)
        :mMoving(false)
    {
        mRoomNumber = roomNumber;
        mRoomBitmap = ResourceHandler::getInstance()->getHumanReadableRoomBitmap(roomNumber);
        setSize(mRoomBitmap->w, mRoomBitmap->h);

        addMouseListener(this);
    }

    int WorldPiece::getRoomNumber()
    {
        return mRoomNumber;
    }

    void WorldPiece::draw(gcn::Graphics* graphics)
    {
        gcn::AllegroGraphics* allegroGraphics = static_cast<gcn::AllegroGraphics*>(graphics);
        
        graphics->setColor(gcn::Color(0xffffff));
        graphics->fillRectangle(gcn::Rectangle(0, 0, getWidth(), getHeight()));

        masked_blit(mRoomBitmap,
                    allegroGraphics->getTarget(),
                    0,
                    0,
                    allegroGraphics->getCurrentClipArea().xOffset,
                    allegroGraphics->getCurrentClipArea().yOffset,
                    mRoomBitmap->w,
                    mRoomBitmap->h);

        graphics->setColor(gcn::Color(255, 0, 0, 160));
        graphics->drawRectangle(gcn::Rectangle(0, 0, getWidth(), getHeight()));       
    }

    void WorldPiece::mouseReleased(gcn::MouseEvent& mouseEvent)
    {   
        generateAction();
    }

    void WorldPiece::mousePressed(gcn::MouseEvent& mouseEvent)
    {
        if (mouseEvent.getSource() != this)
        {
            return;
        }
        
        if (getParent() != NULL)
        {
            getParent()->moveToTop(this);
        }

        mDragOffsetX = mouseEvent.getX();
        mDragOffsetY = mouseEvent.getY();
        
        mMoving = true;

        generateAction();
    }

    void WorldPiece::mouseDragged(gcn::MouseEvent& mouseEvent)
    {
        if (mouseEvent.isConsumed() || mouseEvent.getSource() != this)
        {
            return;
        }
        
        if (mMoving)
        {
            int x = mouseEvent.getX() - mDragOffsetX + getX();
            x = x - x % 20;
            int y = mouseEvent.getY() - mDragOffsetY + getY();
            y = y - y % 15;
            setPosition(x, y);
        }

        mouseEvent.consume();
    }
}