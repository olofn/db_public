#include "core/operators/cloudsoperator.hpp"

void CloudsOperator::divideGrid(int x, 
                                int y, 
                                int width, 
                                int height, 
                                float c1, 
                                float c2, 
                                float c3, 
                                float c4,
								int Scale)
{
	float Edge1, Edge2, Edge3, Edge4, Middle;
	int newWidth = width / 2;
	int newHeight = height / 2;

	if (width >= 2 || height >= 2)
	{	
        float max = (newWidth + newHeight) / 512.0f * 4.0f * Scale;
		Middle = (c1 + c2 + c3 + c4) / 4 + (frand() - 0.5f) * max;	//Randomly displace the midpoint!
		Edge1 = (c1 + c2) / 2;	//Calculate the edges by averaging the two corners of each edge.
		Edge2 = (c2 + c3) / 2;
		Edge3 = (c3 + c4) / 2;
		Edge4 = (c4 + c1) / 2;
		
		//Make sure that the midpoint doesn't accidentally "randomly displaced" past the boundaries!
		Middle = saturate(Middle);
		
		//Do the operation over again for each of the four new grids.			
		divideGrid(x, y, newWidth, newHeight, c1, Edge1, Middle, Edge4, Scale);
		divideGrid(x + newWidth, y, newWidth, newHeight, Edge1, c2, Edge2, Middle, Scale);
		divideGrid(x + newWidth, y + newHeight, newWidth, newHeight, Middle, Edge2, c3, Edge3, Scale);
		divideGrid(x, y + newHeight, newWidth, newHeight, Edge4, Middle, Edge3, c4, Scale);
	}
	else
	{
		float c = (c1 + c2 + c3 + c4) / 4;
        //c = c * c * (3 - c * 2);
        D3DXCOLOR color;
        D3DXColorLerp(&color, &color1, &color2, c);
        texture->putPixel(x, y, color); 
    }
}

void CloudsOperator::process(int tick)
{
    if (texture == 0)
        texture = new Texture();
    
    color1 = getColorProperty(0);
    color2 = getColorProperty(1);
    srand(getByteProperty(3));
    texture->lock();

	int scale = getByteProperty(2);
	int size = 1 << scale;
	float *values = new float[size * size];

	for (int i = 0; i < size * size; i++)
	{
		values[i] = frand();
	}
	
	int w = 256 / size;
	int h = 256 / size;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			int x2 = (x + 1) % size;
			int y2 = (y + 1) % size;
			float c1 = values[x  + y  * size];
			float c2 = values[x2 + y  * size];
			float c3 = values[x2 + y2 * size];
			float c4 = values[x  + y2 * size];
			divideGrid(x * w, y * h, w, h, c1, c2, c3, c4, scale < 1 ? 1 : scale);
		}
	}

	delete[] values;

    texture->unlock();
    texture->setDirty();
}
