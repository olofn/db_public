#pragma once

#include "core/operator.hpp"

class BasicMaterialOperator: public Operator
{
public:
    void process(int tick);
    void render();
    D3DMATERIAL9 d3d9Material;
};