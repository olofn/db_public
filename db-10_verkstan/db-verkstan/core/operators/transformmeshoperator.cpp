#include "core/operators/transformmeshoperator.hpp"

void TransformMeshOperator::process(int tick)
{
    if (mesh != 0)
        delete mesh;

    D3DXVECTOR4 scaleVector = getVectorProperty(0);
    D3DXVECTOR4 rotationVector = getVectorProperty(1);
    D3DXVECTOR4 translationVector = getVectorProperty(2);
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
    D3DXMATRIX matrix = scaleMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * translationMatrix;

    mesh = getInput(0)->mesh->clone();

    for (int i = 0; i < mesh->getNumVertices(); i++)
    {
        Vec3 pos = mesh->pos(i);
        Vec4 result;
        D3DXVec3Transform(&result, &pos, &matrix);
        mesh->pos(i) = Vec3(result.x, result.y, result.z);
    }
}
