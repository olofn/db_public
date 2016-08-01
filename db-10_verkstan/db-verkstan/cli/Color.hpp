#pragma once

using namespace System;

namespace Verkstan
{
    public ref struct Color
    {
    public:
        Color();
        Color(unsigned char r, unsigned char g, unsigned char b);
        unsigned char R;
        unsigned char G;
        unsigned char B;
    };
}