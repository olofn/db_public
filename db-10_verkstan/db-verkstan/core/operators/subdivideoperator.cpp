#include "core/operators/subdivideoperator.hpp"

void SubdivideOperator::process(int tick)
{
    if (mesh != 0)
        delete mesh;

	Mesh *inputMesh = getInput(0)->mesh;

	int repetitions = getByteProperty(0);
	float smoothness = getFloatProperty(1);

	if (repetitions == 0)
	{
		mesh = inputMesh->clone();
	}
	else
	{
		Mesh *srcMesh = inputMesh;
		for(int i = 0; i < repetitions; i++)
		{
			srcMesh = subdivide(srcMesh, srcMesh != inputMesh, smoothness);			
		}
		mesh = srcMesh;
		mesh->recalculateNormals();
	}
}

Mesh* SubdivideOperator::subdivide(Mesh *srcMesh, bool cleanup, float smoothness)
{
	Mesh *dstMesh = 0;

	Mesh::EdgeInfo *edgeInfo = srcMesh->constructEdgeInfo();

	{
		int numTriangles = srcMesh->getNumTriangles() * 4;
		int numQuads = srcMesh->getNumQuads() * 4;
		int numVertices = srcMesh->getNumVertices() + edgeInfo->getNumEdges() + srcMesh->getNumQuads();

		dstMesh = new Mesh(numVertices, numTriangles, numQuads, srcMesh->getNumUVSets());
		dstMesh->setSelectedUVSet(srcMesh->getSelectedUVSet());
	}	

	int startEdgeSplits = srcMesh->getNumVertices();
	int startQuadSplits = startEdgeSplits + edgeInfo->getNumEdges();

	// Copy original vertices
	for (int i = 0; i < srcMesh->getNumVertices(); i++)
	{
		dstMesh->pos(i) = srcMesh->pos(i);
		dstMesh->normal(i) = srcMesh->normal(i);
		for (int j = 0; j < srcMesh->getNumUVSets(); j++)
		{
			dstMesh->uv(i, j) = srcMesh->uv(i, j);
		}
	}

	// Put an extra vertex on each edge
	for (int i = 0; i < edgeInfo->getNumEdges(); i++)
	{
		int e0 = edgeInfo->getEdge(i)[0];
		int e1 = edgeInfo->getEdge(i)[1];
		dstMesh->pos(startEdgeSplits + i) = (srcMesh->pos(e0) + srcMesh->pos(e1)) / 2.0f;
		dstMesh->normal(startEdgeSplits + i) = (srcMesh->normal(e0) + srcMesh->normal(e1)) / 2.0f;
		float recLen = 1.0f / length(dstMesh->normal(startEdgeSplits + i));
		dstMesh->normal(startEdgeSplits + i) *= recLen;
		dstMesh->pos(startEdgeSplits + i) += dstMesh->normal(startEdgeSplits + i) * logf(recLen) * length(srcMesh->pos(e0) - srcMesh->pos(e1)) * smoothness;

		for (int j = 0; j < srcMesh->getNumUVSets(); j++)
		{
			dstMesh->uv(startEdgeSplits + i, j) = (srcMesh->uv(e0, j) + srcMesh->uv(e1, j)) / 2;
		}
	}

	// Put an extra vertex in the middle of each quad
	for (int i = 0; i < srcMesh->getNumQuads(); i++)
	{
		int e0 = srcMesh->quad(i)[0];
		int e1 = srcMesh->quad(i)[1];
		int e2 = srcMesh->quad(i)[2];
		int e3 = srcMesh->quad(i)[3];

		dstMesh->pos(startQuadSplits + i) = (srcMesh->pos(e0) + srcMesh->pos(e1) + srcMesh->pos(e2) + srcMesh->pos(e3)) / 4;
		dstMesh->normal(startQuadSplits + i) = normalize(srcMesh->normal(e0) + srcMesh->normal(e1) + srcMesh->normal(e2) + srcMesh->normal(e3));

		for (int j = 0; j < srcMesh->getNumUVSets(); j++)
		{
			dstMesh->uv(startQuadSplits + i, j) = (srcMesh->uv(e0, j) + srcMesh->uv(e1, j) + srcMesh->uv(e2, j) + srcMesh->uv(e3, j)) / 4;
		}
	}

	// Create subdivided triangles
	for (int i = 0; i < srcMesh->getNumTriangles(); i++)
	{
		int *srcInd = srcMesh->triangle(i);
		int ind[] = { 
			srcInd[0],
			srcInd[1],
			srcInd[2],
			startEdgeSplits + edgeInfo->getIndexOf(srcInd[0], srcInd[1]),
			startEdgeSplits + edgeInfo->getIndexOf(srcInd[1], srcInd[2]),
			startEdgeSplits + edgeInfo->getIndexOf(srcInd[2], srcInd[0])
		};

		dstMesh->setTriangle(i * 4 + 0, ind[0], ind[3], ind[5]);
		dstMesh->setTriangle(i * 4 + 1, ind[5], ind[4], ind[2]);
		dstMesh->setTriangle(i * 4 + 2, ind[5], ind[3], ind[4]);
		dstMesh->setTriangle(i * 4 + 3, ind[3], ind[1], ind[4]);
	}

	// Create subdivided quads
	for (int i = 0; i < srcMesh->getNumQuads(); i++)
	{
		int *srcInd = srcMesh->quad(i);
		int ind[] = { 
			srcInd[0],
			srcInd[1],
			srcInd[2],
			srcInd[3],
			startEdgeSplits + edgeInfo->getIndexOf(srcInd[0], srcInd[1]),
			startEdgeSplits + edgeInfo->getIndexOf(srcInd[1], srcInd[2]),
			startEdgeSplits + edgeInfo->getIndexOf(srcInd[2], srcInd[3]),
			startEdgeSplits + edgeInfo->getIndexOf(srcInd[3], srcInd[0]),
			startQuadSplits + i
		};

		dstMesh->setQuad(i * 4 + 0, ind[0], ind[4], ind[8], ind[7]);
		dstMesh->setQuad(i * 4 + 1, ind[4], ind[1], ind[5], ind[8]);
		dstMesh->setQuad(i * 4 + 2, ind[7], ind[8], ind[6], ind[3]);
		dstMesh->setQuad(i * 4 + 3, ind[8], ind[5], ind[2], ind[6]);
	}

	delete edgeInfo;

	if (cleanup)
	{
		delete srcMesh;
	}

	return dstMesh;
}