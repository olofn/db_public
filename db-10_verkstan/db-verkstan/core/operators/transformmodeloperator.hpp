#pragma once

#include "core/operator.hpp"

class TransformModelOperator: public Operator
{
public:
    void process(int tick);
    void render();
    D3DXMATRIX matrix;
};