#pragma once

class Clip
{
public:
    virtual float getValue(int tick) = 0;
    int start;
    int end;
    unsigned char channel;
};