#pragma once

#include "core/operator.hpp"

class NormalsShaderOperator: public Operator
{
public:
    NormalsShaderOperator();
    void render();
    void process(int tick);
    LPD3DXEFFECT d3d9Effect;

#ifdef DB_EDITOR
    void deviceLost();
#endif
};