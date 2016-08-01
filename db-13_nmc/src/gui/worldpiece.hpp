#ifndef NMC_WORLDPIECE_HPP
#define NMC_WORLDPIECE_HPP

#include "guichan.hpp"

#include <allegro.h>

namespace nmc
{
    class WorldPiece: public gcn::Widget, public gcn::MouseListener
    {
    public:
        WorldPiece(int roomNumber);
        void draw(gcn::Graphics* graphics);
        void mousePressed(gcn::MouseEvent& mouseEvent);
        void mouseDragged(gcn::MouseEvent& mouseEvent);
        void mouseReleased(gcn::MouseEvent& mouseEvent);
        int getRoomNumber();

    protected:
        int mRoomNumber;
        BITMAP* mRoomBitmap;
        bool mMoving;
        int mDragOffsetX;
        int mDragOffsetY;
    };
}
#endif