#ifndef NMC_TILESELECTOR_HPP
#define NMC_TILESELECTOR_HPP

#include <allegro.h>

#include "guichan.hpp"

namespace nmc
{
    class TileSelector: public gcn::Widget, public gcn::MouseListener
    {
    public:
        TileSelector();
        void draw(gcn::Graphics* graphics);
        void logic();
        void mouseExited(gcn::MouseEvent& mouseEvent);
        void mouseEntered(gcn::MouseEvent& mouseEvent);
        void mouseMoved(gcn::MouseEvent& mouseEvent);
        void mousePressed(gcn::MouseEvent& mouseEvent);
        int getSelectedTile();
        void setSelectedTile(int selectedTile);

    protected:
        BITMAP* mTileSetBitmap;
        int mSelectedTile;
        int mCurrentMouseX;
        int mCurrentMouseY;
        bool mDrawMouseHoverTile;

    };
}
#endif