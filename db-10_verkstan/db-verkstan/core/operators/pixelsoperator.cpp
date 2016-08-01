#include "core/operators/pixelsoperator.hpp"

void PixelsOperator::process(int tick)
{
    if (texture == 0)
        texture = new Texture();

    Operator* input = getInput(0);

    if (input != 0)
        input->texture->copy(texture);
    else
        texture->fillRectangle(0, 0, 256, 256, 0xff000000);

    D3DXCOLOR color1 = getColorProperty(0);
    D3DXCOLOR color2 = getColorProperty(1);
    int count = getByteProperty(2) * 255;
    unsigned char seed = getByteProperty(3);

    texture->lock();
    srand(seed);
    D3DXCOLOR color;
    for (int i = 0; i < count; i++)
    {
        D3DXColorLerp(&color, &color1, &color2, frand());
        texture->putPixel(rand() % 256, rand() % 256, color); 
    }
    texture->unlock();
    texture->setDirty();
}
