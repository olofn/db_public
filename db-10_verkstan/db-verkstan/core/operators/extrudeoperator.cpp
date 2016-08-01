#include "core/operators/extrudeoperator.hpp"

void ExtrudeOperator::process(int tick)
{
    if (mesh != 0)
        delete mesh;

	float distance = getFloatProperty(0);
	Mesh *srcMesh = getInput(0)->mesh;

	Mesh::EdgeInfo *edgeInfo = srcMesh->constructEdgeInfo();

	int *edgeSelected = new int[edgeInfo->getNumEdges()];
	ZeroMemory(edgeSelected, sizeof(int) * edgeInfo->getNumEdges());
	bool *edgeFlipped = new bool[edgeInfo->getNumEdges()];
	ZeroMemory(edgeFlipped, sizeof(bool) * edgeInfo->getNumEdges());	
	bool *vertexSelected = new bool[srcMesh->getNumVertices()];
	ZeroMemory(vertexSelected, sizeof(bool) * srcMesh->getNumVertices());
	int *extrudedVertex = new int[srcMesh->getNumVertices()];
	int numEdgeSelected = 0;

	for (int i = 0; i < srcMesh->getNumFaces(); i++)
	{
		if (!srcMesh->faceSelected(i)) 
		{
			continue;
		}

		int size;
		int *vert = srcMesh->face(i, size);

		for (int v = 0; v < size; v++)
		{
			int edge = edgeInfo->getIndexOf(vert[v], vert[(v + 1) % size]);
			edgeSelected[edge]++;
			edgeFlipped[edge] = edgeInfo->getEdge(edge)[0] != vert[v];	
			vertexSelected[vert[v]] = true;
		}
	}

	{
		for (int i = 0; i < srcMesh->getNumVertices(); i++)
		{
			extrudedVertex[i] = i;
		}

		int t = srcMesh->getNumVertices();

		for (int i = 0; i < edgeInfo->getNumEdges(); i++)
		{
			if (edgeSelected[i] == 1)
			{
				//System::Console::WriteLine("Process edge: " + i);
				int *e = edgeInfo->getEdge(i);

				for (int j = 0; j < 2; j++)
				{
					if (extrudedVertex[e[j]] == e[j])
					{						
						extrudedVertex[e[j]] = t;
						t++;
					}
				}

				numEdgeSelected++;
			}
		}
	}


	{
		int numVertices = srcMesh->getNumVertices() + numEdgeSelected;
		int numTriangles = srcMesh->getNumTriangles();
		int numQuads = srcMesh->getNumQuads() + numEdgeSelected;
		mesh = new Mesh(numVertices, numTriangles, numQuads, srcMesh->getNumUVSets());
		mesh->setSelectedUVSet(srcMesh->getSelectedUVSet());
	}
	
	// Copy original vertices
	for (int i = 0; i < srcMesh->getNumVertices(); i++)
	{
		mesh->pos(i) = srcMesh->pos(i);		
		
		for (int j = 0; j < srcMesh->getNumUVSets(); j++)
		{
			mesh->uv(i, j) = srcMesh->uv(i, j);
		}

		if (extrudedVertex[i] != i)
		{
			// TODO: Extrude using face normal?
			mesh->pos(extrudedVertex[i]) = srcMesh->pos(i) + srcMesh->normal(i) * distance;

			for (int j = 0; j < srcMesh->getNumUVSets(); j++)
			{
				mesh->uv(extrudedVertex[i], j) = srcMesh->uv(i, j);
			}
		}
		else if (vertexSelected[i])
		{
			mesh->pos(i) = srcMesh->pos(i) + srcMesh->normal(i) * distance;
		}
	}

	// Copy faces, with extrude
	for (int i = 0; i < srcMesh->getNumFaces(); i++)
	{
		int size;
		int *vert = srcMesh->face(i, size);
		int destVert[4];

		if (srcMesh->faceSelected(i))
		{
			for (int v = 0; v < size; v++)
			{
				destVert[v] = extrudedVertex[vert[v]];
			}
		}

		// This works simply because both meshes contain the same number of triangles
		mesh->setFace(i, destVert);
	}
	

	// Plug the holes
	{
		int q = srcMesh->getNumQuads();

		for (int i = 0; i < edgeInfo->getNumEdges(); i++)
		{
			if (edgeSelected[i] != 1)
			{
				continue;
			}

			int *e = edgeInfo->getEdge(i);
			if (edgeFlipped[i])
			{
				mesh->setQuad(q, e[1], e[0], extrudedVertex[e[0]], extrudedVertex[e[1]]);
			}
			else
			{
				mesh->setQuad(q, e[0], e[1], extrudedVertex[e[1]], extrudedVertex[e[0]]);
			}
			q++;
		}
	}

	mesh->recalculateNormals();

	delete[] edgeSelected;
	delete[] edgeFlipped;
	delete[] vertexSelected;
	delete[] extrudedVertex;
}
