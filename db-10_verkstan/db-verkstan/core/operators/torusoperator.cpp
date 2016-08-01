#include "core/operators/torusoperator.hpp"

void TorusOperator::process(int tick)
{
    if (mesh != 0)
        delete mesh;

    float innerRadius = getFloatProperty(0);
    float outerRadius = getFloatProperty(1);
    unsigned char sides = getByteProperty(2);
    unsigned char rings = getByteProperty(3);

	int numVertices = (sides + 1) * (rings + 1);
	int numTriangles = 0;
	int numQuads = sides * rings;

	mesh = new Mesh(numVertices, numTriangles, numQuads);

	int vert = 0, quad = 0;

	for (int x = 0; x <= rings; x++)
	{
		float u = x / (float)rings;
		Vec3 toOuter(cosf(u * 2 * M_PI), 0.0f, sinf(u * 2 * M_PI));

		for (int y = 0; y <= sides; y++)
		{
			float v = y / (float)sides;

			Vec3 toInner = -cosf(v * 2 * M_PI) * toOuter + sinf(v * 2 * M_PI) * Vec3(0.0f, 1.0f, 0.0f);

			mesh->pos(vert) = toOuter * outerRadius + toInner * innerRadius;
			mesh->color(vert) = 0xff00ff00;//rand() + (rand() << 16);
			mesh->normal(vert) = toInner;
			mesh->uv(vert) = Vec2(u, v);

			if (y != sides && x != rings)
			{
				mesh->setQuad(quad, vert, vert + sides + 1, vert + sides + 2, vert + 1);
				quad++;
			}

			vert++;
		}
	}
}
