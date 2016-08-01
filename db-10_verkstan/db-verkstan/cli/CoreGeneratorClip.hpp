#pragma once

#include "cli/CoreClip.hpp"
#include "cli/Constants.hpp"

using namespace System;

namespace Verkstan
{
    public ref class CoreGeneratorClip: public CoreClip
    {
    public:
        CoreGeneratorClip();
        ~CoreGeneratorClip();
        property unsigned short Id
        {
            unsigned short get();
        }

        int GetPeriod();
        void SetPeriod(int period);
        int GetGeneratorType();
        void SetGeneratorType(int type);

    private:
        Core::GeneratorClip* coreGeneratorClip;
        unsigned short id;
    };
}