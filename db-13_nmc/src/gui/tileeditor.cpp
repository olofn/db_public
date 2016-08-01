#include "tileeditor.hpp"

#include "guichan/allegro.hpp"
#include <iostream>

namespace nmc
{
    TileEditor::TileEditor(TileToolBox* tileToolBox,
                           EntitySelector* entitySelector)
        : mShowMouseHoverTile(false),
        mTileToolBox(tileToolBox),
        mEntitySelector(entitySelector),
        mDraw(false),
        mShowEntities(true),
		mEntityEditMode(false),
        mMode(NORMAL)
    {
        mTileMap = new TileMap();

        addMouseListener(this);
    }

    TileEditor::~TileEditor()
    {
        delete mTileMap;
    }

    void TileEditor::setMode(Mode mode)
    {
        mMode = mode;
    }

    void TileEditor::save()
    {
        mTileMap->save();
    }

    void TileEditor::setShowSolidity(bool showSolidity)
    {
        mTileMap->setShowSolidity(showSolidity);
    }

    void TileEditor::setShowForegroundLayer(bool showForegroundLayer)
    {
        mTileMap->setShowForegroundLayer(showForegroundLayer);
    }

    void TileEditor::setShowBackgroundLayer(bool showBackgroundLayer)
    {
        mTileMap->setShowBackgroundLayer(showBackgroundLayer);
    }

    void TileEditor::setShowEntities(bool showEntities)
    {
        mTileMap->setShowEntities(showEntities);
        mShowEntities = showEntities;
    }

    void TileEditor::draw(gcn::Graphics* graphics)
    {
        gcn::AllegroGraphics* allegroGraphics = static_cast<gcn::AllegroGraphics*>(graphics);

        gcn::ClipRectangle clipArea = allegroGraphics->getCurrentClipArea();

        mTileMap->draw(allegroGraphics->getTarget(),
                       -clipArea.xOffset,
                       -clipArea.yOffset,
                       TileMap::BACKGROUND_LAYER);
        mTileMap->draw(allegroGraphics->getTarget(),
                       -clipArea.xOffset,
                       -clipArea.yOffset,
                       TileMap::FOREGROUND_LAYER);
        mTileMap->draw(allegroGraphics->getTarget(),
                   -clipArea.xOffset,
                   -clipArea.yOffset,
                   TileMap::ENTITY_LAYER);

        graphics->setColor(gcn::Color(0xff0000));
        graphics->drawRectangle(gcn::Rectangle(0,
                                               0,
                                               mTileMap->getWidth()*16,
                                               mTileMap->getHeight()*16));

        if (mMode == NORMAL && mShowMouseHoverTile)
        {
            
            graphics->drawRectangle(gcn::Rectangle(mCurrentMouseX - mCurrentMouseX % 16,
                                                   mCurrentMouseY - mCurrentMouseY % 16,
                                                   16,
                                                   16));
        }

        if (mMode == FILL && mDraw)
        {
            if (mFillX > mCurrentMouseX
                && mFillY > mCurrentMouseY)
            {
                graphics->drawRectangle(gcn::Rectangle(mFillX,
                                                       mFillY,
                                                       mCurrentMouseX - mCurrentMouseX % 16 - mFillX,
                                                       mCurrentMouseY - mCurrentMouseY % 16 - mFillY));
            }
            else if (mFillX > mCurrentMouseX)
            {
                graphics->drawRectangle(gcn::Rectangle(mFillX,
                                                       mFillY,
                                                       mCurrentMouseX - mCurrentMouseX % 16 - mFillX,
                                                       mCurrentMouseY - mCurrentMouseY % 16 - mFillY + 16));
            }
            else if (mFillY > mCurrentMouseY)
            {
                graphics->drawRectangle(gcn::Rectangle(mFillX,
                                                    mFillY,
                                                    mCurrentMouseX - mCurrentMouseX % 16 - mFillX + 16,
                                                    mCurrentMouseY - mCurrentMouseY % 16 - mFillY));
            }
            else
            {
                graphics->drawRectangle(gcn::Rectangle(mFillX,
                                                       mFillY,
                                                       mCurrentMouseX - mCurrentMouseX % 16 - mFillX + 16,
                                                       mCurrentMouseY - mCurrentMouseY % 16 - mFillY + 16));
            }
        }

		graphics->setColor(gcn::Color(0xffff00));

        // Draw door markers.
		int i;
		for (i = 0; i < mTileMap->getWidth(); i += 20)
		{
            graphics->drawLine((i + 8) * 16, 
                                0, 
                                (i + 8) * 16, 
                                8);
            graphics->drawLine((i + 12) * 16 - 1, 
                                0, 
                                (i + 12) * 16 - 1, 
                                8);
            graphics->drawLine((i + 8) * 16, 
                                mTileMap->getHeight() * 16 - 9, 
                                (i + 8) * 16, 
                                mTileMap->getHeight() * 16 - 1);
	        graphics->drawLine((i + 12) * 16 - 1,
                                mTileMap->getHeight() * 16 - 9, 
                                (i + 12) * 16 - 1, 
                                mTileMap->getHeight() * 16 - 1);
		}

		for (i = 0; i < mTileMap->getHeight(); i += 15)
		{
			graphics->drawLine(0, (i + 6) * 16, 8, (i + 6) * 16);
			graphics->drawLine(0, (i + 9) * 16 - 1, 8, (i + 9) * 16 - 1);
			graphics->drawLine(mTileMap->getWidth() * 16 - 9, (i + 6) * 16, mTileMap->getWidth() * 16 - 1, (i + 6) * 16);
			graphics->drawLine(mTileMap->getWidth() * 16 - 9, (i + 9) * 16 - 1, mTileMap->getWidth() * 16 - 1, (i + 9) * 16 - 1);			
		}
    }

    void TileEditor::setRoom(int room)
    {
        mTileMap->load(room);
        mTileMap->setShowEntities(mShowEntities);
        setWidth(mTileMap->getWidth()*16);
        setHeight(mTileMap->getHeight()*16);
    }

    void TileEditor::mouseMoved(gcn::MouseEvent& mouseEvent)
    {
        if (mMode == NORMAL)
        {
            if (mouseEvent.getX() <= mTileMap->getWidth()*16
                && mouseEvent.getY() <= mTileMap->getHeight()*16)
            {
                mCurrentMouseX = mouseEvent.getX();
                mCurrentMouseY = mouseEvent.getY();
                mShowMouseHoverTile = true;
            }
            else
            { 
                mShowMouseHoverTile = false;
            }
        }
        else if (mMode == FILL)
        {
            if (mouseEvent.getX() <= mTileMap->getWidth()*16
                && mouseEvent.getY() <= mTileMap->getHeight()*16)
            {
                mCurrentMouseX = mouseEvent.getX();
                mCurrentMouseY = mouseEvent.getY();
            }
        }
    }

    void TileEditor::mouseDragged(gcn::MouseEvent& mouseEvent)
    {
        if (mMode == NORMAL)
        {
            if (mouseEvent.getX() < mTileMap->getWidth()*16
                && mouseEvent.getY() < mTileMap->getHeight()*16)
            {
                mCurrentMouseX = mouseEvent.getX();
                mCurrentMouseY = mouseEvent.getY();
                mShowMouseHoverTile = true;
                
                if (mDraw && mEntityEditMode)
                {
                    mTileMap->setTileEntity(mouseEvent.getX() / 16,
                                            mouseEvent.getY() / 16,
                                            mEntitySelector->getSelectedEntity());
                }
                else if (mDraw)
                {
                    mTileMap->setTile(mouseEvent.getX() / 16,
                                      mouseEvent.getY() / 16,
                                      mTileToolBox->getSelectedTileNumber());
                    mTileMap->setTileFlags(mouseEvent.getX() / 16,
                                       mouseEvent.getY() / 16,
                                       mTileToolBox->getSelectedTileFlags());
                }
                
            }
            else
            { 
                mShowMouseHoverTile = false;
            }    
        }
        else if (mMode == FILL)
        {
            if (mouseEvent.getX() <= mTileMap->getWidth()*16
                && mouseEvent.getY() <= mTileMap->getHeight()*16)
            {
                mCurrentMouseX = mouseEvent.getX();
                mCurrentMouseY = mouseEvent.getY();
            }
        }
    }

    void TileEditor::mousePressed(gcn::MouseEvent& mouseEvent)
    {
        if (mouseEvent.getButton() == gcn::MouseEvent::RIGHT)
        {
            if (mEntityEditMode)
            {
			    mEntitySelector->setSelectedEntity(mTileMap->getTileEntity(mouseEvent.getX() / 16,
                                                    mouseEvent.getY() / 16));
            }
            else
            {
                mTileToolBox->setSelectedTileNumber(mTileMap->getTile(mouseEvent.getX() / 16,
                                                    mouseEvent.getY() / 16));
                mTileToolBox->setSelectedTileFlags(mTileMap->getTileFlags(mouseEvent.getX() / 16,
                                                   mouseEvent.getY() / 16));  
            }

            mDraw = false;
            return;
        }

        if (mMode == NORMAL)
        {
            if (mouseEvent.getX() < mTileMap->getWidth()*16
                && mouseEvent.getY() < mTileMap->getHeight()*16)
            {
                mCurrentMouseX = mouseEvent.getX();
                mCurrentMouseY = mouseEvent.getY();
                mShowMouseHoverTile = true;

                if (mEntityEditMode)
                {
                    mTileMap->setTileEntity(mouseEvent.getX() / 16,
                                            mouseEvent.getY() / 16,
                                            mEntitySelector->getSelectedEntity());
                }
                else
                {     
                    mTileMap->setTile(mouseEvent.getX() / 16,
                                      mouseEvent.getY() / 16,
                                      mTileToolBox->getSelectedTileNumber());
                    mTileMap->setTileFlags(mouseEvent.getX() / 16,
                                           mouseEvent.getY() / 16,
                                           mTileToolBox->getSelectedTileFlags());
                }
                
                mDraw = true;
            }
        }
        else if (mMode == FILL)
        {
            if (mouseEvent.getButton() == gcn::MouseEvent::RIGHT)
            {

            }
            else
            mFillX = mouseEvent.getX() - mouseEvent.getX() % 16;
            mFillY = mouseEvent.getY() - mouseEvent.getY() % 16;
            mDraw = true;
        }
    }

     void TileEditor::mouseReleased(gcn::MouseEvent& mouseEvent)
     {
         if (mMode == NORMAL)
         {
            mDraw = false;
         }
         else if (mMode == FILL)
         {
             if (mDraw)
             {
                int x = 0;
                int y = 0;
                int width = 0;
                int height = 0;
    
                if (mFillX > mCurrentMouseX)
                {
                    int currentMouseX =  mCurrentMouseX - mCurrentMouseX % 16;
                    x = currentMouseX / 16;
                    width = (mFillX - currentMouseX) / 16;
                }
                else
                {
                    int currentMouseX =  mCurrentMouseX - mCurrentMouseX % 16 + 16;
                    x = mFillX / 16;
                    width = (currentMouseX - mFillX) / 16;
                }

                if (mFillY > mCurrentMouseY)
                {
                    int currentMouseY =  mCurrentMouseY - mCurrentMouseY % 16;
                    y = currentMouseY / 16;
                    height = (mFillY - currentMouseY) / 16;
                }
                else
                {
                    int currentMouseY =  mCurrentMouseY - mCurrentMouseY % 16 + 16;
                    y = mFillY / 16;
                    height = (currentMouseY - mFillY) / 16;
                }
                
                int dx;
                int dy;
                for (dy = 0; dy < height; dy++)
                {
                    for (dx = 0; dx < width; dx++)
                    {
                        if (mEntityEditMode)
                        {
                            mTileMap->setTileEntity(x + dx, y + dy, mEntitySelector->getSelectedEntity());
                        }
                        else
                        {
                           mTileMap->setTile(x + dx, y + dy, mTileToolBox->getSelectedTileNumber());
                           mTileMap->setTileFlags(x + dx, y + dy, mTileToolBox->getSelectedTileFlags());
                        }
                    }
                }

                mDraw = false;
             }
         }
     }

	 void TileEditor::setEntityEditMode(bool entityEditMode)
	 {
		 mEntityEditMode = entityEditMode;
	 }
}