#include "core/operators/distortionoperator.hpp"

void DistortionOperator::process(int tick)
{
    if (texture == 0)
       texture = new Texture();

    unsigned char mode = getByteProperty(0);
    float amount = getByteProperty(1) / 255.0f;

    Texture* srcTexture = getInput(0)->texture;
    Texture* mapTexture = getInput(1)->texture;
 
    texture->lock();
    srcTexture->lock();
    mapTexture->lock();

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            D3DCOLOR c = mapTexture->getPixel(x, y);
            
            Vec3 normal;
            if (mode == 0)
                normal = Vec3(D3DCOLOR_G(c) - 127.0f, D3DCOLOR_B(c) - 127.0f, 1.0f);
            else if (mode == 1)
                normal = Vec3(D3DCOLOR_R(c) - 127.0f, D3DCOLOR_G(c) - 127.0f, D3DCOLOR_B(c) - 127.0f);

            normalize(normal);

            float u = fmodf(normal.x * amount + x, 255.0f);
            float v = fmodf(normal.y * amount + y, 255.0f);

            texture->putPixel(x, y, srcTexture->getPixelWrap(u, v));
        }
    }

    texture->unlock();
    srcTexture->unlock();
    mapTexture->unlock();
    texture->setDirty();
}
