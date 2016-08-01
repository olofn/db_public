#ifndef NMC_ENTITYSELECTOR_HPP
#define NMC_ENTITYSELECTOR_HPP

#include <allegro.h>

#include "guichan.hpp"

namespace nmc
{
    class EntitySelector: public gcn::Widget, public gcn::MouseListener
    {
    public:
        EntitySelector();
        void draw(gcn::Graphics* graphics);
        void logic();
        void mouseExited(gcn::MouseEvent& mouseEvent);
        void mouseEntered(gcn::MouseEvent& mouseEvent);
        void mouseMoved(gcn::MouseEvent& mouseEvent);
        void mousePressed(gcn::MouseEvent& mouseEvent);
        int getSelectedEntity();
        void setSelectedEntity(int selectedEntity);

    protected:
        BITMAP* mEntitySetBitmap;
        int mSelectedEntity;
        int mCurrentMouseX;
        int mCurrentMouseY;
        bool mDrawMouseHoverTile;

    };
}
#endif