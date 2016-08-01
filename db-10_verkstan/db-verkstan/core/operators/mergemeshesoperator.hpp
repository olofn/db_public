#pragma once

#include "core/operator.hpp"

class MergeMeshesOperator: public Operator
{
public:
    void process(int tick);
};