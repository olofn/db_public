#pragma once

#include "core/operator.hpp"

class CameraOperator: public Operator
{
public:
    void process(int tick);
    void render();
    D3DXMATRIX projectionMatrix;
    D3DXMATRIX viewMatrix;
};