#include "core/operators/addmodelsoperator.hpp"

void AddModelsOperator::render()
{
    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->render();
}

void AddModelsOperator::process(int tick)
{
   
}
