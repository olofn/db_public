#pragma once

#include "core/operator.hpp"

class WeldOperator: public Operator
{
public:
    void process(int tick);
};