#ifndef NMC_INTTEXTFIELD_HPP
#define NMC_INTTEXTFIELD_HPP

#include "guichan.hpp"

namespace nmc
{
    class IntTextField: public gcn::TextField
    {
    public:
        int getIntValue();
        void keyPressed(gcn::KeyEvent& keyEvent);
    };
}
#endif