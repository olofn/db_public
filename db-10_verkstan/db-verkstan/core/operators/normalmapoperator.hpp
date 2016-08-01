#pragma once

#include "core/operator.hpp"

class NormalMapOperator: public Operator
{
public:
    NormalMapOperator();
    void process(int tick);
    Texture* normalMapTexture;
#ifdef DB_EDITOR
    void deviceLost();
#endif
};