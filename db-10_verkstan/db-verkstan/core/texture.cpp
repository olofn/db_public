#include "core/globals.hpp"
#include "core/texture.hpp"

Texture::Texture()
:d3d9Texture(0),
width(256),
height(256)
{
    globalDirect3DDevice->CreateOffscreenPlainSurface(256,
                                                      256, 
                                                      D3DFMT_A8R8G8B8, 
                                                      D3DPOOL_SYSTEMMEM,
                                                      &d3d9Surface,
                                                      NULL);  
}

Texture::~Texture()
{
    d3d9Surface->Release();
    if (d3d9Texture != 0)
        d3d9Texture->Release();
}

void Texture::setDirty()
{
    if (d3d9Texture != 0)
    {
        d3d9Texture->Release();
        d3d9Texture = 0;
    }
}

LPDIRECT3DTEXTURE9 Texture::getD3D9Texture()
{
    if (d3d9Texture == 0)
    {
        D3DXCreateTexture(globalDirect3DDevice, 
                          256, 
                          256, 
                          5,
                          D3DPOOL_MANAGED,
                          D3DFMT_A8R8G8B8,
                          D3DPOOL_DEFAULT,
                          &d3d9Texture);

        LPDIRECT3DSURFACE9 d3d9TextureSurface;
        d3d9Texture->GetSurfaceLevel(0, &d3d9TextureSurface);
        globalDirect3DDevice->UpdateSurface(d3d9Surface, 
                                            NULL,
                                            d3d9TextureSurface,
                                            NULL);
        d3d9TextureSurface->Release();
        D3DXFilterTexture(d3d9Texture, NULL, 0, D3DX_DEFAULT);
    }
                                           
    return d3d9Texture;
}

void Texture::lock()
{
    d3d9Surface->LockRect(&d3d9LockedRect, NULL, NULL);
}

void Texture::unlock()
{
    d3d9Surface->UnlockRect();
}

void Texture::fillRectangle(int x, 
                            int y,
                            int width,
                            int height,
                            DWORD c)
{
    lock();
    DWORD* pixels = (DWORD*)d3d9LockedRect.pBits;
    int pitch = d3d9LockedRect.Pitch / sizeof(DWORD);
    int h = y + height;
    h = h > 255 ? 255 : h;
    int w = x + width;
    w = w > 255 ? 255 : w;
    for (int j = y; j <= h; j++)
        for (int i = x; i <= w; i++)
            pixels[pitch * j + i] =  c;
    unlock();
}

Texture* Texture::clone()
{
    Texture* clone = new Texture();
    D3DXLoadSurfaceFromSurface(clone->d3d9Surface, 
                               NULL, 
                               NULL, 
                               d3d9Surface, 
                               NULL, 
                               NULL, 
                               D3DX_FILTER_NONE,
                               0);
    return clone;
}

void Texture::copy(Texture* texture)
{
    D3DXLoadSurfaceFromSurface(texture->d3d9Surface, 
                               NULL, 
                               NULL, 
                               d3d9Surface, 
                               NULL, 
                               NULL, 
                               D3DX_FILTER_NONE,
                               0);
}
DWORD Texture::getPixelWrap(float x, float y)
{
    // Fractions
    float xFraction = x >= 0.0f ? (x - (int)x) : 1.0f + (x - (int)x);
    float yFraction = y >= 0.0f ? (y - (int)y) : 1.0f + (y - (int)y);

    int xPixel = x >= 0.0f ? (int)x : (int)x - 1;
	int yPixel = y >= 0.0f ? (int)y : (int)y - 1;

    int r = 0;
    int g = 0;
    int b = 0;

    float weight = (1.0f - xFraction) * (1.0f - yFraction);
    int xCurrent = (xPixel + 2560) % 256;
    int yCurrent = (yPixel + 2560) % 256;
    D3DCOLOR colorCurrent = getPixel(xCurrent, yCurrent);
    r += (int)(D3DCOLOR_R(colorCurrent) * weight);
    g += (int)(D3DCOLOR_G(colorCurrent) * weight);
    b += (int)(D3DCOLOR_B(colorCurrent) * weight);

    weight = xFraction * (1.0f - yFraction);
    xCurrent = (xPixel + 2561) % 256;
    yCurrent = (yPixel + 2560) % 256;
    colorCurrent = getPixel(xCurrent, yCurrent);
    r += (int)(D3DCOLOR_R(colorCurrent) * weight);
    g += (int)(D3DCOLOR_G(colorCurrent) * weight);
    b += (int)(D3DCOLOR_B(colorCurrent) * weight);

    weight = (1.0f - xFraction) * yFraction;
    xCurrent = (xPixel + 2560) % 256;
    yCurrent = (yPixel + 2561) % 256;
    colorCurrent = getPixel(xCurrent, yCurrent);
    r += (int)(D3DCOLOR_R(colorCurrent) * weight);
    g += (int)(D3DCOLOR_G(colorCurrent) * weight);
    b += (int)(D3DCOLOR_B(colorCurrent) * weight);

    weight = xFraction * yFraction;
    xCurrent = (xPixel + 2561) % 256;
    yCurrent = (yPixel + 2561) % 256;
    colorCurrent = getPixel(xCurrent, yCurrent);
    r += (int)(D3DCOLOR_R(colorCurrent) * weight);
    g += (int)(D3DCOLOR_G(colorCurrent) * weight);
    b += (int)(D3DCOLOR_B(colorCurrent) * weight);

    return D3DCOLOR_XRGB(r, g, b);
}