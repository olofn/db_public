#pragma once

#include "core/operator.hpp"

class CloudsOperator: public Operator
{
public:
    void process(int tick);
    D3DXCOLOR color1;
    D3DXCOLOR color2;
    void divideGrid(int x, int y, int width, int height, float c1, float c2, float c3, float c4, int scale);
};