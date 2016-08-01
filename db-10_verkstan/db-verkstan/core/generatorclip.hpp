#pragma once

#include "core/clip.hpp"

class GeneratorClip: public Clip
{
public:
    float getValue(int tick);
    int period;
    unsigned char type;
};