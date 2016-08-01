#pragma once

#include "core/operator.hpp"

class BlurOperator: public Operator
{
public:
    void process(int tick);
};