#include "core/operators/transformmodeloperator.hpp"

void TransformModelOperator::render()
{
    globalWorldMatrixStack->Push();
    globalWorldMatrixStack->MultMatrixLocal(&matrix);
    getInput(0)->render();
    globalWorldMatrixStack->Pop();
}

void TransformModelOperator::process(int tick)
{
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
    matrix = scaleMatrix * rotationXMatrix * rotationYMatrix * rotationZMatrix * translationMatrix; 
}
