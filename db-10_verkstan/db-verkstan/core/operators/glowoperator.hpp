#pragma once

#include "core/operator.hpp"

class GlowOperator: public Operator
{
public:
    void process(int tick);
};