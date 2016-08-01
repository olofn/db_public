#include "cli/CoreSplineClip.hpp"

namespace Verkstan
{
    CoreSplineClip::CoreSplineClip()
    {
        coreSplineClip = new Core::SplineClip();
        for (int i = 0; i < DB_MAX_CLIPS; i++)
        {   
            if (Core::coreClips[i] == 0)
            {
                Core::coreClips[i] = coreSplineClip;
                id = i;
                break;
            }
        }

        SetCoreClip(coreSplineClip);
    }

    CoreSplineClip::~CoreSplineClip()
    {
       Core::coreClips[id] = 0;
       delete coreSplineClip;
    }

    unsigned short CoreSplineClip::Id::get()
    {
        return id;
    }

    void CoreSplineClip::SetNumberOfControlPoints(int number)
    {
        coreSplineClip->numberOfControlPoints = number;
    }

    int CoreSplineClip::GetNumberOfControlPoints()
    {
        return coreSplineClip->numberOfControlPoints;
    }

    void CoreSplineClip::SetControlPoint(int index, int tick, char value)
    {
        if (tick < 0)
            tick = 0;
        coreSplineClip->controlPoints[index].tick = tick;
        coreSplineClip->controlPoints[index].value = value;
    }

    int CoreSplineClip::GetControlPointTick(int index)
    {
        return coreSplineClip->controlPoints[index].tick;
    }

    char CoreSplineClip::GetControlPointValue(int index)
    {
        return coreSplineClip->controlPoints[index].value;
    }

    void CoreSplineClip::SetSplineType(int type)
    {
        coreSplineClip->type = type;
    }

    int CoreSplineClip::GetSplineType()
    {
        return coreSplineClip->type;
    }
}