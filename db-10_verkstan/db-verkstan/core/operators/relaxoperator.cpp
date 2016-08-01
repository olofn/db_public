#include "core/operators/relaxoperator.hpp"

void RelaxOperator::process(int tick)
{
    if (mesh != 0)
        delete mesh;

	mesh = getInput(0)->mesh->clone();

	float strength = getFloatProperty(0);
	int repetitions = getByteProperty(1);	
	
	Mesh::EdgeInfo *edgeInfo = mesh->constructEdgeInfo();

	for(int i = 0; i < repetitions; i++)
	{
		relax(edgeInfo, strength);
	}

	mesh->recalculateNormals();

	delete edgeInfo;
}

void RelaxOperator::relax(Mesh::EdgeInfo *edgeInfo, float strength)
{
	Vec3 *force = new Vec3[mesh->getNumVertices()];
    ZeroMemory(force, sizeof(float) * mesh->getNumVertices());

	for(int i = 0; i < mesh->getNumVertices(); i++)
	{
		force[i] = Vec3(0, 0, 0);
	}

	for(int i = 0; i < edgeInfo->getNumEdges(); i++)
	{
		int *e = edgeInfo->getEdge(i);
		Vec3 offset = mesh->pos(e[0]) - mesh->pos(e[1]);
		force[e[0]] -= offset;
		force[e[1]] += offset;
		//System::Console::WriteLine(e[0] + " " + e[1] + " " + length(offset));
	}

	for(int i = 0; i < mesh->getNumVertices(); i++)
	{
		//System::Console::WriteLine(i + " " + length(force[i]));
		mesh->pos(i) += force[i] * strength;
	}

	delete[] force;
}