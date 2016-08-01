#pragma once

#include "core/operator.hpp"

class TwoDimensionalPlaneOperator: public Operator
{
public:
    void render();
    void process(int tick);
   
    D3DXMATRIX identityMatrix;
    D3DXMATRIX projectionMatrix;

#ifdef DB_EDITOR
    void deviceLost();
#endif
};