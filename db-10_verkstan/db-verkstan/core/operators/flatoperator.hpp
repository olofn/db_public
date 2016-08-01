#pragma once

#include "core/operator.hpp"

class FlatOperator: public Operator
{
public:
    void process(int tick);
};