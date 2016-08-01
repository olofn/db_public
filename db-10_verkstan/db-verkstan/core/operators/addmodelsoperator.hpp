#pragma once

#include "core/operator.hpp"

class AddModelsOperator: public Operator
{
public:
    void process(int tick);
    void render();
};