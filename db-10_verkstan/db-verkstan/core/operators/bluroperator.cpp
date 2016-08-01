#include "core/operators/bluroperator.hpp"

DWORD pack(DWORD r, DWORD g, DWORD b, DWORD div, DWORD amp)
{
	div *= 16;
	r = (r * amp) / div;
	g = (g * amp) / div;
	b = (b * amp) / div;

	r = min(r, (DWORD)255);
	g = min(g, (DWORD)255);
	b = min(b, (DWORD)255);

	return 0xff000000 |
		(r & 0xff) |
		(g & 0xff) << 8 |
		(b & 0xff) << 16;
}

// Some thoughts and ideas about enhancing the code.
// Different was of handling edges could be handled,
// like CLAMP, WRAP and ZERO.
// As the vertical and horizontal bluring is almost
// identicall it could be done with a single loop
// if the loop transposes each pixel so it's ready
// for the next blur.
void BlurOperator::process(int tick)
{
    if (texture != 0)
        delete texture;

    unsigned char type = getByteProperty(0) + 1;
    unsigned char direction = getByteProperty(1) + 1;
    unsigned char width = getByteProperty(2) + 1;
    unsigned char amplify = getByteProperty(3);

    Texture* in = getInput(0)->texture->clone();   
/*
	if (width <= 1)
	{
		texture = in;
		return;
	}
*/
    Texture* out = new Texture();

    in->lock();
    out->lock();


	if (direction & 1)
	{
		// Repeat box blur
		for (int t = 0; t < type; t++)
		{
			// For each line
			for (int y = 0; y < 256; y++)
			{
				DWORD r = 0, g = 0, b = 0;
				for (int x = 0; x < width; x++)
				{
					DWORD c = in->getPixel(x, y);
					r += c & 0xff;
					g += (c >> 8) & 0xff;
					b += (c >> 16) & 0xff;
				}

				for (int x = 0; x < 256; x++)
				{
					out->putPixel((x + width / 2) & 0xff, y, pack(r, g, b, width, amplify));

					DWORD c1 = in->getPixel((x + width) & 0xff, y);
					DWORD c2 = in->getPixel(x, y);
					r += c1 & 0xff;
					g += (c1 >> 8) & 0xff;
					b += (c1 >> 16) & 0xff;
					r -= c2 & 0xff;
					g -= (c2 >> 8) & 0xff;
					b -= (c2 >> 16) & 0xff;
				}
			}

			{
				Texture *tmp = out;
				out = in;
				in = tmp;
			}
		}
	}


	if (direction & 2)
	{
		// Repeat box blur
		for (int t = 0; t < type; t++)
		{
			// For each column
			for (int x = 0; x < 256; x++)
			{
				DWORD r = 0, g = 0, b = 0;
				for (int y = 0; y < width; y++)
				{
					DWORD c = in->getPixel(x, y);
					r += c & 0xff;
					g += (c >> 8) & 0xff;
					b += (c >> 16) & 0xff;
				}

				for (int y = 0; y < 256; y++)
				{
					out->putPixel(x, (y + width / 2) & 0xff, pack(r, g, b, width, amplify));

					DWORD c1 = in->getPixel(x, (y + width) & 0xff);
					DWORD c2 = in->getPixel(x, y);
					r += c1 & 0xff;
					g += (c1 >> 8) & 0xff;
					b += (c1 >> 16) & 0xff;
					r -= c2 & 0xff;
					g -= (c2 >> 8) & 0xff;
					b -= (c2 >> 16) & 0xff;
				}
			}

			{
				Texture *tmp = out;
				out = in;
				in = tmp;
			}
		}
	}


	
    in->unlock();
    out->unlock();

    texture = in;

    delete out;

    texture->setDirty();


/*
    width = width % 2 == 0 ? width + 1 : width;
    width = width < 1 ? 1 : width;
    amplify = amplify > 32 ? 32 : amplify; 
    int wh = width / 2;
    float amp = (width - 1.0f) * (amplify / 32.0f);

    float w = ((float)width - amp);

    // Type 0 is Box blur
    // Type 1 is Triangle blur
    // Type 2 is Gaussien blur
    for (int p = 0; p < type + 1; p++)
    {
        // Swap
        tmp = in;
        in = out;
        out = tmp;

        // If we should blur along the x-axis.
        if (direction == 0 || direction == 2)
        {
            // Blur along the x-axis.
            for (int y = 0; y < 256; ++y)
            {
                //int suma = 0;
                float sumr = 0;
                float sumg = 0;
                float sumb = 0;
               
                for (int i = 0; i < width; ++i)
                {
                    D3DCOLOR c = in->getPixel(i, y);
                    //suma += D3DCOLOR_A(c);
                    sumr += D3DCOLOR_R(c) / w;
                    sumg += D3DCOLOR_G(c) / w;
                    sumb += D3DCOLOR_B(c) / w;
                }

                for (int x = 0; x < 256; ++x)
                {
                    int ox = (x + wh) % 256;

                    //int a = suma / (width - amp);
                    int r = (int)sumr;// / (width - amp);
                    int g = (int)sumg;// / (width - amp);
                    int b = (int)sumb;// / (width - amp);

                    //a = a > 255 ? 255 : a;
                    r = r > 255 ? 255 : r;
                    g = g > 255 ? 255 : g;
                    b = b > 255 ? 255 : b;

                    out->putPixel(ox, y, D3DCOLOR_XRGB(r, g, b));
                    
                    D3DCOLOR c1 = in->getPixel(x, y);
                    //suma -= D3DCOLOR_A(c1);
                    sumr -= D3DCOLOR_R(c1) / w;
                    sumg -= D3DCOLOR_G(c1) / w;
                    sumb -= D3DCOLOR_B(c1) / w;

                    int ex = (x + width) % 256;

                    D3DCOLOR c2 = in->getPixel(ex, y);
                    //suma += D3DCOLOR_A(c2);
                    sumr += D3DCOLOR_R(c2) / w;
                    sumg += D3DCOLOR_G(c2) / w;
                    sumb += D3DCOLOR_B(c2) / w;
                }
            }
        }

        // If direction is X and Y we need to perform a swap
        // before we blur along the Y-axis.
        if (direction == 2)
        {
            // Swap
            tmp = in;
            in = out;
            out = tmp;
        }

        // If we should blur along the y-axis.
        if (direction > 0)
        {
            // Blur along the y-axis.
            for (int x = 0; x < 256; ++x)
            {
                //int suma = 0;
                float sumr = 0;
                float sumg = 0;
                float sumb = 0;
               
                for (int i = 0; i < width; ++i)
                {
                    D3DCOLOR c = in->getPixel(x, i);
                    //suma += D3DCOLOR_A(c);
                    sumr += D3DCOLOR_R(c) / w;
                    sumg += D3DCOLOR_G(c) / w;
                    sumb += D3DCOLOR_B(c) / w;
                }

                for (int y = 0; y < 256; ++y)
                {
                    int oy = (y + wh) % 256;

                    //int a = suma / (width - amp);
                    int r = (int)sumr;
                    int g = (int)sumg;
                    int b = (int)sumb;

                    r = r > 255 ? 255 : r;
                    g = g > 255 ? 255 : g;
                    b = b > 255 ? 255 : b;

                    out->putPixel(x, oy, D3DCOLOR_XRGB(r, g, b));
                    
                    D3DCOLOR c1 = in->getPixel(x, y);
                    sumr -= D3DCOLOR_R(c1) / w;
                    sumg -= D3DCOLOR_G(c1) / w;
                    sumb -= D3DCOLOR_B(c1) / w;

                    int ey = (y + width) % 256;

                    D3DCOLOR c2 = in->getPixel(x, ey);
                    sumr += D3DCOLOR_R(c2) / w;
                    sumg += D3DCOLOR_G(c2) / w;
                    sumb += D3DCOLOR_B(c2) / w;
                }
            }
        }
    }

    in->unlock();
    out->unlock();

    texture = out->clone();

    delete in;
    delete out;*/
}
