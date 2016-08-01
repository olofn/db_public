#include "core/operators/normalmapoperator.hpp"

NormalMapOperator::NormalMapOperator()
:normalMapTexture(0)
{
}

void NormalMapOperator::process(int tick)
{
    if (texture == 0)
        texture = new Texture();

    if (normalMapTexture == 0)
        normalMapTexture = new Texture();

    D3DXComputeNormalMap(normalMapTexture->getD3D9Texture(),
                         getInput(0)->texture->getD3D9Texture(),
                         NULL,
                         0,
                         D3DX_CHANNEL_RED,
                         getByteProperty(0));
    LPDIRECT3DSURFACE9 surface;
    normalMapTexture->getD3D9Texture()->GetSurfaceLevel(0, &surface);
    D3DXLoadSurfaceFromSurface(texture->d3d9Surface, 
                               NULL, 
                               NULL, 
                               surface, 
                               NULL, 
                               NULL, 
                               D3DX_FILTER_NONE,
                               0);
    normalMapTexture->getD3D9Texture()->Release();
    texture->setDirty();
}

#ifdef DB_EDITOR
void NormalMapOperator::deviceLost()
{
    Operator::deviceLost();
    if (normalMapTexture != 0)
    {
        delete normalMapTexture;
        normalMapTexture = 0;
    }
}
#endif
