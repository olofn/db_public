#include "core/operators/rectangleoperator.hpp"

void RectangleOperator::process(int tick)
{    
    if (texture == 0)
        texture = new Texture();

    Operator* input = getInput(0);
    
    if (input != 0)
        input->texture->copy(texture);
    else
        texture->fillRectangle(0, 0, 256, 256, 0xff000000);

    D3DXCOLOR color = getColorProperty(0);
    unsigned char x = getByteProperty(1);
    unsigned char y = getByteProperty(2);
    unsigned char width = getByteProperty(3);
    unsigned char height = getByteProperty(4);

    texture->fillRectangle(x, y, width, height, color);
    texture->setDirty();
}
