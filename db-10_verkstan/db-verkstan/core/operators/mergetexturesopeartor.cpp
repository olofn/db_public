#include "core/operators/mergetexturesoperator.hpp"

void MergeTexturesOperator::process(int tick)
{
    if (texture == 0)
        texture = new Texture();

    getInput(0)->texture->copy(texture);

    texture->lock();
    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->texture->lock();
    
    unsigned char mode = getByteProperty(0);
    
    DWORD* pixels = (DWORD*)texture->d3d9LockedRect.pBits;
    int pitch = texture->d3d9LockedRect.Pitch / sizeof(DWORD);

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            D3DCOLOR dstColor = pixels[x + y * pitch];
            int r = D3DCOLOR_R(dstColor);
            int g = D3DCOLOR_G(dstColor);
            int b = D3DCOLOR_B(dstColor);
            int a = 255;
            float rf = r / 255.0f;
            float gf = g / 255.0f;
            float bf = b / 255.0f;

            for (int i = 1; i < numberOfInputs; i++)
            {
                 DWORD* srcPixels = (DWORD*)getInput(i)->texture->d3d9LockedRect.pBits;
                 D3DCOLOR c = srcPixels[x + y * pitch];

                 switch(mode)
                 {
                 case 0:  // Add Clamp
                    r += D3DCOLOR_R(c);
                    g += D3DCOLOR_G(c);
                    b += D3DCOLOR_B(c);
                    r = r > 255 ? 255 : r;
                    g = g > 255 ? 255 : g;
                    b = b > 255 ? 255 : b;
                    break;
                 case 1: // Add Wrap
                    r += D3DCOLOR_R(c);
                    g += D3DCOLOR_G(c);
                    b += D3DCOLOR_B(c);
                    r = r % 256;
                    g = g % 256;
                    b = b % 256;
                    break;
                 case 2: // Sub Clamp
                    r -= D3DCOLOR_R(c);
                    g -= D3DCOLOR_G(c);
                    b -= D3DCOLOR_B(c);
                    r = r < 0 ? 0 : r;
                    g = g < 0 ? 0 : g;
                    b = b < 0 ? 0 : b;
                    break;
                 case 3: // Sub Wrap
                    r -= D3DCOLOR_R(c);
                    g -= D3DCOLOR_G(c);
                    b -= D3DCOLOR_B(c);
                    r = r < 0 ? r + 256 : r;
                    g = g < 0 ? g + 256 : g;
                    b = b < 0 ? b + 256 : b;
                    break;
                 case 4: // Mult
                    rf *= D3DCOLOR_R(c) / 255.0f;
                    gf *= D3DCOLOR_G(c) / 255.0f;
                    bf *= D3DCOLOR_B(c) / 255.0f;
                    r = (int)(rf * 255.0f);
                    g = (int)(gf * 255.0f);
                    b = (int)(bf * 255.0f);
                    break;
                case 5: // Alpha
                    a = D3DCOLOR_R(c);
                    break;
                 }
            }
            
            pixels[x + y * pitch] = D3DCOLOR_ARGB(a, r, g, b);
        }
    }

    texture->unlock();
    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->texture->unlock();

    texture->setDirty();
}
