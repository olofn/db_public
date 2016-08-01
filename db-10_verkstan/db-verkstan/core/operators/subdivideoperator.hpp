#pragma once

#include "core/operator.hpp"

class SubdivideOperator: public Operator
{
public:
    void process(int tick);

private:
	Mesh* subdivide(Mesh *srcMesh, bool cleanup, float smoothness);
};