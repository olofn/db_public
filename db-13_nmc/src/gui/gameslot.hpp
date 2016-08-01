#ifndef NMC_GAMESLOT_HPP
#define NMC_GAMESLOT_HPP

#include "guichan.hpp"
#include "gui/decoratedcontainer.hpp"

namespace nmc
{
    class GameSlot: public DecoratedContainer
    {
    public:
        GameSlot();
        ~GameSlot();
        void update(int slotNumber);
    protected:
        gcn::Label* mAreaLabel;
        gcn::ImageFont* mFont;
    };
}
#endif

