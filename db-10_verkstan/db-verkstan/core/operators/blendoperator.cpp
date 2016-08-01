#include "core/operators/blendoperator.hpp"

void BlendOperator::process(int tick)
{
    if (texture == 0)
       texture = new Texture();

    Operator* inputToBlend1 = getInput(0);
    Operator* inputToBlend2 = getInput(1);
    Operator* inputAlpha = getInput(2);

    texture->lock();
    inputToBlend1->texture->lock();
    inputToBlend2->texture->lock();
    inputAlpha->texture->lock();

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            float a = D3DCOLOR_R(inputAlpha->texture->getPixel(x, y)) / 255.0f;
            float oneMinusA = 1.0f - a;
            D3DCOLOR c1 = inputToBlend1->texture->getPixel(x, y);
            D3DCOLOR c2 = inputToBlend2->texture->getPixel(x, y);

            int r = D3DCOLOR_R(c1) * a + D3DCOLOR_R(c2) * oneMinusA;
            int g = D3DCOLOR_G(c1) * a + D3DCOLOR_G(c2) * oneMinusA;
            int b = D3DCOLOR_B(c1) * a + D3DCOLOR_B(c2) * oneMinusA;
           
            texture->putPixel(x, y, D3DCOLOR_XRGB(r, g, b));
        }
    }

    texture->unlock();
    inputToBlend1->texture->unlock();
    inputToBlend2->texture->unlock();
    inputAlpha->texture->unlock();

    texture->setDirty();
}
