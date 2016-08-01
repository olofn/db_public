#pragma once

#include "core/operator.hpp"

class ColorizeOperator: public Operator
{
public:
    void process(int tick);
};