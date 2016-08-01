#include "transformuvoperator.hpp"

void TransformUVOperator::process(int tick)
{
    if (mesh != 0)
        delete mesh;

    unsigned char set = getByteProperty(0);
    D3DXVECTOR4 scaleVector = getVectorProperty(1);
    D3DXVECTOR4 rotationVector = getVectorProperty(2);
    D3DXVECTOR4 translationVector = getVectorProperty(3);
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
        Vec2 pos = mesh->uv(i, set);
        Vec3 poss = Vec3(pos.x, pos.y, 1.0f);
        Vec4 result;
        D3DXVec3Transform(&result, &poss, &matrix);
        mesh->uv(i, set) = Vec2(result.x, result.y);
    }
}
