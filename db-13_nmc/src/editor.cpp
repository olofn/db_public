#include "editor.hpp"

#include "resourcehandler.hpp"
#include "stringutil.hpp"

namespace nmc
{
    Editor::Editor()
    {
        mGui = new gcn::Gui();
        mAllegroGraphics = new gcn::AllegroGraphics();
        mGui->setGraphics(mAllegroGraphics);
        mAllegroImageLoader = new gcn::AllegroImageLoader();
        gcn::Image::setImageLoader(mAllegroImageLoader);
        mAllegroInput = new gcn::AllegroInput();
        mGui->setInput(mAllegroInput);
        
        mFixedFont = new gcn::ImageFont(ResourceHandler::getInstance()->getRealFilename("gamefont3.bmp"), 32, 126);
		mFixedFont->setGlyphSpacing(1);
        gcn::Widget::setGlobalFont(mFixedFont);

        mTop = new gcn::Container();
        mTop->setSize(640, 480);
        mTop->setOpaque(false);
        mGui->setTop(mTop);

        mNewButton = new ImageButton("icons/new.bmp");
        mNewButton->setBaseColor(gcn::Color(255, 150, 200));
        mNewButton->addActionListener(this);
        mSaveRoomButton = new ImageButton("icons/save.bmp");
        mSaveRoomButton->setBaseColor(gcn::Color(255, 150, 200));
        mSaveRoomButton->addActionListener(this);
        mSaveWorldButton = new ImageButton("icons/save.bmp");
        mSaveWorldButton->setBaseColor(gcn::Color(255, 150, 200));
        mSaveWorldButton->addActionListener(this);
        mRoomCheckBox = new ImageCheckBox("icons/room.bmp");
        mRoomCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mRoomCheckBox->addActionListener(this);
        mRoomCheckBox->setMarked(true);
        mWorldCheckBox = new ImageCheckBox("icons/world.bmp");
        mWorldCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mWorldCheckBox->addActionListener(this);
        mSolidityCheckBox = new ImageCheckBox("icons/solidity.bmp");
        mSolidityCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mSolidityCheckBox->addActionListener(this);
        mBackgroundLayerCheckBox = new ImageCheckBox("icons/backgroundlayer.bmp");
        mBackgroundLayerCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mBackgroundLayerCheckBox->addActionListener(this);
        mBackgroundLayerCheckBox->setMarked(true);
        mForegroundLayerCheckBox = new ImageCheckBox("icons/foregroundlayer.bmp");
        mForegroundLayerCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mForegroundLayerCheckBox->setMarked(true);
        mForegroundLayerCheckBox->addActionListener(this);
        mEntityLayerCheckBox = new ImageCheckBox("icons/entitylayer.bmp");
        mEntityLayerCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mEntityLayerCheckBox->setMarked(true);
        mEntityLayerCheckBox->addActionListener(this);
        mEntityCheckBox = new ImageCheckBox("icons/entity.bmp");
        mEntityCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mEntityCheckBox->setMarked(false);
        mEntityCheckBox->addActionListener(this);
        mTileCheckBox = new ImageCheckBox("icons/tile.bmp");
        mTileCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mTileCheckBox->setMarked(true);
        mTileCheckBox->addActionListener(this);
        mNormalModeCheckBox = new ImageCheckBox("icons/normalmode.bmp");
        mNormalModeCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mNormalModeCheckBox->setMarked(true);
        mNormalModeCheckBox->addActionListener(this);
        mFillModeCheckBox = new ImageCheckBox("icons/fillmode.bmp");
        mFillModeCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mFillModeCheckBox->setMarked(false);
        mFillModeCheckBox->addActionListener(this);

        mToolBarContainer = new gcn::Container();
        mToolBarContainer->setBaseColor(gcn::Color(255, 150, 200));
        
        mToolBarContainer->add(mRoomCheckBox, 0, 0);
        mToolBarContainer->add(mWorldCheckBox, mRoomCheckBox->getWidth(), 0);
        mToolBarContainer->setSize(640, mRoomCheckBox->getHeight());
        mTop->add(mToolBarContainer, 0, 0); 

        mRoomToolBarContainer = new gcn::Container();
        mRoomToolBarContainer->setSize(640 - mRoomCheckBox->getWidth() * 3 , mNewButton->getHeight());
        mRoomToolBarContainer->setBaseColor(gcn::Color(255, 150, 200));
        mRoomToolBarContainer->add(mSaveRoomButton);

        mRoomToolBarContainer->add(mTileCheckBox, mSaveRoomButton->getWidth() * 2, 0);
        mRoomToolBarContainer->add(mEntityCheckBox, mSaveRoomButton->getWidth() * 3, 0);

        mRoomToolBarContainer->add(mSolidityCheckBox, mSaveRoomButton->getWidth()*5, 0);
        mRoomToolBarContainer->add(mBackgroundLayerCheckBox, mSaveRoomButton->getWidth() * 6, 0);
        mRoomToolBarContainer->add(mForegroundLayerCheckBox, mSaveRoomButton->getWidth() * 7, 0);
        mRoomToolBarContainer->add(mEntityLayerCheckBox, mSaveRoomButton->getWidth() * 8, 0);
        mRoomToolBarContainer->add(mNormalModeCheckBox, mSaveRoomButton->getWidth() * 10, 0);
        mRoomToolBarContainer->add(mFillModeCheckBox, mSaveRoomButton->getWidth() * 11, 0);

        mTop->add(mRoomToolBarContainer, mRoomCheckBox->getWidth() * 3, 0); 

        mWorldToolBarContainer = new gcn::Container();
        mWorldToolBarContainer->setSize(640 - mRoomCheckBox->getWidth() * 3 , mNewButton->getHeight());
        mWorldToolBarContainer->setBaseColor(gcn::Color(255, 150, 200));
        mWorldToolBarContainer->add(mSaveWorldButton);
        mWorldToolBarContainer->add(mNewButton, mSaveWorldButton->getWidth(), 0);
        mTop->add(mWorldToolBarContainer, mRoomCheckBox->getWidth() * 3, 0); 
        
        mEntitySelector = new EntitySelector();
        mEntitySelector->setWidth(128);
        mEntitySelector->setBackgroundColor(gcn::Color(0x888888));
        mEntitySelector->setSelectionColor(gcn::Color(205, 100, 150));
        mEntitySelector->addActionListener(this);
        mEntitySelectorScrollArea = new gcn::ScrollArea(mEntitySelector);
        mEntitySelectorScrollArea->setSize(128, 256);
        mEntitySelectorScrollArea->setBackgroundColor(gcn::Color(0x888888));
        mEntitySelectorScrollArea->setBaseColor(gcn::Color(255, 150, 200));
        mEntitySelectorWindow = new gcn::Window("Entities");
        mEntitySelectorWindow->add(mEntitySelectorScrollArea);
        mEntitySelectorWindow->resizeToContent();
        mEntitySelectorWindow->setBaseColor(gcn::Color(255, 150, 200));
        mEntitySelectorWindow->setVisible(false);
        mTop->add(mEntitySelectorWindow, 
                  mTop->getWidth() - mEntitySelectorWindow->getWidth(), 
                  mToolBarContainer->getHeight());

        mTileToolBox = new TileToolBox();
        mTileToolBoxWindow = new gcn::Window("Tiles");
        mTileToolBoxWindow->add(mTileToolBox);
        mTileToolBoxWindow->resizeToContent();
        mTileToolBoxWindow->setBaseColor(gcn::Color(255, 150, 200));
        mTop->add(mTileToolBoxWindow, 
                  mTop->getWidth() - mTileToolBoxWindow->getWidth(),
                  mToolBarContainer->getHeight());

        mTileEditor = new TileEditor(mTileToolBox, mEntitySelector);
        mTileEditor->setSize(640, 480);        
        mTileEditorScrollArea = new gcn::ScrollArea(mTileEditor);
        mTileEditorScrollArea->setSize(640, 480 - mToolBarContainer->getHeight());
        mTileEditorScrollArea->setBaseColor(gcn::Color(255, 150, 200));
        mTileEditorScrollArea->setBackgroundColor(gcn::Color(120, 160, 160));
        mTop->add(mTileEditorScrollArea, 0, mToolBarContainer->getHeight());

        mSaveRoomDialogOKButton = new gcn::Button("OK");
        mSaveRoomDialogOKButton->setBaseColor(gcn::Color(255, 150, 200));
        mSaveRoomDialogOKButton->addActionListener(this);
        mSaveRoomDialogCancelButton = new gcn::Button("Cancel");
        mSaveRoomDialogCancelButton->setBaseColor(gcn::Color(255, 150, 200));
        mSaveRoomDialogCancelButton->addActionListener(this);
        mSaveRoomDialogOKButton->setWidth(mSaveRoomDialogCancelButton->getWidth());
        mSaveRoomDialogTextBox = new gcn::TextBox("Are you sure you want to save and possibly\n" 
                                                  "overwrite any existing saved room?");
		mSaveRoomDialogTextBox->setBorderSize(0);
        mSaveRoomDialogTextBox->setEditable(false);
        mSaveRoomDialogTextBox->setOpaque(false);
        mSaveRoomDialogWindow = new gcn::Window("Are you sure you want to save?");
        mSaveRoomDialogWindow->setBaseColor(gcn::Color(255, 150, 200));
        mSaveRoomDialogWindow->add(mSaveRoomDialogTextBox);
        mSaveRoomDialogWindow->add(mSaveRoomDialogOKButton, 
                                   mSaveRoomDialogTextBox->getWidth() / 2 
                                   - 5 - mSaveRoomDialogOKButton->getWidth(),
                                   mSaveRoomDialogTextBox->getHeight() + 10);
        mSaveRoomDialogWindow->add(mSaveRoomDialogCancelButton,
                                    mSaveRoomDialogTextBox->getWidth() / 2 
                                    + 5 + mSaveRoomDialogOKButton->getWidth() / 2,
                                   mSaveRoomDialogTextBox->getHeight() + 10);
        mSaveRoomDialogWindow->resizeToContent();
        mSaveRoomDialogWindow->setVisible(false);
        mSaveRoomDialogWindow->setMovable(false);
        mTop->add(mSaveRoomDialogWindow, 
                  mTop->getWidth() / 2 - mSaveRoomDialogWindow->getWidth() / 2,
                  mTop->getHeight() / 2 - mSaveRoomDialogWindow->getHeight() / 2);

        mSaveWorldDialogOKButton = new gcn::Button("OK");
        mSaveWorldDialogOKButton->setBaseColor(gcn::Color(255, 150, 200));
        mSaveWorldDialogOKButton->addActionListener(this);
        mSaveWorldDialogCancelButton = new gcn::Button("Cancel");
        mSaveWorldDialogCancelButton->setBaseColor(gcn::Color(255, 150, 200));
        mSaveWorldDialogCancelButton->addActionListener(this);
        mSaveWorldDialogOKButton->setWidth(mSaveWorldDialogCancelButton->getWidth());
        mSaveWorldDialogTextBox = new gcn::TextBox("Are you sure you want to save and possibly\n" 
                                                  "overwrite any existing saved World?");
		mSaveWorldDialogTextBox->setBorderSize(0);
        mSaveWorldDialogTextBox->setEditable(false);
        mSaveWorldDialogTextBox->setOpaque(false);

        mSaveWorldDialogWindow = new gcn::Window("Are you sure you want to save?");
        mSaveWorldDialogWindow->setBaseColor(gcn::Color(255, 150, 200));
        mSaveWorldDialogWindow->add(mSaveWorldDialogTextBox);
        mSaveWorldDialogWindow->add(mSaveWorldDialogOKButton, 
                                   mSaveWorldDialogTextBox->getWidth() / 2 
                                   - 5 - mSaveWorldDialogOKButton->getWidth(),
                                   mSaveWorldDialogTextBox->getHeight() + 10);
        mSaveWorldDialogWindow->add(mSaveWorldDialogCancelButton,
                                    mSaveWorldDialogTextBox->getWidth() / 2 
                                    + 5 + mSaveWorldDialogOKButton->getWidth() / 2,
                                   mSaveWorldDialogTextBox->getHeight() + 10);
        mSaveWorldDialogWindow->resizeToContent();
        mSaveWorldDialogWindow->setVisible(false);
        mSaveWorldDialogWindow->setMovable(false);
        mTop->add(mSaveWorldDialogWindow, 
                  mTop->getWidth() / 2 - mSaveWorldDialogWindow->getWidth() / 2,
                  mTop->getHeight() / 2 - mSaveWorldDialogWindow->getHeight() / 2);

        mNewRoomDialogWidthLabel = new gcn::Label("Width");
        mNewRoomDialogHeightLabel = new gcn::Label("Height");
        mNewRoomDialogNameLabel = new gcn::Label("Name");
        mNewRoomDialogWidthTextField = new IntTextField();
        mNewRoomDialogWidthTextField->setWidth(20);
        mNewRoomDialogWidthTextField->setBackgroundColor(gcn::Color(0x000000));
        mNewRoomDialogWidthTextField->setForegroundColor(gcn::Color(0xffffff));
        mNewRoomDialogHeightTextField = new IntTextField();
        mNewRoomDialogHeightTextField->setWidth(20);
        mNewRoomDialogHeightTextField->setBackgroundColor(gcn::Color(0x000000));
        mNewRoomDialogHeightTextField->setForegroundColor(gcn::Color(0xffffff));
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
        mNewRoomDialogWindow->add(mNewRoomDialogWidthTextField, 
                                  50, 
                                  10);
        mNewRoomDialogWindow->add(mNewRoomDialogHeightLabel, 
                                  10, 
                                  30);
        mNewRoomDialogWindow->add(mNewRoomDialogHeightTextField, 
                                  50, 
                                  30);
        mNewRoomDialogWindow->add(mNewRoomDialogNameLabel, 
                                  10, 
                                  48);
        mNewRoomDialogWindow->add(mNewRoomDialogNameTextField,
                                  50,
                                  48);
        mNewRoomDialogWindow->resizeToContent();
        mNewRoomDialogWindow->add(mNewRoomDialogOKButton,
                                  mNewRoomDialogWindow->getWidth() / 2 
                                   - 5 - mNewRoomDialogOKButton->getWidth(),
                                  70);
        mNewRoomDialogWindow->add(mNewRoomDialogCancelButton,
                                    mNewRoomDialogWindow->getWidth() / 2 + 5,
                                   70);
        mNewRoomDialogWindow->resizeToContent();
        mNewRoomDialogWindow->setMovable(false);
        mNewRoomDialogWindow->setVisible(false);
        mTop->add(mNewRoomDialogWindow,
                  mTop->getWidth() / 2 - mNewRoomDialogWindow->getWidth() / 2,
                  mTop->getHeight() / 2 - mNewRoomDialogWindow->getHeight() / 2);
        
        mRoomSelector = new RoomSelector();
        mWorldEditor = new WorldEditor(mRoomSelector);
        mWorldEditor->setSize(640, 480);
        mWorldEditor->setBaseColor(gcn::Color(120, 160, 160));
        mWorldEditorScrollArea = new gcn::ScrollArea(mWorldEditor);
        mWorldEditorScrollArea->setSize(640, 480 - mToolBarContainer->getHeight());
        mWorldEditorScrollArea->setVisible(false);
        mWorldEditorScrollArea->setBaseColor(gcn::Color(255, 150, 200));
        mWorldEditorScrollArea->setBackgroundColor(gcn::Color(120, 160, 160));
        mTop->add(mWorldEditorScrollArea, 0, mToolBarContainer->getHeight());

        mRoomSelector->setWidth(128);
        mRoomSelector->setBackgroundColor(gcn::Color(0x000000));
        mRoomSelector->setSelectionColor(gcn::Color(205, 100, 150));
        mRoomSelector->addActionListener(this);
        mRoomSelectorScrollArea = new gcn::ScrollArea(mRoomSelector);
        mRoomSelectorScrollArea->setSize(128, 256);
        mRoomSelectorScrollArea->setBackgroundColor(gcn::Color(0x000000));
        mRoomSelectorScrollArea->setBaseColor(gcn::Color(255, 150, 200));
        mRoomSelectorWindow = new gcn::Window("Rooms");
        mRoomSelectorWindow->add(mRoomSelectorScrollArea);
        mRoomSelectorWindow->resizeToContent();
        mRoomSelectorWindow->setBaseColor(gcn::Color(255, 150, 200));
        mTop->add(mRoomSelectorWindow, 
                  mTop->getWidth() - mRoomSelectorWindow->getWidth(), 
                  mToolBarContainer->getHeight());

        mTop->moveToTop(mTileToolBoxWindow);
        mTop->moveToTop(mEntitySelectorWindow);
        
        setState(WORLD);
    }

    Editor::~Editor()
    {
        delete mWorldEditor;

        delete mEntitySelector;
        delete mEntitySelectorScrollArea;
        delete mEntitySelectorWindow;

        delete mRoomSelector;
        delete mRoomSelectorScrollArea;
        delete mRoomSelectorWindow;

        delete mNewRoomDialogWindow;
        delete mNewRoomDialogWidthLabel;
        delete mNewRoomDialogHeightLabel;
        delete mNewRoomDialogNameLabel;
        delete mNewRoomDialogWidthTextField;
        delete mNewRoomDialogHeightTextField;
        delete mNewRoomDialogNameTextField;
        delete mNewRoomDialogOKButton;
        delete mNewRoomDialogCancelButton;

        delete mSaveRoomDialogTextBox;
        delete mSaveRoomDialogOKButton;
        delete mSaveRoomDialogCancelButton;
        delete mSaveRoomDialogWindow;

        delete mSaveWorldDialogTextBox;
        delete mSaveWorldDialogOKButton;
        delete mSaveWorldDialogCancelButton;
        delete mSaveWorldDialogWindow;

        delete mTileToolBoxWindow;
        delete mTileToolBox;

        delete mNewButton;
        delete mSaveRoomButton;
        delete mSaveWorldButton;
        delete mRoomCheckBox;
        delete mWorldCheckBox;
        delete mSolidityCheckBox;
        delete mBackgroundLayerCheckBox;
        delete mForegroundLayerCheckBox;
        delete mEntityLayerCheckBox;
        delete mEntityCheckBox;
        delete mTileCheckBox;
        delete mNormalModeCheckBox;
        delete mFillModeCheckBox;
        delete mRoomToolBarContainer;
        delete mWorldToolBarContainer;
        delete mToolBarContainer;

        delete mTileEditor;
        delete mTileEditorScrollArea;

        delete mTop;

        delete mFixedFont;
        delete mAllegroImageLoader;
        delete mAllegroInput;
        delete mAllegroGraphics;
        delete mGui;
    }

    void Editor::save()
    {
        mTileEditor->save();
        mWorldEditor->save();
    }

    void Editor::logic()
    {
        mGui->logic();
    }

    void Editor::draw(BITMAP* dest)
    {
        mAllegroGraphics->setTarget(dest);
        mGui->draw();
    }

    void Editor::setRoomNumber(int roomNumber)
    {
        mRoomNumber = roomNumber;
        mTileEditor->setRoom(roomNumber);
    }

    void Editor::action(const gcn::ActionEvent& actionEvent)
    {   
        if (actionEvent.getSource() == mNewButton)
        {
            mNewRoomDialogWindow->setVisible(true);
            mNewRoomDialogWindow->requestModalFocus();
            mNewRoomDialogWidthTextField->setText("1");
            mNewRoomDialogHeightTextField->setText("1");
            mTop->moveToTop(mNewRoomDialogWindow);
        }
        else if (actionEvent.getSource() == mSaveRoomButton)
        {
            mSaveRoomDialogWindow->setVisible(true);
            mSaveRoomDialogWindow->requestModalFocus();
            mTop->moveToTop(mSaveRoomDialogWindow);
        }
        else if (actionEvent.getSource() == mSaveWorldButton)
        {
            mSaveWorldDialogWindow->setVisible(true);
            mSaveWorldDialogWindow->requestModalFocus();
            mTop->moveToTop(mSaveWorldDialogWindow);
        }
        else if (actionEvent.getSource() == mRoomCheckBox)
        {
            if (mRoomCheckBox->isMarked())
            {
                setState(ROOM);
                setRoomNumber(mRoomSelector->getSelectedRoom());
            }
            else
            {
                setState(WORLD);
                mRoomSelector->setSelectedRoom(mRoomNumber);
            }
        }
        else if (actionEvent.getSource() == mWorldCheckBox)
        {
            if (mWorldCheckBox->isMarked())
            {
                setState(WORLD);
                mRoomSelector->setSelectedRoom(mRoomNumber);
            }
            else
            {
                setState(ROOM);
                setRoomNumber(mRoomSelector->getSelectedRoom());
            }
        }
        else if (actionEvent.getSource() == mSolidityCheckBox)
        {
            mTileEditor->setShowSolidity(mSolidityCheckBox->isMarked());
        }
        else if (actionEvent.getSource() == mForegroundLayerCheckBox)
        {
            mTileEditor->setShowForegroundLayer(mForegroundLayerCheckBox->isMarked());
        }
        else if (actionEvent.getSource() == mBackgroundLayerCheckBox)
        {
            mTileEditor->setShowBackgroundLayer(mBackgroundLayerCheckBox->isMarked());
        }
        else if (actionEvent.getSource() == mEntityCheckBox)
        {
            mEntitySelectorWindow->setVisible(mEntityCheckBox->isMarked());
            mTileToolBoxWindow->setVisible(!mEntityCheckBox->isMarked());
            mTileCheckBox->setMarked(!mEntityCheckBox->isMarked());
			mTileEditor->setEntityEditMode(mEntityCheckBox->isMarked());
        }
        else if (actionEvent.getSource() == mTileCheckBox)
        {
            mEntitySelectorWindow->setVisible(!mTileCheckBox->isMarked());
            mTileToolBoxWindow->setVisible(mTileCheckBox->isMarked());
            mEntityCheckBox->setMarked(!mTileCheckBox->isMarked());
			mTileEditor->setEntityEditMode(!mTileCheckBox->isMarked());
        }
        else if (actionEvent.getSource() == mNormalModeCheckBox)
        {
            if (mNormalModeCheckBox->isMarked())
            {
                mTileEditor->setMode(TileEditor::NORMAL);
            }
            else
            {
                mTileEditor->setMode(TileEditor::FILL);
            }

            mFillModeCheckBox->setMarked(!mNormalModeCheckBox->isMarked());
        }
        else if (actionEvent.getSource() == mFillModeCheckBox)
        {
            if (mFillModeCheckBox->isMarked())
            {
                mTileEditor->setMode(TileEditor::FILL);
            }
            else
            {
                mTileEditor->setMode(TileEditor::NORMAL);
            }

            mNormalModeCheckBox->setMarked(!mFillModeCheckBox->isMarked());
        }
        else if (actionEvent.getSource() == mEntityLayerCheckBox)
        {
            mTileEditor->setShowEntities(mEntityLayerCheckBox->isMarked());
        }
        else if (actionEvent.getSource() == mSaveRoomDialogOKButton)
        {
            mSaveRoomDialogWindow->setVisible(false);
            mSaveRoomDialogWindow->releaseModalFocus();
            mTileEditor->save();
        }
        else if (actionEvent.getSource() == mSaveRoomDialogCancelButton)
        {
            mSaveRoomDialogWindow->setVisible(false);
            mSaveRoomDialogWindow->releaseModalFocus();
        }
        else if (actionEvent.getSource() == mSaveWorldDialogOKButton)
        {
            mSaveWorldDialogWindow->setVisible(false);
            mSaveWorldDialogWindow->releaseModalFocus();
            mWorldEditor->save();
        }
        else if (actionEvent.getSource() == mSaveWorldDialogCancelButton)
        {
            mSaveWorldDialogWindow->setVisible(false);
            mSaveWorldDialogWindow->releaseModalFocus();
        }
        else if (actionEvent.getSource() == mNewRoomDialogOKButton)
        {
            mNewRoomDialogWindow->setVisible(false);
            mNewRoomDialogWindow->releaseModalFocus();

            int width = mNewRoomDialogWidthTextField->getIntValue();
            int height = mNewRoomDialogHeightTextField->getIntValue();
            std::string name = mNewRoomDialogNameTextField->getText();

            if (name.empty() || width == 0 || height == 0)
            {
                return;
            }

            int newRoomNumber = ResourceHandler::getInstance()->newRoomBitmap(width,
                                                                              height,
                                                                              name);
            setRoomNumber(newRoomNumber);
        }
        else if (actionEvent.getSource() == mNewRoomDialogCancelButton)
        {
            mNewRoomDialogWindow->setVisible(false);
            mNewRoomDialogWindow->releaseModalFocus();
        }
        else if (actionEvent.getSource() == mRoomSelector)
        {
            setRoomNumber(mRoomSelector->getSelectedRoom());
        }
    }

    int Editor::getRoomNumber()
    {
        return mRoomNumber;
    }

    void Editor::setState(State state)
    {
        if (state == ROOM)
        {
            mTileEditorScrollArea->setVisible(true);
            mEntitySelectorWindow->setVisible(mEntityCheckBox->isMarked());
            mTileToolBoxWindow->setVisible(!mEntityCheckBox->isMarked());
            mRoomToolBarContainer->setVisible(true);
            mRoomSelectorWindow->setVisible(false);
            mWorldEditorScrollArea->setVisible(false);
            mWorldToolBarContainer->setVisible(false);
            mWorldCheckBox->setMarked(false);
            mRoomCheckBox->setMarked(true);
        }
        else if (state == WORLD)
        {
            mTileEditorScrollArea->setVisible(false);
            mEntitySelectorWindow->setVisible(false);
            mTileToolBoxWindow->setVisible(false);
            mRoomToolBarContainer->setVisible(false);
            mRoomSelectorWindow->setVisible(true);
            mWorldEditorScrollArea->setVisible(true);
            mWorldToolBarContainer->setVisible(true);
            mWorldCheckBox->setMarked(true);
            mRoomCheckBox->setMarked(false);
        }
    }
}