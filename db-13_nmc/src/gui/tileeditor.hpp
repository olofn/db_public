#ifndef NMC_TILEEDITOR_HPP
#define NMC_TILEEDITOR_HPP

#include "guichan.hpp"
#include "tilemap.hpp"
#include "gui/entityselector.hpp"
#include "gui/tiletoolbox.hpp"

namespace nmc
{
    class TileEditor: public gcn::Widget, public gcn::MouseListener
    {
    public:
        enum Mode
        {
            NORMAL,
            FILL
        };

        TileEditor(TileToolBox* tileToolBox,
                   EntitySelector* entitySelector);
        ~TileEditor();
        void save();
        void draw(gcn::Graphics* graphics);
        void setRoom(int room);
        void mouseMoved(gcn::MouseEvent& mouseEvent);
        void mouseDragged(gcn::MouseEvent& mouseEvent);
        void mousePressed(gcn::MouseEvent& mouseEvent);
        void mouseReleased(gcn::MouseEvent& mouseEvent);
        void setShowSolidity(bool showSolidity);
        void setShowBackgroundLayer(bool showBackgroundLayer);
        void setShowForegroundLayer(bool showForegroundLayer);
        void setShowEntities(bool showEntitites);
		void setEntityEditMode(bool entityEditMode);
        void setMode(Mode mode);

       

    protected:
        TileMap* mTileMap;
        bool mShowMouseHoverTile;
        bool mDraw;
        bool mShowEntities;
		bool mEntityEditMode;
        int mCurrentMouseX;
        int mCurrentMouseY;
        int mFillX;
        int mFillY;
        TileToolBox* mTileToolBox;
        EntitySelector* mEntitySelector;
        Mode mMode;
    };
}
#endif