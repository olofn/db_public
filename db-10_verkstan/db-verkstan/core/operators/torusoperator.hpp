#pragma once

#include "core/operator.hpp"

class TorusOperator: public Operator
{
public:
    void process(int tick);
};