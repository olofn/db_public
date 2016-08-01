#pragma once

using namespace System;

#include "cli/Constants.hpp"

namespace Verkstan
{
    public ref class CoreOperatorInput
    {
    public:
        CoreOperatorInput(int index,
                          Constants::OperatorTypes type,
                          bool infinite,
                          bool optional);
        property bool Infinite;
        property bool Optional;
        property Constants::OperatorTypes Type;
        property int Index;
    };
}