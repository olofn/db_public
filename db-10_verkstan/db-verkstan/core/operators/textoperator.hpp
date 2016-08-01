#pragma once

#include "core/operator.hpp"

class TextOperator: public Operator
{
public:
    TextOperator();
    ~TextOperator();
    void process(int tick);
    LPDIRECT3DTEXTURE9 d3d9RenderTargetTexture;

#ifdef DB_EDITOR
    void deviceLost();
#endif
};