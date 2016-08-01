#pragma once

#include "core/operator.hpp"

class RotozoomOperator: public Operator
{
public:
    void process(int tick);
};