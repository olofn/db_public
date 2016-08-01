#include "core/operators/rendertotextureoperator.hpp"

RenderToTextureOperator::RenderToTextureOperator()
:d3d9RenderTargetTexture(0),
 d3d9RenderToSurface(0)
{
    
}

RenderToTextureOperator::~RenderToTextureOperator()
{
	if (d3d9RenderTargetTexture != 0)
		d3d9RenderTargetTexture->Release();
    if (d3d9RenderToSurface != 0)
        d3d9RenderToSurface->Release();
}

void RenderToTextureOperator::process(int tick)
{  
   
}

void RenderToTextureOperator::preRender(int tick)
{    
    /*
    if (texture == 0)
        texture = new Texture();
 
    if (d3d9RenderTargetTexture == 0)
    {
        D3DXCreateTexture(globalDirect3DDevice, 
                          512, 
                          512, 
                          1,
                          D3DUSAGE_RENDERTARGET,
                          D3DFMT_A8R8G8B8,
                          D3DPOOL_DEFAULT,
                          &d3d9RenderTargetTexture);

        d3d9RenderTargetTexture->GetSurfaceLevel(0, &d3d9RenderTargetSurface);
        texture->d3d9Texture = d3d9RenderTargetTexture;
    }

    if (d3d9RenderToSurface == 0)
    {
        D3DXCreateRenderToSurface(globalDirect3DDevice, 
		                          512, 
		                          512, 
		                          D3DFMT_A8R8G8B8, 
		                          TRUE, 
		                          D3DFMT_D16, 
		                          &d3d9RenderToSurface);
    }
    
    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->preRender(tick);

    d3d9RenderToSurface->BeginScene(d3d9RenderTargetSurface, NULL);
    globalDirect3DDevice->Clear(0,
                                NULL,
                                D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                                D3DCOLOR_XRGB(0,0,0),
                                1.0f,
                                0);
    globalWorldMatrixStack->Push();
    globalWorldMatrixStack->LoadIdentity();
    globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());
        
    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->render(tick);

    globalWorldMatrixStack->Pop();
    globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());
    d3d9RenderToSurface->EndScene(0);
    */
}

#ifdef DB_EDITOR
void RenderToTextureOperator::deviceLost()
{
    if (d3d9RenderToSurface != 0)
        d3d9RenderToSurface->OnLostDevice();

	if (d3d9RenderTargetTexture != 0)
    {
		d3d9RenderTargetTexture->Release();
        d3d9RenderTargetTexture = 0;
    }
    Operator::deviceLost();
}
#endif