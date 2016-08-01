#include "core/operators/planeoperator.hpp"

void PlaneOperator::process(int tick)
{
   	if (mesh != 0)
        delete mesh;

    float width = getFloatProperty(0);
    float height = getFloatProperty(1);
    int xSlices = getByteProperty(2);
	int ySlices = getByteProperty(3);

    int numVertices = (1 + xSlices) * (1 + ySlices);
	int numQuads = xSlices * ySlices;

	mesh = new Mesh(numVertices, 0, numQuads);

    int vert = 0;
    int quad = 0;

    for (int y = 0; y <= ySlices; y++)
	{
		for (int x = 0; x <= xSlices; x++)
		{
			Vec2 uv(x / (float)xSlices, y / (float)ySlices);
			Vec3 pos = Vec3(uv.x * 2.0f - 1.0f, uv.y * 2.0f - 1.0f, 0.0f);
			mesh->pos(vert) = Vec3(pos.x * width, pos.y * height, 0.0f);
			mesh->normal(vert) = Vec3(0.0f, 0.0f, 1.0f);
			mesh->uv(vert) = Vec2(uv.x, uv.y);

			if (y != ySlices && x != xSlices)
			{
				mesh->setQuad(quad, vert, vert + xSlices + 1, vert + xSlices + 2, vert + 1);
				quad++;
			}

			vert++;
		}
	}
}
