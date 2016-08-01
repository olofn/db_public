#include "core/operators/particlesystemoperator.hpp"

void ParticleSystemOperator::process(int tick)
{

}

void ParticleSystemOperator::render()
{	
	Mesh *srcMesh = getInput(0)->mesh->clone();

	if (!srcMesh)
	{
		return;
	}

	float particleSize = getFloatProperty(0);
	float lightingRange = getFloatProperty(1);
	
	globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

    Vec3 forward, up, right;

	{
		D3DXMATRIX viewMatrix;
		D3DXMATRIX worldMatrix;
		D3DXMATRIX worldViewMatrix;

		globalDirect3DDevice->GetTransform(D3DTS_VIEW, &viewMatrix);
		globalDirect3DDevice->GetTransform(D3DTS_WORLD, &worldMatrix);

		D3DXMatrixMultiply(&worldViewMatrix, &viewMatrix, &worldMatrix);
		D3DXMatrixTranspose(&worldViewMatrix, &worldViewMatrix);

		right = Vec3(worldViewMatrix.m[0]);
		up = Vec3(worldViewMatrix.m[1]);
		forward = Vec3(worldViewMatrix.m[2]);
	}

	Mesh *tmpMesh = new Mesh(srcMesh->getNumVertices() * 4, 0, srcMesh->getNumVertices(), 1, true);

	int *sortedVerts = srcMesh->constructSortedVertexIndices(-forward);

	unsigned int *colors = new unsigned int[srcMesh->getNumVertices()];

	Mesh::BoxedMesh *boxedMesh = srcMesh->constructBoxedMesh(lightingRange * 2);

	for (int i = 0; i < srcMesh->getNumVertices(); i++)
	{
		float wsum = 0.0f;
		Vec3 n(0.0f, 0.0f, 0.0f);

		int bx, by, bz;
		boxedMesh->getBoxFor(bx, by, bz, i);

		for (int z = -1; z <= 1; z++)
		{
			for (int y = -1; y <= 1; y++)
			{
				for (int x = -1; x <= 1; x++)
				{
					Mesh::BoxedMesh::Box &box = boxedMesh->get(bx + x, by + y, bz + z);
					for (int v = 0; v < box.size; v++)
					{
						int j = box.vertices[v];

						if (i == j)
						{
							continue;
						}

						Vec3 diff = srcMesh->pos(j) - srcMesh->pos(i);
						float l = length(diff);
						float w = pow(2.0f, -l / lightingRange);

						n += w * (diff / l);

						wsum += w;
					}
				}
			}
		}

		srcMesh->normal(i) = normalize(-n);
	}

	for (int i = 0; i < srcMesh->getNumVertices(); i++)
	{
		float ao = 1.0f;

		int bx, by, bz;
		boxedMesh->getBoxFor(bx, by, bz, i);

		for (int z = -1; z <= 1; z++)
		{
			for (int y = -1; y <= 1; y++)
			{
				for (int x = -1; x <= 1; x++)
				{
					Mesh::BoxedMesh::Box &box = boxedMesh->get(bx + x, by + y, bz + z);
					for (int v = 0; v < box.size; v++)
					{
						int j = box.vertices[v];

						if (i == j)
						{
							continue;
						}

						Vec3 diff = srcMesh->pos(j) - srcMesh->pos(i);
						float l = length(diff);
						float w = pow(2.0f, -l / lightingRange);
						float aw = saturate(dot((diff / l), srcMesh->normal(i)));
						ao *= saturate(1.0f - w * aw);
					}
				}
			}
		}

		Vec3 lightDir = normalize(Vec3(1.0f, 1.0f, 1.0f));
		Vec3 lightColor(1.0f, 0.9f, 0.7f);
		Vec3 ambientColor(0.2f, 0.2f, 0.3f);

		Vec3 diffuse = saturate(0.2f + dot(lightDir, srcMesh->normal(i))) * lightColor;

		Vec3 color = diffuse + ambientColor * ao;
		
		int r = (int)(color.x * 255.0f);
		int g = (int)(color.y * 255.0f);
		int b = (int)(color.z * 255.0f);
		colors[i] = D3DCOLOR_ARGB(255, min(r, 255), min(g, 255), min(b, 255));
	}


	for (int i = 0; i < srcMesh->getNumVertices(); i++)
	{
		int j = sortedVerts[i];

		tmpMesh->pos(i * 4 + 0) = srcMesh->pos(j) + (up + right) * particleSize;
		tmpMesh->pos(i * 4 + 1) = srcMesh->pos(j) + (up - right) * particleSize;
		tmpMesh->pos(i * 4 + 2) = srcMesh->pos(j) + (-up - right) * particleSize;
		tmpMesh->pos(i * 4 + 3) = srcMesh->pos(j) + (-up + right) * particleSize;

		tmpMesh->normal(i * 4 + 0) = srcMesh->normal(j);
		tmpMesh->normal(i * 4 + 1) = srcMesh->normal(j);
		tmpMesh->normal(i * 4 + 2) = srcMesh->normal(j);
		tmpMesh->normal(i * 4 + 3) = srcMesh->normal(j);

		tmpMesh->uv(i * 4 + 0) = Vec2(1.0f, 0.0f);
		tmpMesh->uv(i * 4 + 1) = Vec2(0.0f, 0.0f);
		tmpMesh->uv(i * 4 + 2) = Vec2(0.0f, 1.0f);
		tmpMesh->uv(i * 4 + 3) = Vec2(1.0f, 1.0f);

		tmpMesh->color(i * 4 + 0) = colors[j];
		tmpMesh->color(i * 4 + 1) = colors[j];
		tmpMesh->color(i * 4 + 2) = colors[j];
		tmpMesh->color(i * 4 + 3) = colors[j];

		tmpMesh->setQuad(i, i * 4 + 0, i * 4 + 3, i * 4 + 2, i * 4 + 1);
	}						
							
	globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	tmpMesh->render();		

	delete tmpMesh;
	delete srcMesh;

	delete[] sortedVerts;
	delete[] colors;
	delete boxedMesh;
}

#ifdef DB_EDITOR
void ParticleSystemOperator::deviceLost()
{
}
#endif