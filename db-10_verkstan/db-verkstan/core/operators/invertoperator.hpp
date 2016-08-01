#pragma once

#include "core/operator.hpp"

class InvertOperator: public Operator
{
public:
    void process(int tick);
};