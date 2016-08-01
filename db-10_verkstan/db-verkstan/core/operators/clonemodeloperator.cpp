#include "core/operators/clonemodeloperator.hpp"

void CloneModelOperator::render()
{
    globalWorldMatrixStack->Push();

    getInput(0)->render();

    for (int i = 1; i < clones; i++)
    {
        globalWorldMatrixStack->MultMatrixLocal(&matrix);
        getInput(0)->render();
    }

    globalWorldMatrixStack->Pop();
}

void CloneModelOperator::process(int tick)
{
    clones = getByteProperty(0);
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
    matrix = scaleMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * translationMatrix;
}
