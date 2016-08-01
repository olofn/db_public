#pragma once

#include "core/operator.hpp"

class RenderToTextureOperator: public Operator
{
public:
    RenderToTextureOperator();
    ~RenderToTextureOperator();
    void preRender(int tick);
    void process(int tick);
    LPDIRECT3DSURFACE9 d3d9RenderTargetSurface;
    LPDIRECT3DTEXTURE9 d3d9RenderTargetTexture;
    LPD3DXRENDERTOSURFACE d3d9RenderToSurface;

#ifdef DB_EDITOR
    void deviceLost();
#endif
};