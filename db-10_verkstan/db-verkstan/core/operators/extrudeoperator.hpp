#pragma once

#include "core/operator.hpp"

class ExtrudeOperator: public Operator
{
public:
    void process(int tick);
};