#pragma once

#include "core/operator.hpp"

class BlendOperator: public Operator
{
public:
    void process(int tick);
};