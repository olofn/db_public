#pragma once

using namespace System;

namespace Verkstan
{
    public ref struct Vector
    {
    public:
        Vector();
        Vector(float x, float y, float z);
        float X;
        float Y;
        float Z;
    };
}