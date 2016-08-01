#include "core/operators/rotozoomoperator.hpp"

void RotozoomOperator::process(int tick)
{    
    if (texture == 0)
        texture = new Texture();

    Texture* source = getInput(0)->texture;

    unsigned char centerx = getByteProperty(0);
    unsigned char centery = getByteProperty(1);
    unsigned char rotation = getByteProperty(2);
    unsigned char zoom = getByteProperty(3);
   
    source->lock();
    texture->lock();

    float frotate = rotation / 256.0f * D3DX_PI * 2.0f;
    float fzoom = pow(2.0f, (zoom - 128.0f) / 32.0f);
    float co = cosf(frotate);
    float si = sinf(frotate);

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
		{
            float u = ((x - centerx) * co + (y - centery) * (-si) + centerx) * fzoom;
            float v = ((x - centerx) * si + (y - centery) * co + centery) * fzoom;
            texture->putPixel(x, y, source->getPixelWrap(u, v));
        }
    }

    source->unlock();
    texture->unlock();
    texture->setDirty();
}
