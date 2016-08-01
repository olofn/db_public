#ifndef DBSH07_EXTENDEDALLEGROINPUT_HPP
#define DBSH07_EXTENDEDALLEGROINPUT_HPP

#include "guichan/allegro.hpp"

namespace gcn
{
    class ExtendedAllegroInput: public AllegroInput
    {
    public:
        void ExtendedAllegroInput::pollMouseInput();
    };
}

#endif