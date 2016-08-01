#include "core/operators/modeloperator.hpp"

void ModelOperator::render()
{
    unsigned char cullMode = getByteProperty(0);
    if (cullMode == 0)
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    else if (cullMode == 1)
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    else if (cullMode == 2)
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    unsigned char fillMode = getByteProperty(1);
    if (fillMode == 0)
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    else if (fillMode == 1)
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
    else if (fillMode == 2)
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);

    globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());
    getInput(0)->mesh->render();
}

void ModelOperator::process(int tick)
{
    
}
