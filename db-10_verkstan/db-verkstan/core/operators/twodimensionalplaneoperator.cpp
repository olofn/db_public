#include "core/operators/twodimensionalplaneoperator.hpp"

struct TwoDimensionalVertex
{
    float x, y, z;
    DWORD color;
    float u, v;
};

void TwoDimensionalPlaneOperator::render()
{    
    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->render();

    Texture* inputTexture = 0;
    
    if (getInput(0) != 0)
        inputTexture = getInput(0)->texture;

    D3DXMATRIX lastViewMatrix;
    D3DXMATRIX lastProjectionMatrix;
    globalDirect3DDevice->GetTransform(D3DTS_VIEW, &lastViewMatrix);
    globalDirect3DDevice->GetTransform(D3DTS_PROJECTION, &lastProjectionMatrix);
    globalDirect3DDevice->SetTransform(D3DTS_VIEW, &identityMatrix);
    globalDirect3DDevice->SetTransform(D3DTS_WORLD, &identityMatrix);
    globalDirect3DDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
    DWORD lastLightning;
    globalDirect3DDevice->GetRenderState(D3DRS_LIGHTING, &lastLightning); 
    globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    D3DXCOLOR color = getColorProperty(0);
    color.a = getByteProperty(1) / 255.0f;

    float x = getFloatProperty(2);
    float width = getFloatProperty(3);
    float y = getFloatProperty(4);
    float height = getFloatProperty(5);
    float z = getFloatProperty(6);
    float uOffset = getFloatProperty(7);
    float vOffset = getFloatProperty(8);
    float uScale = getFloatProperty(9);
    float vScale = getFloatProperty(10);

    float ratio = (globalWindowHeight / (float)globalWindowWidth) / 4.0f;
    float u1 = -ratio + uOffset;
    float u2 = 1.0f + ratio + uOffset;
    float v1 = vOffset;
    float v2 = 1.0f + vOffset;

    if (getByteProperty(11) == 1)
    {
        u1 = 0.0f;
        u2 = 1.0f;
        v1 = 0.0f;
        v2 = 1.0f;
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
    }
    else
    {
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_BORDER);
    }

    u1 *= uScale;
    u2 *= uScale;
    v1 *= vScale;
    v2 *= vScale;

    TwoDimensionalVertex quad[4];
    quad[0].x = x; 
    quad[0].y = y; 
    quad[0].z = z;
    quad[0].u = u1; 
    quad[0].v = v1; 
    quad[0].color = color;
    
    quad[1].x = x + width; 
    quad[1].y = y; 
    quad[1].z = z;
    quad[1].u = u2; 
    quad[1].v = v1; 
    quad[1].color = color;

    quad[2].x = x + width; 
    quad[2].y = y + height; 
    quad[2].z = z;
    quad[2].u = u2;
    quad[2].v = v2; 
    quad[2].color = color;

    quad[3].x = x; 
    quad[3].y = y + height; 
    quad[3].z = z;
    quad[3].u = u1; 
    quad[3].v = v2; 
    quad[3].color = color;

    DWORD oldFVF;
    globalDirect3DDevice->GetFVF(&oldFVF);
    globalDirect3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1);
    
    globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);     
    globalDirect3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
    globalDirect3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
    globalDirect3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);

    if (inputTexture != 0)
        globalDirect3DDevice->SetTexture(0, inputTexture->getD3D9Texture());

    globalDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &quad, sizeof(TwoDimensionalVertex));
    globalDirect3DDevice->SetTexture(0, 0);
    globalDirect3DDevice->SetFVF(oldFVF);

    globalDirect3DDevice->SetTransform(D3DTS_PROJECTION, &lastProjectionMatrix);
    globalDirect3DDevice->SetTransform(D3DTS_VIEW, &lastViewMatrix);
    globalDirect3DDevice->GetRenderState(D3DRS_LIGHTING, &lastLightning); 
}

void TwoDimensionalPlaneOperator::process(int tick)
{
    D3DXMatrixIdentity(&identityMatrix);
    D3DXMatrixOrthoOffCenterLH(&projectionMatrix, 
                               0.0f, 
                               1.0f, 
                               1.0f, 
                               0.0f, 
                               -1.0f, 
                               1.0f);
}

#ifdef DB_EDITOR
void TwoDimensionalPlaneOperator::deviceLost()
{
    Operator::deviceLost();
    setDirty(true);
}
#endif
