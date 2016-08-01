#include "core/globals.hpp"
#include "core/mesh.hpp"

Mesh::Mesh(int _numVertices, int _numTriangles, int _numQuads, int _numUVSets, bool _vertexColors) :
	triangleData(0),
	quadData(0),
	selectedUVSet(0),
	numVertices(_numVertices),
	numTriangles(_numTriangles),
	numQuads(_numQuads),
	numUVSets(_numUVSets),
	fvf(0),
	vertexBuffer(0),
	indexBuffer(0),
	vertexColors(_vertexColors ? 1 : 0)
{
	vertexStride = 6 + 2 * numUVSets + vertexColors;
	vertexData = new float[numVertices * vertexStride];
	ZeroMemory(vertexData, sizeof(float) * numVertices * vertexStride);

	if (numTriangles) 
	{
		triangleData = new int[numTriangles * 3];
		ZeroMemory(triangleData, sizeof(int) * numTriangles * 3);
	}

	if (numQuads)
	{
		quadData = new int[numQuads * 4];
		ZeroMemory(quadData, sizeof(int) * numQuads * 4);
	}

	faceSelection = new bool[getNumFaces()];
	ZeroMemory(faceSelection, sizeof(bool) * getNumFaces());

    //vertexSelection = new bool[numVertices];
    //ZeroMemory(vertexSelection, sizeof(bool) * numVertices);
}


Mesh::Mesh(const Mesh& mesh) : 
	triangleData(0),
	quadData(0),
	selectedUVSet(mesh.selectedUVSet),
	numVertices(mesh.numVertices),
	numTriangles(mesh.numTriangles),
	numQuads(mesh.numQuads),
	numUVSets(mesh.numUVSets),
	fvf(0),
	vertexBuffer(0),
	indexBuffer(0),
	vertexColors(mesh.vertexColors)
{
	vertexStride = 6 + 2 * numUVSets + vertexColors;
	vertexData = new float[numVertices * vertexStride];
	memcpy(vertexData, mesh.vertexData, sizeof(float) * vertexStride * numVertices);

	if (numTriangles) 
	{
		triangleData = new int[numTriangles * 3];
		memcpy(triangleData, mesh.triangleData, sizeof(int) * numTriangles * 3);
	}
	
	if (numQuads) 
	{
		quadData = new int[numQuads * 4];
		memcpy(quadData, mesh.quadData, sizeof(int) * numQuads * 4);
	}

	faceSelection = new bool[getNumFaces()];
	memcpy(faceSelection, mesh.faceSelection, sizeof(bool) * getNumFaces());

  //  vertexSelection = new bool[numVertices];
  //  memcpy(vertexSelection, mesh.vertexSelection, sizeof(bool) * numVertices);
}


Mesh::~Mesh()
{
	destroyD3DBuffers();
	delete[] vertexData;
	delete[] triangleData;
	delete[] quadData;
}


void Mesh::render()
{
	if (!(indexBuffer && vertexBuffer))
	{
		createD3DBuffers();
	}

	globalDirect3DDevice->SetFVF(fvf);
	globalDirect3DDevice->SetStreamSource(0, vertexBuffer, 0, vertexStride * sizeof(float));
	globalDirect3DDevice->SetIndices(indexBuffer);

	globalDirect3DDevice->DrawIndexedPrimitive
	(
		D3DPT_TRIANGLELIST,					// Type
		0,									// BaseVertexIndex
		0,									// MinIndex
		numVertices,						// NumVertices
		0,									// StartIndex
		numTriangles + 2 * numQuads			// PrimitiveCount
	);
}


Vec3 &Mesh::pos(int vertexIndex)
{
	return *((Vec3*)(vertexData + vertexIndex * vertexStride));
}


unsigned int &Mesh::color(int vertexIndex)
{
	return *((unsigned int*)(vertexData + vertexIndex * vertexStride + 6));
}


Vec3 &Mesh::normal(int vertexIndex)
{
	return *((Vec3*)(vertexData + vertexIndex * vertexStride + 3));
}


Vec2 &Mesh::uv(int vertexIndex)
{
	return uv(vertexIndex, selectedUVSet);
}


Vec2 &Mesh::uv(int vertexIndex, int uvSet)
{
	return *((Vec2*)(vertexData + vertexIndex * vertexStride + 6 + 2 * uvSet + vertexColors));
}


int *Mesh::triangle(int triangleIndex)
{
	return triangleData + triangleIndex * 3;
}


int *Mesh::quad(int quadIndex)
{
	return quadData + quadIndex * 4;
}


void Mesh::setTriangle(int triangleIndex, int v0, int v1, int v2)
{
	int *o = triangle(triangleIndex);
	o[0] = v0;
	o[1] = v1;
	o[2] = v2;
}


void Mesh::setQuad(int quadIndex, int v0, int v1, int v2, int v3)
{
	int *o = quad(quadIndex);
	o[0] = v0;
	o[1] = v1;
	o[2] = v2;
	o[3] = v3;
}


void Mesh::setFace(int faceIndex, int *v)
{
	if (faceIndex < numTriangles)
	{
		setTriangle(faceIndex, v[0], v[1], v[2]);
	}
	else
	{
		setQuad(faceIndex - numTriangles, v[0], v[1], v[2], v[3]);
	}
}


int *Mesh::face(int faceIndex, int &outNumVertices)
{
	if (faceIndex < numTriangles)
	{
		outNumVertices = 3;
		return triangle(faceIndex);
	}
	else
	{
		outNumVertices = 4;
		return quad(faceIndex - numTriangles);
	}
}


static int edgeComparator(const void *_e1, const void *_e2)
{
	int *e1 = (int *)_e1;
	int *e2 = (int *)_e2;

	int r = e1[0] - e2[0];
	return r == 0 ? e1[1] - e2[1] : r;
}


Mesh::EdgeInfo *Mesh::constructEdgeInfo()
{
	int numDuplicatedEdges = numTriangles * 3 + numQuads * 4;
	int *duplicatedEdges = new int[numDuplicatedEdges * 2];
	int i = 0;

	// Put all edges in edges array, don't care about duplicates right now,
	// but order indices for each edge (smallest first)
	for (int f = 0; f < getNumFaces(); f++)
	{
		int sides;
		int *facePtr = face(f, sides);

		for (int e = 0; e < sides; e++)
		{
			int v1 = facePtr[e];
			int v2 = facePtr[(e + 1) % sides];
			if (v1 < v2)
			{
				duplicatedEdges[i] = v1;
				duplicatedEdges[i + 1] = v2;
			}
			else
			{
				duplicatedEdges[i] = v2;
				duplicatedEdges[i + 1] = v1;
			}
			i += 2;
		}
	}

	// Sort the edges
	qsort((void *)duplicatedEdges, numDuplicatedEdges, sizeof(int) * 2, edgeComparator);
	
	int numEdges = 0;
	
	// Count the edges
	{
		int last1 = -1, last2 = -1;
		for (int e = 0; e < numDuplicatedEdges; e++)
		{		
			int e1 = duplicatedEdges[e * 2];
			int e2 = duplicatedEdges[e * 2 + 1];
			if (e2 != last2 || e1 != last1)
			{
				numEdges++;
			}
			last1 = e1;
			last2 = e2;
		}
	}

	int *edges = new int[numEdges * 2];
	
	// Create proper edges array without duplicates
	{
		int i = 0;
		int last1 = -1, last2 = -1;
		for (int e = 0; e < numDuplicatedEdges; e++)
		{		
			int e1 = duplicatedEdges[e * 2];
			int e2 = duplicatedEdges[e * 2 + 1];
			if (e2 != last2 || e1 != last1)
			{
				edges[i * 2] = e1;
				edges[i * 2 + 1] = e2;
				i++;
			}
			last1 = e1;
			last2 = e2;			
		}
	}

	delete[] duplicatedEdges;

	return new EdgeInfo(edges, numEdges);
}


static Vec3 sortAxisProjector;
static Mesh* sortAxisMesh;
static int projectedComparator(const void *_i1, const void *_i2)
{
	int i1 = *(int *)_i1;
	int i2 = *(int *)_i2;

	Vec3 p1 = sortAxisMesh->pos(i1);
	Vec3 p2 = sortAxisMesh->pos(i2);

	float j1 = dot(p1, sortAxisProjector);
	float j2 = dot(p2, sortAxisProjector);

	return j1 < j2 ? -1 : 1;
}

int *Mesh::constructSortedVertexIndices(Vec3 sortAxis)
{
	sortAxisProjector = sortAxis;
	sortAxisMesh = this;

	int *result = new int[getNumVertices()];

	for (int i = 0; i < getNumVertices(); i++)
	{
		result[i] = i;
	}	

	qsort(result, getNumVertices(), sizeof(int), projectedComparator);

	return result;
}


Mesh::BoxedMesh *Mesh::constructBoxedMesh(float boxSize)
{
	return new BoxedMesh(this, boxSize);
}


Vec3 Mesh::getTriangleNormal(int triangleIndex)
{
	int *verts = triangle(triangleIndex);
	return cross(pos(verts[1]) - pos(verts[0]),	pos(verts[2]) - pos(verts[0]));
}


Vec3 Mesh::getQuadNormal(int quadIndex)
{
	int *verts = quad(quadIndex);
	return (cross(pos(verts[1]) - pos(verts[0]), pos(verts[3]) - pos(verts[0])) +		   
		    cross(pos(verts[3]) - pos(verts[2]), pos(verts[1]) - pos(verts[2]))) / 2.0f;
}


Vec3 Mesh::getFaceNormal(int faceIndex)
{
	if (faceIndex < numTriangles)
	{
		return getTriangleNormal(faceIndex);
	}
	else
	{
		return getQuadNormal(faceIndex - numTriangles);
	}
}


bool &Mesh::faceSelected(int faceIndex)
{
	return faceSelection[faceIndex];
}


//bool &Mesh::vertexSelected(int vertexIndex)
//{
//	return vertexSelection[vertexIndex];
//}


void Mesh::recalculateNormals()
{
	for (int i = 0; i < getNumVertices(); i++)
	{
		normal(i) = Vec3(0, 0, 0);
	}

	for (int i = 0; i < getNumFaces(); i++)
	{
		int size;
		int *verts = face(i, size);
		Vec3 n = getFaceNormal(i);

		for (int v = 0; v < size; v++)
		{
			normal(verts[v]) += n;			
		}
	}

	for (int i = 0; i < getNumVertices(); i++)
	{
		normal(i) = normalize(normal(i));
	}
}


void Mesh::createD3DBuffers()
{
	destroyD3DBuffers();

	// CREATE VERTEX BUFFER
	{
		int vertexBytes = numVertices * vertexStride * sizeof(float);

		fvf = D3DFVF_XYZ | D3DFVF_NORMAL | (numUVSets << D3DFVF_TEXCOUNT_SHIFT) | (vertexColors * D3DFVF_DIFFUSE);

		globalDirect3DDevice->CreateVertexBuffer
		( 
			vertexBytes,		// Length
			0,					// Usage
			fvf,				// FVF
			D3DPOOL_DEFAULT,	// Pool
			&vertexBuffer,		// ppVertexBuffer
			NULL				// pSharedHandle
		);

		void *vertexBufferData;
		vertexBuffer->Lock(0, vertexBytes, &vertexBufferData, 0);
		memcpy(vertexBufferData, vertexData, vertexBytes);	
		vertexBuffer->Unlock();
	}


	// CREATE INDEX BUFFER
	{
		int triangleBytes = numTriangles * sizeof(int) * 3;
		int quadBytes = numQuads * 2 * sizeof(int) * 3;
		int indexBytes = triangleBytes + quadBytes;

		globalDirect3DDevice->CreateIndexBuffer(
			indexBytes,			// Length
			0,					// Usage
			D3DFMT_INDEX32,		// Format
			D3DPOOL_DEFAULT,	// Pool
			&indexBuffer,		// ppIndexBuffer
			NULL				// pSharedHandle
		);

		int *indexBufferData;
		indexBuffer->Lock(0, indexBytes, (void **)(&indexBufferData), 0);
		
		// Simply copy in triangle data since it is in the right format
		memcpy(indexBufferData, triangleData, triangleBytes);
	
		// Quads needs some processing
		for (int i = 0; i < numQuads; i++)
		{
			int *q = quad(i);
			int offset = numTriangles * 3 + i * 6;
			indexBufferData[offset + 0] = q[0];
			indexBufferData[offset + 1] = q[1];
			indexBufferData[offset + 2] = q[3];
			indexBufferData[offset + 3] = q[1];
			indexBufferData[offset + 4] = q[2];
			indexBufferData[offset + 5] = q[3];
		}

		indexBuffer->Unlock();
	}

}


void Mesh::destroyD3DBuffers()
{
	if (vertexBuffer) { vertexBuffer->Release(); vertexBuffer = 0; }
	if (indexBuffer)  { indexBuffer->Release();  indexBuffer = 0;  }
}


void Mesh::debugPrint()
{
    /*
	System::Console::WriteLine("Num Vertices: " + numVertices);
	for(int i = 0; i < numVertices; i++)
	{
		for(int j = 0; j < vertexStride; j++)
		{
			System::Console::Write(vertexData[i * vertexStride + j] + " ");
		}
		System::Console::WriteLine();
	}

	System::Console::WriteLine("Num Triangles: " + numTriangles);
	for(int i = 0; i < numTriangles; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			System::Console::Write(triangleData[i * 3 + j] + " ");
		}
		System::Console::WriteLine();
	}

	
	System::Console::WriteLine("Num Quads: " + numQuads);
	for(int i = 0; i < numQuads; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			System::Console::Write(quadData[i * 4 + j] + " ");
		}
		System::Console::WriteLine();
	}
    */
}



///////////////////////
// EdgeInfo
///////////////////////

Mesh::EdgeInfo::EdgeInfo(int *_edges, int _numEdges) :
	edges(_edges),
	numEdges(_numEdges)
{
}

Mesh::EdgeInfo::~EdgeInfo()
{
	delete[] edges;
}

int Mesh::EdgeInfo::getNumEdges()
{
	return numEdges;
}

int *Mesh::EdgeInfo::getEdge(int i)
{
	return edges + i * 2;
}

int Mesh::EdgeInfo::getIndexOf(int v1, int v2)
{
	int key[2];
	if (v1 < v2)
	{
		key[0] = v1;
		key[1] = v2;
	}
	else
	{
		key[0] = v2;
		key[1] = v1;
	}

	int min = 0;
	int max = getNumEdges();

	while(true)
	{
		if (min == max)
		{
			// Not found
			return -1;
		}

		int sample = min + (max - min) / 2;
		int *edge = getEdge(sample);		
		int r = edgeComparator(edge, key);

		if (r == 0)
		{
			return sample;
		}
		else if (r < 0)
		{
			min = sample + 1;
		}
		else if (r > 0)
		{
			max = sample;
		}
	}
}



///////////////////////
// BoxedMesh
///////////////////////

Mesh::BoxedMesh::BoxedMesh(Mesh *mesh_, float boxSize_) : 
	boxSize(boxSize_),
	mesh(mesh_)
{
	minPos = maxPos = mesh->pos(0);
	for (int i = 1; i < mesh->getNumVertices(); i++)
	{
		Vec3 p = mesh->pos(i);
		minPos = Vec3(min(minPos.x, p.x), min(minPos.y, p.y), min(minPos.z, p.z));
		maxPos = Vec3(max(maxPos.x, p.x), max(maxPos.y, p.y), max(maxPos.z, p.z));
	}

	size = maxPos - minPos;
	numBoxesX = (int)ceil((double)size.x / boxSize);
	numBoxesY = (int)ceil((double)size.y / boxSize);
	numBoxesZ = (int)ceil((double)size.z / boxSize);
	numBoxesTotal = numBoxesX * numBoxesY * numBoxesZ;

	boxes = new Box[numBoxesTotal];

	int guessedVertsPerBox = max((mesh->getNumVertices() * 2) / numBoxesTotal, 1);

	for (int i = 1; i < mesh->getNumVertices(); i++)
	{
		int x, y, z;
		getBoxFor(x, y, z, i);
		Box &box = get(x, y, z);

		if (box.allocated == 0)
		{
			box.allocated = guessedVertsPerBox;
			box.vertices = new int[guessedVertsPerBox];
		}
		else if (box.allocated == box.size)
		{
			int newAllocation = box.allocated * 2;
			int *newVertices = new int[newAllocation];
			memcpy(newVertices, box.vertices, box.allocated * sizeof(int));
			delete[] box.vertices;
			box.vertices = newVertices;
			box.allocated = newAllocation;
		}

		box.vertices[box.size] = i;
		box.size++;
	}
}

Mesh::BoxedMesh::~BoxedMesh()
{
	for (int i = 0; i < numBoxesTotal; i++)
	{
		delete[] boxes[i].vertices;
	}
	delete[] boxes;
}

Mesh::BoxedMesh::Box &Mesh::BoxedMesh::get(int x, int y, int z)
{
	static Box emptyBox;

	if (x < 0 || x >= numBoxesX ||
		y < 0 || y >= numBoxesY ||
		z < 0 || z >= numBoxesZ)
	{
		return emptyBox;
	}

	return boxes[x + y * numBoxesX + z * numBoxesX * numBoxesY];
}

void Mesh::BoxedMesh::getBoxFor(int &outX, int &outY, int &outZ, int vertex)
{
	Vec3 p = mesh->pos(vertex) - minPos;
	outX = (int)floor((double)p.x / boxSize);
	outY = (int)floor((double)p.y / boxSize);
	outZ = (int)floor((double)p.z / boxSize);
}