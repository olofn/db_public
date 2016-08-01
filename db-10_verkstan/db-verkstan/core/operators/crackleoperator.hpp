#pragma once

#include "core/operator.hpp"

class CrackleOperator: public Operator
{
public:
    void process(int tick);
};