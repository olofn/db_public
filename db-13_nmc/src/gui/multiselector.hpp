#ifndef NMC_MULTISELECTOR_HPP
#define NMC_MULTISELECTOR_HPP

#include "guichan.hpp"

#include <vector>

namespace nmc
{
    class MultiSelector: public gcn::Widget, public gcn::KeyListener
    {
    public:
        MultiSelector();
        ~MultiSelector();
        void draw(gcn::Graphics* graphics);
        void logic();
        void addSelection(int x, int y);
        int getSelectorHeight();
        int getSelectorWidth();
        void keyPressed(gcn::KeyEvent& keyEvent);
        int getSelected();
        void setSelected(int selected);

    protected:
        class Selection
        {
        public:
            Selection(int x_, int y_)
                :x(x_), y(y_)
            {}
            int x;
            int y;
        };

        std::vector<Selection> mSelections;
        int mCurrentSelection;
        gcn::Image* mSelectorImage;
        int mFrameCounter;
    };
}

#endif