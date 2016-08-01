#include "cli/CoreOperator.hpp"

#include "cli/CoreOperatorProperty.hpp"

namespace Verkstan
{
    CoreOperatorProperty::CoreOperatorProperty(int index,
                                               String^ name, 
                                               Constants::OperatorPropertyTypes type)
    {
        Name = name;
        Type = type;
        Index = index;
    }

      
    CoreOperatorProperty::CoreOperatorProperty(int index,
                                               String^ name, 
                                               Constants::OperatorPropertyTypes type,
                                               List<String^>^ enumValues)
    {
        Name = name;
        Type = type;
        Index = index;
        EnumValues = enumValues;
    }
}