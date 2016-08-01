#include "core/operators/normalsshaderoperator.hpp"
#include "core/shaders/normalsshader.hpp"

NormalsShaderOperator::NormalsShaderOperator()
:d3d9Effect(0)
{

}

void NormalsShaderOperator::render()
{
    D3DXMATRIX projMatrix;
    D3DXMATRIX viewMatrix;
    D3DXMATRIX worldMatrix = *globalWorldMatrixStack->GetTop();
    globalDirect3DDevice->GetTransform(D3DTS_PROJECTION, &projMatrix);
    globalDirect3DDevice->GetTransform(D3DTS_VIEW, &viewMatrix);
    D3DXMATRIX worldViewProj = worldMatrix * viewMatrix * projMatrix;

    d3d9Effect->SetMatrix("WorldViewProjection", &worldViewProj);
    d3d9Effect->SetTechnique("Simple");
    UINT passes;
    d3d9Effect->Begin(&passes, 0);

    for (int i = 0; i < passes; i++) 
    {
       d3d9Effect->BeginPass(i);
       for (int i = 0; i < numberOfInputs; i++)
            getInput(i)->render();
        d3d9Effect->EndPass();
    }
    
    d3d9Effect->End();
}

void NormalsShaderOperator::process(int tick)
{
    if (d3d9Effect == 0)
       D3DXCreateEffect(globalDirect3DDevice, 
                        normalsshader, 
                        sizeof(normalsshader), 
                         NULL, 
                         NULL, 
                         NULL, 
                         NULL,
                         &d3d9Effect,
                         NULL); 
}

#ifdef DB_EDITOR
void NormalsShaderOperator::deviceLost()
{
	Operator::deviceLost();
	
    if (d3d9Effect != 0)
    {
        d3d9Effect->Release();
        d3d9Effect = 0;
        setDirty(true);
    }
}
#endif
