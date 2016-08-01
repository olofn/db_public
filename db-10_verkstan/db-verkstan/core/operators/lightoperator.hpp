#pragma once

#include "core/operator.hpp"

class LightOperator: public Operator
{
public:
    void process(int tick);
    void render();
    D3DLIGHT9 d3dLight;
};