#pragma once

#include "core/operator.hpp"

class CloneModelOperator: public Operator
{
public:
    void process(int tick);
    void render();
    D3DXMATRIX matrix;
    int clones;
};