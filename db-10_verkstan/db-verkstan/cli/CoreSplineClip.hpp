#pragma once

#include "cli/CoreClip.hpp"
#include "cli/Constants.hpp"

using namespace System;

namespace Verkstan
{
    public ref class CoreSplineClip: public CoreClip
    {
    public:
        CoreSplineClip();
        ~CoreSplineClip();
        property unsigned short Id
        {
            unsigned short get();
        }
        void SetNumberOfControlPoints(int number);
        int GetNumberOfControlPoints();
        void SetControlPoint(int index, int tick, char value);
        int GetControlPointTick(int index);
        char GetControlPointValue(int index);
        void SetSplineType(int type);
        int GetSplineType();

    private:
        Core::SplineClip* coreSplineClip;
        unsigned short id;
    };
}