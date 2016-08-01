#include "core/operators/sphereoperator.hpp"
#include "../util.hpp"

void SphereOperator::process(int tick)
{
	if (mesh != 0)
        delete mesh;
    
	float radius = getFloatProperty(0);
    int slices = getByteProperty(1);
    int stacks = getByteProperty(2);

	int numVertices = (stacks + 1) * (slices + 1) + slices * 2;
	int numTriangles = slices * 2;
	int numQuads = slices * stacks;

	mesh = new Mesh(numVertices, numTriangles, numQuads);

	int vert = 0, tri = 0, quad = 0;
	int cvert = (stacks + 1) * (slices + 1);

	for (int x = 0; x <= slices; x++)
	{
		float u = x / (float)slices;

		for (int y = 0; y <= stacks; y++)
		{
			float v = (y + 1.0f) / (stacks + 2.0f);
			Vec3 p = Vec3(cosf(u * M_PI * 2) * sinf(v * M_PI),
				          cosf(v * M_PI),
					      sinf(u * M_PI * 2) * sinf(v * M_PI));

			mesh->pos(vert) = p * radius;
			mesh->normal(vert) = p;
			mesh->uv(vert) = Vec2(u, v);
			
			if (y == 0 && x != slices)
			{
				mesh->pos(cvert) = Vec3(0.0f, radius, 0.0f);
				mesh->normal(cvert) = Vec3(0.0f, 1.0f, 0.0f);
				mesh->uv(cvert) = Vec2((x + 0.5f) / slices, 0.0f);

				mesh->setTriangle(tri, vert, cvert, vert + stacks + 1);

				cvert++;
				tri++;
			}

			if (y == stacks && x != slices)
			{
				mesh->pos(cvert) = Vec3(0.0f, -radius, 0.0f);
				mesh->normal(cvert) = Vec3(0.0f, -1.0f, 0.0f);
				mesh->uv(cvert) = Vec2((x + 0.5f) / slices, 1.0f);

				mesh->setTriangle(tri, cvert, vert, vert + stacks + 1);

				cvert++;
				tri++;
			}


			if (y != stacks && x != slices)
			{
				mesh->setQuad(quad, vert, vert + stacks + 1, vert + stacks + 2, vert + 1);
				quad++;
			}

			vert++;
		}
	}
/*
	int numVertices = 2 + slices * stacks;
	int numQuads = slices * (stacks - 1);
    int numTriangles = slices * 2;

	mesh = new Mesh(numVertices, numTriangles + numQuads * 2, 0, 1);

	int v = 0;
	int t = 0;

	for(int i = 0; i < stacks; i++)
	{
		float a = (((float)i + 1) / (stacks + 1)) * (float)M_PI;
		float cosa = cosf(a);
		float sina = sinf(a);

		for(int j = 0; j < slices; j++)
		{
			float b = (float)(j * M_PI * 2 / slices);
			mesh->normal(v) = Vec3(cosf(b) * sina, sinf(b) * sina, cosa * radius);
			mesh->pos(v) = mesh->normal(v) * radius;
			mesh->uv(v) = Vec2(a, b);			
			mesh->triangle(t)[0] = v;
			mesh->triangle(t)[1] = v - 1 < 0 ? 0 : v - 1;
			mesh->triangle(t)[2] = v - slices < 0 ? 0 : v - slices;
			v++; t++;
		}
	}
*/
	/*
    if (mesh != 0)
        delete mesh;

    mesh = new Mesh();

    float radius = getFloatProperty(0);
    unsigned char slices = getByteProperty(1);
    unsigned char stacks = getByteProperty(2);

    LPD3DXMESH tmpMesh;
    D3DXCreateSphere(globalDirect3DDevice, 
                     radius,
                     (int)slices,
                     (int)stacks,
                     &tmpMesh, 
                     NULL);
    tmpMesh->CloneMeshFVF(NULL, 
                          FVF_VERTEX,
                          globalDirect3DDevice,
                          &mesh->d3d9Mesh);
    tmpMesh->Release();*/
}
