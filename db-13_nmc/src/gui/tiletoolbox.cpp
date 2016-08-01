#include "gui/tiletoolbox.hpp"

#include "tilemap.hpp"

#include <iostream>

namespace nmc
{
    TileToolBox::TileToolBox()
    {
        mTileSelector = new TileSelector();
        mTileSelector->addActionListener(this);
        mScrollArea = new gcn::ScrollArea(mTileSelector);
        mScrollArea->setSize(128 + 12, 256 + 12);
        mScrollArea->setBackgroundColor(gcn::Color(0x888888));
        mScrollArea->setBaseColor(gcn::Color(255, 150, 200));
        add(mScrollArea);

        mSolidityCheckBox = new ImageCheckBox("icons/solidity.bmp");
        mSolidityCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mSolidityCheckBox->addActionListener(this);
        add(mSolidityCheckBox);
        mSolidityCheckBox->setPosition(0, mScrollArea->getHeight());
        
		mBackgroundLayerCheckBox = new ImageCheckBox("icons/backgroundlayer.bmp");
        mBackgroundLayerCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mBackgroundLayerCheckBox->addActionListener(this);
        add(mBackgroundLayerCheckBox);
        mBackgroundLayerCheckBox->setPosition(mSolidityCheckBox->getWidth(), mScrollArea->getHeight());
        
		mForegroundLayerCheckBox = new ImageCheckBox("icons/foregroundlayer.bmp");
        mForegroundLayerCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mForegroundLayerCheckBox->addActionListener(this);
        add(mForegroundLayerCheckBox);
        mForegroundLayerCheckBox->setPosition(mSolidityCheckBox->getWidth()*2, mScrollArea->getHeight());
        
		mPlatformCheckBox = new ImageCheckBox("icons/platform.bmp");
        mPlatformCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mPlatformCheckBox->addActionListener(this);
        add(mPlatformCheckBox);
        mPlatformCheckBox->setPosition(mSolidityCheckBox->getWidth()*3, mScrollArea->getHeight());
		
		mIceCheckBox = new ImageCheckBox("icons/ice.bmp");
        mIceCheckBox->setBaseColor(gcn::Color(255, 150, 200));
        mIceCheckBox->addActionListener(this);
        add(mIceCheckBox);
        mIceCheckBox->setPosition(mSolidityCheckBox->getWidth()*4, mScrollArea->getHeight());

        setSize(mScrollArea->getWidth(), mScrollArea->getHeight() + mSolidityCheckBox->getHeight());
    }

    TileToolBox::~TileToolBox()
    {
        delete mScrollArea;
        delete mSolidityCheckBox;
        delete mForegroundLayerCheckBox;
        delete mBackgroundLayerCheckBox;
        delete mPlatformCheckBox;
		delete mIceCheckBox;
        delete mTileSelector;
    }

    void TileToolBox::setSelectedTileWithDefaultFlags(int tileNumber)
    {
        mTileSelector->setSelectedTile(tileNumber);

        if (tileNumber > 0)
        {
            mSelectedTileFlags = TileMap::SOLID;
        }
        else
        {
            mSelectedTileFlags = 0;
        }
    
        setSelectedTileFlags(mSelectedTileFlags);   
    }

    void TileToolBox::setSelectedTileNumber(int tileNumber)
    {
        mTileSelector->setSelectedTile(tileNumber); 
    }
        
    void TileToolBox::setSelectedTileFlags(int tileFlags)
    {
        mSelectedTileFlags = tileFlags;
        
        mSolidityCheckBox->setMarked(mSelectedTileFlags & TileMap::SOLID);
        mForegroundLayerCheckBox->setMarked(!(mSelectedTileFlags & TileMap::BACKGROUND));
        mBackgroundLayerCheckBox->setMarked(mSelectedTileFlags & TileMap::BACKGROUND);
        mPlatformCheckBox->setMarked(mSelectedTileFlags & TileMap::PLATFORM);
    }

    int TileToolBox::getSelectedTileNumber()
    {
        return mTileSelector->getSelectedTile();
    }

    int TileToolBox::getSelectedTileFlags()
    {
        return mSelectedTileFlags;
    }

    void TileToolBox::action(const gcn::ActionEvent& actionEvent)
    {
        if (actionEvent.getSource() == mTileSelector)
        {
            setSelectedTileWithDefaultFlags(mTileSelector->getSelectedTile());
        }
        else if (actionEvent.getSource() == mSolidityCheckBox)
        {
            if (mSolidityCheckBox->isMarked())
            {   
                mSelectedTileFlags |= TileMap::SOLID;
            }
            else
            {
                mSelectedTileFlags &= ~TileMap::SOLID; 
            }
             
        }
        else if (actionEvent.getSource() == mBackgroundLayerCheckBox)
        {     
            if (mBackgroundLayerCheckBox->isMarked())
            {   
                mSelectedTileFlags |= TileMap::BACKGROUND;
            }
            else
            {
                mSelectedTileFlags &= ~TileMap::BACKGROUND; 
            }
            
            mForegroundLayerCheckBox->setMarked(!mBackgroundLayerCheckBox->isMarked());
        }
        else if (actionEvent.getSource() == mForegroundLayerCheckBox)
        {
            if (mForegroundLayerCheckBox->isMarked())
            {   
                mSelectedTileFlags &= ~TileMap::BACKGROUND;
            }
            else
            {
                mSelectedTileFlags |= TileMap::BACKGROUND; 
            }

            mBackgroundLayerCheckBox->setMarked(!mForegroundLayerCheckBox->isMarked());
        }
        else if (actionEvent.getSource() == mPlatformCheckBox)
        {
            if (mPlatformCheckBox->isMarked())
            {   
                mSelectedTileFlags &= ~TileMap::SOLID;
				mSelectedTileFlags |= TileMap::PLATFORM; 
            }
            else
            {
				mSelectedTileFlags &= ~TileMap::PLATFORM; 
            }

			mSolidityCheckBox->setMarked(mSelectedTileFlags & TileMap::SOLID);
        }
		else if (actionEvent.getSource() == mIceCheckBox)
        {
            if (mIceCheckBox->isMarked())
            {   
				mSelectedTileFlags |= TileMap::ICE; 
            }
            else
            {
				mSelectedTileFlags &= ~TileMap::ICE; 
            }
        }
    }

    void TileToolBox::draw(gcn::Graphics* graphics)
    {
        drawChildren(graphics);
    }
}
