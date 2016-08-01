#pragma once

#include "core/operator.hpp"

class DisplacementMapOperator: public Operator
{
public:
    void process(int tick);
};