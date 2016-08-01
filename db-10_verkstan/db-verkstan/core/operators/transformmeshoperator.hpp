#pragma once

#include "core/operator.hpp"

class TransformMeshOperator: public Operator
{
public:
    void process(int tick);
};