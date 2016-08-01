#include "core/operators/clonemeshoperator.hpp"

void CloneMeshOperator::process(int tick)
{
    if (mesh != 0)
        delete mesh;

    unsigned char clones = getByteProperty(0);
    D3DXVECTOR3 scaleVector = getVectorProperty(1);
    D3DXVECTOR3 rotationVector = getVectorProperty(2);
    D3DXVECTOR3 translationVector = getVectorProperty(3);
    D3DXMATRIX scaleMatrix;
    D3DXMatrixScaling(&scaleMatrix, 
                      scaleVector.x, 
                      scaleVector.y, 
                      scaleVector.z);
    D3DXMATRIX rotationXMatrix;
    D3DXMatrixRotationX(&rotationXMatrix, rotationVector.x);
    D3DXMATRIX rotationYMatrix;
    D3DXMatrixRotationY(&rotationYMatrix, rotationVector.y);
    D3DXMATRIX rotationZMatrix;
    D3DXMatrixRotationZ(&rotationZMatrix, rotationVector.z);
    D3DXMATRIX translationMatrix;
    D3DXMatrixTranslation(&translationMatrix,
                          translationVector.x,
                          translationVector.y,
                          translationVector.z);
    D3DXMATRIX cloneMatrix = scaleMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * translationMatrix;

    Mesh* srcMesh = getInput(0)->mesh;

    mesh = new Mesh(srcMesh->getNumVertices() * clones,
                    srcMesh->getNumTriangles() * clones,
                    srcMesh->getNumQuads() * clones);

    D3DXMATRIX matrix;
    D3DXMatrixIdentity(&matrix);

    int c = 0;
    int verticeOffset = 0;
    int triangleIndex = 0;
    int quadIndex = 0;
    do
    {
        c++;
        for (int v = 0; v < srcMesh->getNumVertices(); v++)
        {
            Vec3 pos = srcMesh->pos(v);
            Vec3 transformedPos;
            D3DXVec3TransformCoord(&transformedPos, &pos, &matrix);
            mesh->pos(verticeOffset + v) = transformedPos;
            mesh->uv(verticeOffset + v) = srcMesh->uv(v);
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
        matrix *= cloneMatrix;
    }
    while (c < clones);
}