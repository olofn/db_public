#include "core/operators/glowoperator.hpp"

void GlowOperator::process(int tick)
{
    if (texture == 0)
        texture = new Texture();

    Operator* input = getInput(0);

    if (input != 0)
        input->texture->copy(texture);
    else
        texture->fillRectangle(0, 0, 256, 256, 0xff000000);

    D3DXCOLOR color = getColorProperty(0);
    unsigned char centerx = getByteProperty(1);
    unsigned char centery = getByteProperty(2);
    float radiusx = 1.0f / getByteProperty(3);
    float radiusy = 1.0f / getByteProperty(4);
    float gamma = 1.0f - getByteProperty(5) / 256.0f;
    float alpha = 1.0f - getByteProperty(6) / 256.0f;
 
    D3DXCOLOR blackColor = D3DCOLOR_ARGB(0, 0, 0, 0);

    texture->lock();
    
    for (int y = 0; y < 256; y++)
    {
        float dy = (float)(y - centery) * radiusy;
		float dy_2 = dy*dy;

        for (int x = 0; x < 256; x++)
        {
            float dx = (float)(x-centerx) * radiusx;
			float d = sqrtf(dx*dx + dy_2);
           
            if (d > 1.0f)		
                d = 1.0f;
			d = 1.0f - d;
            
            float a = -1.0f;;
            if (d != 0.0f)
            {
                d = powf(d, gamma);
                a = d - alpha;
            }
            
            if (a < 0.0f)
                continue;

            D3DXCOLOR resultColor;
            D3DXCOLOR inputColor = texture->getPixel(x, y);
            D3DXColorLerp(&resultColor, &inputColor, &color, a);
            texture->putPixel(x, y, resultColor);
        }
    }

    texture->unlock();
    texture->setDirty();
}
