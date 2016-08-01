#pragma once

#include "core/operator.hpp"

class MegaExtrudeOperator: public Operator
{
public:
    void process(int tick);
};