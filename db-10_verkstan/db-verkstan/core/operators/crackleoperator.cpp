#include "core/operators/crackleoperator.hpp"

void CrackleOperator::process(int tick)
{
    if (texture == 0)
        texture = new Texture();
    
    D3DXCOLOR color1 = getColorProperty(0);
    D3DXCOLOR color2 = getColorProperty(1);
	int count = getByteProperty(2) + 2;
	float randomness = getByteProperty(3);
    srand(getByteProperty(4));

	Vec2 *pos = new Vec2[count * count];

	for (int i = 0; i < count * count; i++)
	{
		int x = ((i % count) * 256) / count;
		int y = ((i / count) * 256) / count;
		pos[i] = Vec2(x + frand(0.0f, randomness / count), y + frand(0.0f, randomness / count));
	}

    texture->lock();

	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			int px = (x * count) / 256;
			int py = (y * count) / 256;

			float dist1 = 512.0f * 512.0f;
			float dist2 = 512.0f * 512.0f;
			int point1 = 0;
			int point2 = 0;

			Vec2 current((float)x, (float)y);

			for (int oy = -1; oy <= 1; oy++)
			{
				for (int ox = -1; ox <= 1; ox++)
				{
					int tx = (px + ox + count) % count;
					int ty = (py + oy + count) % count;
					int i = tx + ty * count;
					
					Vec2 diff(min(min(abs(current.x - pos[i].x), abs(current.x - pos[i].x - 256.0f)), abs(current.x - pos[i].x + 256.0f)),
						      min(min(abs(current.y - pos[i].y), abs(current.y - pos[i].y - 256.0f)), abs(current.y - pos[i].y + 256.0f)));

					float dist = lengthSq(diff);

					if (dist < dist1)
					{
						dist2 = dist1;
						point2 = point1;
						dist1 = dist;
						point1 = i;
					}
					else if (dist < dist2 && i != point1)
					{
						dist2 = dist;
						point2 = i;
					}
				}
			}

			dist1 = sqrt(dist1);
			dist2 = sqrt(dist2);
			float t = (dist1 / (dist1 + dist2)) * 2.0f;

			D3DXCOLOR c;
			D3DXColorLerp(&c, &color2, &color1, t);
			texture->putPixel(x, y, c);
		}
	}

    texture->unlock();
    texture->setDirty();

	delete[] pos;
}
