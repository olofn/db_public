#pragma once

#include "core/operator.hpp"

class DistortionOperator: public Operator
{
public:
    void process(int tick);
};