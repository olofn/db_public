#pragma once

#include "core/operator.hpp"

class MergeTexturesOperator: public Operator
{
public:
    void process(int tick);
};