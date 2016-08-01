#include "worldeditor.hpp"

#include "world.hpp"

#include "stringutil.hpp"
#include "resourcehandler.hpp"

namespace nmc
{
    WorldEditor::WorldEditor(RoomSelector* roomSelector)
        : mRoomSelector(roomSelector),
          mDrawingNewRoom(false)
    {
        addMouseListener(this);

        unsigned int i;
        for (i = 0; i < World::getInstance()->getRoomNumberList().size(); i++)
        {
            int roomNumber = World::getInstance()->getRoomNumberList()[i];

            WorldPiece* worldPiece = new WorldPiece(roomNumber);
            mWorldPieces[roomNumber] = worldPiece;
            worldPiece->setX(World::getInstance()->getRoomPosition(roomNumber).x);
            worldPiece->setY(World::getInstance()->getRoomPosition(roomNumber).y);
            worldPiece->addActionListener(this);
            add(worldPiece);
        }

        resizeToContent();

        mNewRoomDialogWidthLabel = new gcn::Label();
        mNewRoomDialogHeightLabel = new gcn::Label();
        mNewRoomDialogNameLabel = new gcn::Label("Name");
        mNewRoomDialogNameTextField = new gcn::TextField();
        mNewRoomDialogNameTextField->setWidth(100);
        mNewRoomDialogNameTextField->setBackgroundColor(gcn::Color(0x000000));
        mNewRoomDialogNameTextField->setForegroundColor(gcn::Color(0xffffff));
        mNewRoomDialogCancelButton = new gcn::Button("Cancel");
        mNewRoomDialogCancelButton->addActionListener(this);
        mNewRoomDialogCancelButton->setBaseColor(gcn::Color(255, 150, 200));
        mNewRoomDialogOKButton = new gcn::Button("OK");
        mNewRoomDialogOKButton->addActionListener(this);
        mNewRoomDialogOKButton->setWidth(mNewRoomDialogCancelButton->getWidth());
        mNewRoomDialogOKButton->setBaseColor(gcn::Color(255, 150, 200));
        mNewRoomDialogWindow = new gcn::Window("New room");
        mNewRoomDialogWindow->setBaseColor(gcn::Color(255, 150, 200));
        mNewRoomDialogWindow->add(mNewRoomDialogWidthLabel, 
                                  10, 
                                  10);
        mNewRoomDialogWindow->add(mNewRoomDialogHeightLabel, 
                                  10, 
                                  20);
        mNewRoomDialogWindow->add(mNewRoomDialogNameLabel, 
                                  10, 
                                  38);
        mNewRoomDialogWindow->add(mNewRoomDialogNameTextField,
                                  50,
                                  38);
        mNewRoomDialogWindow->resizeToContent();
        mNewRoomDialogWindow->add(mNewRoomDialogOKButton,
                                  mNewRoomDialogWindow->getWidth() / 2 
                                   - 5 - mNewRoomDialogOKButton->getWidth(),
                                  60);
        mNewRoomDialogWindow->add(mNewRoomDialogCancelButton,
                                  mNewRoomDialogWindow->getWidth() / 2 + 5,
                                  60);
        mNewRoomDialogWindow->resizeToContent();
        mNewRoomDialogWindow->setMovable(false);
        mNewRoomDialogWindow->setVisible(false);
        mNewRoomDialogWindow->setPosition(320 - mNewRoomDialogWindow->getWidth() / 2,
                                          240 - mNewRoomDialogWindow->getHeight() / 2);
        add(mNewRoomDialogWindow);
    }

    WorldEditor::~WorldEditor()
    {
        std::map<int, WorldPiece*>::iterator it;

        for (it = mWorldPieces.begin(); it != mWorldPieces.end(); it++)
        {
           delete (*it).second;
        }

        delete mNewRoomDialogWindow;
        delete mNewRoomDialogWidthLabel;
        delete mNewRoomDialogHeightLabel;
        delete mNewRoomDialogNameLabel;
        delete mNewRoomDialogNameTextField;
        delete mNewRoomDialogOKButton;
        delete mNewRoomDialogCancelButton;
    }

    void WorldEditor::draw(gcn::Graphics* graphics)
    {
        if (mDrawingNewRoom || mNewRoomDialogWindow->isVisible())
        {
            graphics->setColor(gcn::Color(0xffffff));
            graphics->fillRectangle(gcn::Rectangle(mNewRoomX, mNewRoomY, mNewRoomWidth, mNewRoomHeight));
            graphics->setColor(gcn::Color(0xff0000));
            graphics->drawRectangle(gcn::Rectangle(mNewRoomX, mNewRoomY, mNewRoomWidth, mNewRoomHeight));
        }

        drawChildren(graphics);
    }

    void WorldEditor::action(const gcn::ActionEvent& actionEvent)
    {
        if (actionEvent.getSource() == mNewRoomDialogCancelButton)
        {
            mNewRoomDialogWindow->setVisible(false);
        }
        else if (actionEvent.getSource() ==  mNewRoomDialogOKButton)
        {
            mNewRoomDialogWindow->setVisible(false);
            std::string name = mNewRoomDialogNameTextField->getText();

            if (name.empty())
            {
                return;
            }

            int newRoomNumber = ResourceHandler::getInstance()->newRoomBitmap(mNewRoomWidth / 20,
                                                                              mNewRoomHeight / 15,
                                                                              name);

            WorldPiece* worldPiece = new WorldPiece(newRoomNumber);
            worldPiece->setPosition(mNewRoomX, mNewRoomY);
            worldPiece->addActionListener(this);
            mWorldPieces[newRoomNumber] = worldPiece;
            add(worldPiece);

            mRoomSelector->setSelectedRoom(newRoomNumber);
        }
        else
        {
            WorldPiece* worldPiece = static_cast<WorldPiece*>(actionEvent.getSource());
            mRoomSelector->setSelectedRoom(worldPiece->getRoomNumber());

            resizeToContent();
        }
    }

    void WorldEditor::resizeToContent()
    {
       WidgetListIterator it;

        for (it = mWidgets.begin(); it != mWidgets.end(); it++)
        {
            Widget* widget = *it;

            int xOffset = 0;
            int yOffset = 0;
            int widthOffset = 0;
            int heightOffset = 0;

            if (widget->getX() < 0)
            {
                xOffset = -widget->getX();
            }

            if (widget->getY() < 0)
            {
                yOffset = -widget->getY();
            }
             
            if (widget->getX() + widget->getWidth() > getWidth())
            {
                widthOffset = widget->getX() + widget->getWidth() - getWidth();
            }

            if (widget->getY() + widget->getHeight() > getHeight())
            {
                heightOffset = widget->getY() + widget->getHeight() - getHeight();
            }

            if (xOffset != 0 
                || yOffset != 0 
                || widthOffset != 0
                || heightOffset != 0)
            {
                setSize(getWidth() + widthOffset*2,
                        getHeight() + heightOffset*2);

                WidgetListIterator it2;

                for (it2 = mWidgets.begin(); it2 != mWidgets.end(); it2++)
                {
                    Widget* widgetToMove = *it2;
                    widgetToMove->setPosition(widgetToMove->getX() + xOffset,
                                              widgetToMove->getY() + yOffset);
                }
            }
        }
    }
      
    void WorldEditor::mouseDragged(gcn::MouseEvent& mouseEvent)
    {
        if (mDrawingNewRoom && !mNewRoomDialogWindow->isVisible())
        {
            mNewRoomWidth = mouseEvent.getX() - mNewRoomX;
            mNewRoomHeight = mouseEvent.getY() - mNewRoomY;

            mNewRoomWidth = mNewRoomWidth - mNewRoomWidth % 20;
            mNewRoomHeight = mNewRoomHeight - mNewRoomHeight % 15;
        }
    }

    void WorldEditor::mouseReleased(gcn::MouseEvent& mouseEvent)
    {
        if (mDrawingNewRoom 
            && mNewRoomWidth != 0 
            && mNewRoomHeight != 0
            && !mNewRoomDialogWindow->isVisible())
        {
            mDrawingNewRoom = false;

            if (mNewRoomWidth < 0)
            {
                int oldNewRoomX = mNewRoomX;
                mNewRoomX = mNewRoomX + mNewRoomWidth;
                mNewRoomWidth = -mNewRoomWidth; 
            }
            
            if (mNewRoomHeight < 0)
            {
                int oldNewRoomY = mNewRoomY;
                mNewRoomY = mNewRoomY + mNewRoomHeight;
                mNewRoomHeight = -mNewRoomHeight; 
            }

            mNewRoomDialogWidthLabel->setCaption("Width " + toString(mNewRoomWidth));
            mNewRoomDialogWidthLabel->adjustSize();
            mNewRoomDialogHeightLabel->setCaption("Height " + toString(mNewRoomHeight));
            mNewRoomDialogHeightLabel->adjustSize();
            mNewRoomDialogNameTextField->setText("");
            mNewRoomDialogWindow->setVisible(true);
            moveToTop(mNewRoomDialogWindow);
        }
        else
        {
            mDrawingNewRoom = false;
        }
    }

    void WorldEditor::mousePressed(gcn::MouseEvent& mouseEvent)
    {
        if (mouseEvent.getSource() != this)
        {
            return;
        }

        if (mDrawingNewRoom)
        {
            mDrawingNewRoom = false;
            return;
        }

        if (mouseEvent.getButton() == gcn::MouseEvent::RIGHT)
        {
            if (mWorldPieces.find(mRoomSelector->getSelectedRoom()) == mWorldPieces.end())
            {
                WorldPiece* worldPiece = new WorldPiece(mRoomSelector->getSelectedRoom());
                mWorldPieces[mRoomSelector->getSelectedRoom()] = worldPiece;

                worldPiece->setPosition(mouseEvent.getX() - mouseEvent.getX() % 20, 
                                        mouseEvent.getY() - mouseEvent.getY() % 15);
                worldPiece->addActionListener(this);
                add(worldPiece);
            }
        }
        else if (mouseEvent.getButton() == gcn::MouseEvent::LEFT)
        {
            if (!mNewRoomDialogWindow->isVisible() 
                && getWidgetAt(mouseEvent.getX(), mouseEvent.getY()) == NULL)
            {   
                mDrawingNewRoom = true;

                if (mouseEvent.getX() % 20 < 10)
                {
                    mNewRoomX = mouseEvent.getX() - mouseEvent.getX() % 20;
                }
                else
                {
                    mNewRoomX = mouseEvent.getX() - mouseEvent.getX() % 20 + 20;
                }

                if (mouseEvent.getY() % 15 < 8)
                {
                    mNewRoomY = mouseEvent.getY() - mouseEvent.getY() % 15;
                }
                else
                {
                    mNewRoomY = mouseEvent.getY() - mouseEvent.getY() % 15 + 15;
                }

                mNewRoomWidth = 0;
                mNewRoomHeight = 0;
            }
        }
    }

    void WorldEditor::save()
    {
        std::map<int, WorldPiece*>::iterator it;

        for (it = mWorldPieces.begin(); it != mWorldPieces.end(); it++)
        {
            WorldPiece* worldPiece = it->second;
            World::getInstance()->setRoomPosition(worldPiece->getRoomNumber(), 
                                                  RoomPosition(worldPiece->getX(), worldPiece->getY()));
        }

        World::getInstance()->save();
    }
}