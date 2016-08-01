#include "cli/CoreOperatorInput.hpp"

namespace Verkstan
{
    CoreOperatorInput::CoreOperatorInput(int index,
                                         Constants::OperatorTypes type,
                                         bool infinite,
                                         bool optional)
    {
        Index = index;
        Type = type;
        Infinite = infinite;
        Optional = optional;
    }
}