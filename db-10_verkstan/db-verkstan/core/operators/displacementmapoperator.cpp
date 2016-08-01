#include "displacementmapoperator.hpp"

void DisplacementMapOperator::process(int tick)
{
    if (mesh != 0)
        delete mesh;

	float distance = getFloatProperty(0);
	mesh = getInput(0)->mesh->clone();
	Texture *texture = getInput(1)->texture;

	texture->lock();

	for (int i = 0; i < mesh->getNumVertices(); i++)
	{
		Vec2 uv = mesh->uv(i) * 256.0f;
		D3DCOLOR pixel = texture->getPixel(((int)uv.x) & 0xff, ((int)uv.y) & 0xff);
        float d = (D3DCOLOR_R(pixel) + D3DCOLOR_G(pixel) + D3DCOLOR_B(pixel)) / 765.0f;
		mesh->pos(i) += mesh->normal(i) * d * distance;
	}

	texture->unlock();

	mesh->recalculateNormals();
}
