#include "core/splineclip.hpp"
#include "core/core.hpp"

SplineClip::SplineClip()
:numberOfControlPoints(0),
type(0)
{
  
}

float SplineClip::getValue(int tick)
{
    int index;
    for (index = 0; index < numberOfControlPoints; index++)
    {
        if (controlPoints[index].tick > tick)
        {
            break;
        }
    }

    if (type == 2) // On Off
    {
        return index % 2 == 0 ? -1.0f : 1.0f;
    }

    if (numberOfControlPoints == 0)
        return 0.0f;
    if (numberOfControlPoints == 1)
        return controlPoints[0].value / 128.0f;
    if (controlPoints[0].tick >= tick)
        return controlPoints[0].value / 128.0f;
    if (controlPoints[numberOfControlPoints - 1].tick <= tick)  
        return controlPoints[numberOfControlPoints - 1].value  / 128.0f;

    index--;
    ControlPoint p2 = getControlPoint(index);
    ControlPoint p3 = getControlPoint(index + 1);

    float t = (tick - p2.tick) / (float)(p3.tick - p2.tick); 

    if (type == 1) // Linear
    {
        return  (1.0f - t) * (p2.value  / 128.0f) + (p3.value  / 128.0f) * t;
    }

    ControlPoint p1 = getControlPoint(index - 1);
    ControlPoint p4 = getControlPoint(index + 2);

    if (type == 0) // Catmull-Rom
    {
        float t2 = 0.5f * (p3.value - p1.value) / 128.0f;
        float t3 = 0.5f * (p4.value - p2.value) / 128.0f;
            
        float h1 = 2.0f*t*t*t - 3.0f*t*t + 1.0f;
        float h2 = -2.0f*t*t*t + 3.0f*t*t;
        float h3 = t*t*t - 2.0f*t*t + t;
        float h4 = t*t*t - t*t; 

        return h1*p2.value/128.0f + h2*p3.value/128.0f + h3*t2 + h4*t3;
    }
}

SplineClip::ControlPoint SplineClip::getControlPoint(int index)
{
    if (index < 0)
    {
        ControlPoint p = controlPoints[0];
        p.tick = - 256*(-1*index);
        return p;
    }

    if (index >= numberOfControlPoints)
    {
        ControlPoint p = controlPoints[numberOfControlPoints - 1];
        p.tick += 256*index;
        return p;
    }

    return controlPoints[index];
}
