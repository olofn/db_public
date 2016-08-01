#include "core/operators/boxoperator.hpp"

void BoxOperator::process(int tick)
{
	if (mesh != 0)
        delete mesh;

	Vec3 dimension(getFloatProperty(0) / 2.0f, getFloatProperty(1) / 2.0f, getFloatProperty(2) / 2.0f);
	int xSlices = getByteProperty(3);
	int ySlices = getByteProperty(4);
	int zSlices = getByteProperty(5);

	int numVertices = ((1 + xSlices) * (1 + ySlices) + (1 + ySlices) * (1 + zSlices) + (1 + zSlices) * (1 + xSlices)) * 2;
	int numQuads = (xSlices * ySlices + ySlices * zSlices + zSlices * xSlices) * 2;

	mesh = new Mesh(numVertices, 0, numQuads, 1);

	int vert = 0, quad = 0;
	Vec3 f = Vec3(0, 0, 1);
	
	for (int sign = -1; sign <= 1; sign += 2)
	{
		for (int axis = 0; axis < 3; axis++)
		{
			Vec3 n = (float)sign * f;
			Vec3 a = Vec3(n.y, n.z, n.x);
			Vec3 b = Vec3(f.z, f.x, f.y);

			for (int y = 0; y <= ySlices; y++)
			{
				for (int x = 0; x <= xSlices; x++)
				{
					Vec2 uv(x / (float)xSlices, y / (float)ySlices);
					Vec3 pos = (uv.x * 2.0f - 1.0f) * a + (uv.y * 2.0f - 1.0f) * b + n;
					mesh->pos(vert) = Vec3(pos.x * dimension.x, pos.y * dimension.y, pos.z * dimension.z);
					mesh->normal(vert) = n;
					mesh->uv(vert) = Vec2(uv.y, uv.x);

					if (y != ySlices && x != xSlices)
					{
						mesh->setQuad(quad, vert, vert + xSlices + 1, vert + xSlices + 2, vert + 1);
						quad++;
					}

					vert++;
				}
			}

			int temp = xSlices;
			xSlices = ySlices;
			ySlices = zSlices;
			zSlices = temp;
			f = Vec3(f.y, f.z, f.x);
		}
	}

/*
	Vec3 uv1 = normalize(cross(Vec3(1,1,1), Vec3(0,1,0)));
	Vec3 uv2 = normalize(cross(Vec3(1,1,1), uv1));

	for (int z = -1; z <= 1; z += 2)
	{
		for (int y = -1; y <= 1; y += 2)
		{
			for (int x = -1; x <= 1; x += 2)			
			{
				mesh->pos(v).x = x * width;
				mesh->pos(v).y = y * height;
				mesh->pos(v).z = z * depth;
				mesh->normal(v) = normalize(Vec3(x / width, y / height, z / depth));
				mesh->uv(v) = Vec2(dot(uv1, Vec3((float)x, (float)y, (float)z)), dot(uv2, Vec3((float)x, (float)y, (float)z)));
				v++;
			}
		}
	}

	mesh->setQuad(q, 0, 2, 3, 1);   q++;
	mesh->setQuad(q, 4, 5, 7, 6);   q++;
	mesh->setQuad(q, 6, 7, 3, 2);   q++;
	mesh->setQuad(q, 0, 1, 5, 4);   q++;
	mesh->setQuad(q, 0, 4, 6, 2);   q++;
	mesh->setQuad(q, 1, 3, 7, 5);   q++;*/
}
