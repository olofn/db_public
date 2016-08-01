#include "core/operators/basicmaterialoperator.hpp"

void BasicMaterialOperator::render()
{
    Operator* textureOperator = getInput(1);

    globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, getByteProperty(4));
   
    unsigned char textureAddress = getByteProperty(5);
    if (textureAddress == 0)
    {
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
    }
    else if (textureAddress == 1)
    {
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_MIRROR);
    }
    else if (textureAddress == 2)
    {
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_BORDER);
    }
    else if (textureAddress == 3)
    {
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_CLAMP);
    }

    unsigned char textureFiltiring = getByteProperty(6);
    if (textureFiltiring == 0)
    {
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
    }
    else if (textureFiltiring == 1)
    {   
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_CONVOLUTIONMONO);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_CONVOLUTIONMONO);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_CONVOLUTIONMONO);
    }
    else if (textureFiltiring == 2)
    {
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_GAUSSIANQUAD);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_GAUSSIANQUAD);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_GAUSSIANQUAD);
    }
    else if (textureFiltiring == 3)
    {
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
    }
    else if (textureFiltiring == 4)
    {
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_NONE);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_NONE);
        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_NONE);
    }

    globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, !getByteProperty(7)); 

	globalDirect3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	globalDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    if (textureOperator != 0)
        globalDirect3DDevice->SetTexture(0, textureOperator->texture->getD3D9Texture());

    globalDirect3DDevice->SetMaterial(&d3d9Material);
    globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

    globalDirect3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_PHONG); 
	globalDirect3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
    globalDirect3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	globalDirect3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

    getInput(0)->render();
    globalDirect3DDevice->SetTexture(0, 0);	

	globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); 
}

void BasicMaterialOperator::process(int tick)
{
    ZeroMemory(&d3d9Material, sizeof(d3d9Material));
    d3d9Material.Diffuse = getColorProperty(0);
    d3d9Material.Specular = getColorProperty(1);
    d3d9Material.Ambient = getColorProperty(2);
    d3d9Material.Power = getFloatProperty(3);
}
