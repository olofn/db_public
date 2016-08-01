#include "core/operators/textoperator.hpp"

TextOperator::TextOperator()
:d3d9RenderTargetTexture(0)
{
    
}

TextOperator::~TextOperator()
{
	if (d3d9RenderTargetTexture != 0)
		d3d9RenderTargetTexture->Release();
}

void TextOperator::process(int tick)
{   
    if (d3d9RenderTargetTexture == 0)
        D3DXCreateTexture(globalDirect3DDevice, 
                          256, 
                          256, 
                          D3DX_DEFAULT,
                          D3DUSAGE_RENDERTARGET,
                          D3DFMT_A8R8G8B8,
                          D3DPOOL_DEFAULT,
                          &d3d9RenderTargetTexture);

    if (texture == 0)
        texture = new Texture();

    Operator* input =  getInput(0);
 
    D3DXCOLOR color = getColorProperty(0);
    unsigned char height = getByteProperty(1);
    unsigned char x = getByteProperty(2);
    unsigned char y = getByteProperty(3);
    const char *font = getStringProperty(4);
    const char *text = getStringProperty(5);

    LPD3DXFONT d3d9Font;
    D3DXCreateFontA(globalDirect3DDevice,
                   height, 
                   0, 
                   FALSE, 
                   0, 
                   FALSE, 
                   DEFAULT_CHARSET, 
                   OUT_DEFAULT_PRECIS, 
                   DEFAULT_QUALITY, 
                   DEFAULT_PITCH | FF_DONTCARE, 
                   font, 
                   &d3d9Font);

    LPDIRECT3DSURFACE9 renderTargetSurface;
    LPDIRECT3DSURFACE9 backbuffer;
    d3d9RenderTargetTexture->GetSurfaceLevel(0, &renderTargetSurface);
    globalDirect3DDevice->GetRenderTarget(0, &backbuffer);
    globalDirect3DDevice->SetRenderTarget(0, renderTargetSurface);
    
    if (input != 0)
    {
        D3DXLoadSurfaceFromSurface(renderTargetSurface, 
                                   NULL, 
                                   NULL, 
                                   input->texture->d3d9Surface, 
                                   NULL, 
                                   NULL, 
                                   D3DX_FILTER_NONE,
                                   0);
    }
    else
    {
        globalDirect3DDevice->Clear(0,
                                    NULL,
                                    D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                                    D3DCOLOR_XRGB(0,0,0),
                                    1.0f,
                                    0);
    }
    globalDirect3DDevice->BeginScene();
    RECT rect;
    rect.left = x;
    rect.right= 256;
    rect.top = y;
    rect.bottom = 256;
    d3d9Font->DrawTextA(NULL, text, -1, &rect, DT_LEFT, color);
    globalDirect3DDevice->EndScene();

    globalDirect3DDevice->SetRenderTarget(0, backbuffer);
    backbuffer->Release();

    d3d9Font->Release();
    
    globalDirect3DDevice->GetRenderTargetData(renderTargetSurface,
                                              texture->d3d9Surface);
    renderTargetSurface->Release();
    
    texture->setDirty();
}

#ifdef DB_EDITOR
void TextOperator::deviceLost()
{
    Operator::deviceLost();
    if (d3d9RenderTargetTexture != 0)
    {
        d3d9RenderTargetTexture->Release();
        d3d9RenderTargetTexture = 0;
    }
}
#endif