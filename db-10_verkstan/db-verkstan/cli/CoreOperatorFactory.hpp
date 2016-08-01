#pragma once

#include "cli/Constants.hpp"

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan 
{
    ref class CoreOperator;

    public ref class CoreOperatorFactory
    {
    public:
        static ICollection<String^>^ GetCategories();
        static ICollection<String^>^ GetNamesInCategory(String^ category);
        static CoreOperator^ Create(String^ typeName);
     
    private:
        static void CreateCategories();
        static Dictionary<String^, List<String^>^>^ categories;
    };
}