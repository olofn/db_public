#pragma once

#include "core/clip.hpp"

#define DB_MAX_SPLINE_CONTROL_POINTS 128

class SplineClip: public Clip
{
public:
    SplineClip();
    float getValue(int tick);
    
    struct ControlPoint
    {
        char value;
        int tick;
    };
    ControlPoint controlPoints[DB_MAX_SPLINE_CONTROL_POINTS];
    unsigned char numberOfControlPoints;
    unsigned char type;
private:
    ControlPoint getControlPoint(int index);
};