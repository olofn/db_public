#include "core/operators/icosahedronoperator.hpp"

void IcosahedronOperator::process(int tick)
{
	if (mesh != 0)
        delete mesh;

    int numVertices = 12;
	int numTriangles = 20;

	mesh = new Mesh(numVertices, numTriangles, 0, 1);

	int v = 0, t = 0;

	float tau = (1.0f + sqrtf(5.0f)) / 2.0f;
	float one = 1.0f / sqrtf(tau * tau + 1.0f);
	tau *= one;

	mesh->pos(v) = Vec3(  tau,  one,    0); v++;
	mesh->pos(v) = Vec3( -tau,  one,    0); v++;
	mesh->pos(v) = Vec3( -tau, -one,    0); v++;
	mesh->pos(v) = Vec3(  tau, -one,    0); v++;
	mesh->pos(v) = Vec3(  one,   0 ,  tau); v++;
	mesh->pos(v) = Vec3(  one,   0 , -tau); v++;
	mesh->pos(v) = Vec3( -one,   0 , -tau); v++;
	mesh->pos(v) = Vec3( -one,   0 ,  tau); v++;
	mesh->pos(v) = Vec3(   0 ,  tau,  one); v++;
	mesh->pos(v) = Vec3(   0 , -tau,  one); v++;
	mesh->pos(v) = Vec3(   0 , -tau, -one); v++;
	mesh->pos(v) = Vec3(   0 ,  tau, -one); v++;

	for (int i = 0; i < numVertices; i++)
	{
		mesh->normal(i) = mesh->pos(i);
		mesh->uv(i).x = mesh->pos(i).x;
		mesh->uv(i).y = mesh->pos(i).y;
	}

	mesh->setTriangle(t,  4,  8,  7); t++;
	mesh->setTriangle(t,  4,  7,  9); t++;
	mesh->setTriangle(t,  5,  6, 11); t++;
	mesh->setTriangle(t,  5, 10,  6); t++;
	mesh->setTriangle(t,  0,  4,  3); t++;
	mesh->setTriangle(t,  0,  3,  5); t++;
	mesh->setTriangle(t,  2,  7,  1); t++;
	mesh->setTriangle(t,  2,  1,  6); t++;
	mesh->setTriangle(t,  8,  0, 11); t++;
	mesh->setTriangle(t,  8, 11,  1); t++;
	mesh->setTriangle(t,  9, 10,  3); t++;
	mesh->setTriangle(t,  9,  2, 10); t++;
	mesh->setTriangle(t,  8,  4,  0); t++;
	mesh->setTriangle(t, 11,  0,  5); t++;
	mesh->setTriangle(t,  4,  9,  3); t++;
	mesh->setTriangle(t,  5,  3, 10); t++;
	mesh->setTriangle(t,  7,  8,  1); t++;
	mesh->setTriangle(t,  6,  1, 11); t++;
	mesh->setTriangle(t,  7,  2,  9); t++;
	mesh->setTriangle(t,  6, 10,  2); t++;
}
