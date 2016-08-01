#pragma once

#include "core/operator.hpp"

class CloneMeshOperator: public Operator
{
public:
    void process(int tick);
};