#include "core/operators/mergemeshesoperator.hpp"

void MergeMeshesOperator::process(int tick)
{
    if (mesh != 0)
        delete mesh;

    int numberOfVertices = 0;
    int numberOfQuads = 0;
    int numberOfTriangles = 0;
    for (int i = 0; i < numberOfInputs; i++)
    {
        numberOfVertices += getInput(i)->mesh->getNumVertices();
        numberOfQuads += getInput(i)->mesh->getNumQuads();
        numberOfTriangles += getInput(i)->mesh->getNumTriangles();
    }

    mesh = new Mesh(numberOfVertices, numberOfTriangles, numberOfQuads);

    int triangleIndex = 0;
    int quadIndex = 0;
    int verticeOffset = 0;
    for (int i = 0; i < numberOfInputs; i++)
    {
        Mesh* srcMesh = getInput(i)->mesh;
      
        for (int v = 0; v < srcMesh->getNumVertices(); v++)
        {
            mesh->pos(v + verticeOffset) = srcMesh->pos(v);
            mesh->uv(v + verticeOffset) = srcMesh->uv(v);
        }

        for (int f = 0; f < srcMesh->getNumFaces(); f++)
        {
            int n;
            int* face = srcMesh->face(f, n);

            if (n == 3)
            {
                mesh->setTriangle(triangleIndex, 
                                  verticeOffset + face[0], 
                                  verticeOffset + face[1], 
                                  verticeOffset + face[2]);
                triangleIndex++;
            }
            else
            {
                mesh->setQuad(quadIndex, 
                              verticeOffset + face[0], 
                              verticeOffset + face[1], 
                              verticeOffset + face[2], 
                              verticeOffset + face[3]);
                quadIndex++;
            }
        }

        verticeOffset += srcMesh->getNumVertices();
    }

    mesh->recalculateNormals();
}
