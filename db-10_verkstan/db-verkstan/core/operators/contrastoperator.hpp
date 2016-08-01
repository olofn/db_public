#pragma once

#include "core/operator.hpp"

class ContrastOperator: public Operator
{
public:
    void process(int tick);
};