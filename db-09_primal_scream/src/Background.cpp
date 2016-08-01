#include "Precompiled.hpp"
#include "Background.hpp"
#include "Resource.hpp"

Background::Background(char *layer1Image, char *layer2Image, int color)
	: color(color)
	, layer1(0)
	, layer2(0)
{
	if (layer1Image)
	{
		layer1 = Resource::getBitmap(layer1Image);
	}

	if (layer2Image)
	{
		layer2 = Resource::getBitmap(layer2Image);
	}
}

static void tileBitmap(BITMAP *target, BITMAP *source, int offsetX, int offsetY)
{
	offsetX = (offsetX % source->w) - source->w;
	offsetY = (offsetY % source->h) - source->h;

	for (int y = offsetY; y < target->h; y += source->h)
	{
		for (int x = offsetX; x < target->w; x += source->w)
		{
			draw_sprite(target, source, x, y);
		}
	}
}

void Background::draw(BITMAP *buffer, int offsetX, int offsetY, int layer)
{
	clear_to_color(buffer, color);

	if (layer2)
	{
		tileBitmap(buffer, layer2, offsetX / 4, offsetY / 4);
	}

	if (layer1)
	{
		tileBitmap(buffer, layer1, offsetX / 2, offsetY / 2);
	}
}

