#pragma once

#include "cli/Core.hpp"

using namespace System;

namespace Verkstan
{
    public ref class CoreClip
    {
    public:
        CoreClip();
        virtual ~CoreClip();
        int GetStart();
        void SetStart(int start);
        int GetEnd();
        void SetEnd(int end);
        float GetValue(int tick);
        unsigned char GetChannel();
        void SetChannel(unsigned char channel);
    protected:
        void SetCoreClip(Core::Clip* coreClip);

    private:
        Core::Clip* coreClip;
    };
}