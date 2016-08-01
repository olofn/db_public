#pragma once

#include "core/operator.hpp"

class PlaneOperator: public Operator
{
public:
    void process(int tick);
};