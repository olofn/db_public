#pragma once

#include "core/operator.hpp"

class BoxOperator: public Operator
{
public:
    void process(int tick);
};