#pragma once

#include "core/operator.hpp"

class RandomSelectionOperator: public Operator
{
public:
    void process(int tick);
};