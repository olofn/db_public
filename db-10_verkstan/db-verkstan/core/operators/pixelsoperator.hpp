#pragma once

#include "core/operator.hpp"

class PixelsOperator: public Operator
{
public:
    void process(int tick);
};