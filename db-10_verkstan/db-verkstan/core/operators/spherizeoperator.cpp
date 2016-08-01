#include "spherizeoperator.hpp"

void SpherizeOperator::process(int tick)
{
    if (mesh != 0)
        delete mesh;

	float radius = getFloatProperty(0);
	float amount = getFloatProperty(1);
	mesh = getInput(0)->mesh->clone();

	for (int i = 0; i < mesh->getNumVertices(); i++)
	{
		Vec3 p = mesh->pos(i);
		Vec3 n = normalize(p) * radius;
		mesh->pos(i) = p + (n - p) * amount;
	}

	mesh->recalculateNormals();
}
