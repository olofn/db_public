#include "core/operators/invertoperator.hpp"

void InvertOperator::process(int tick)
{
    if (texture == 0)
        texture = new Texture();

    Operator* input = getInput(0);
    texture->lock();
    input->texture->lock();

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            texture->putPixel(x, y, (~input->texture->getPixel(x, y)) | 0xff000000);
        }
    }

    input->texture->unlock();
    texture->unlock();
}
