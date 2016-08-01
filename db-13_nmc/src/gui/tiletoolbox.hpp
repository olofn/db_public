#ifndef NMC_TILETOOLBOX_HPP
#define NMC_TILETOOLBOX_HPP

#include "guichan.hpp"
#include "gui/tileselector.hpp"
#include "gui/imagecheckbox.hpp"

namespace nmc
{
    class TileToolBox: public gcn::BasicContainer, public gcn::ActionListener
    {
    public:
        TileToolBox();
        ~TileToolBox();
        void setSelectedTileWithDefaultFlags(int tileNumber);
        void setSelectedTileNumber(int tileNumber);
        void setSelectedTileFlags(int tileFlags);
        int getSelectedTileNumber();
        int getSelectedTileFlags();
        void action(const gcn::ActionEvent& actionEvent);
        void draw(gcn::Graphics* graphics);

    protected:
        int mSelectedTileFlags;

        gcn::ScrollArea* mScrollArea;
        TileSelector* mTileSelector;
        ImageCheckBox* mSolidityCheckBox;
        ImageCheckBox* mBackgroundLayerCheckBox;
        ImageCheckBox* mForegroundLayerCheckBox;
        ImageCheckBox* mPlatformCheckBox;
		ImageCheckBox* mIceCheckBox;
    };
}

#endif