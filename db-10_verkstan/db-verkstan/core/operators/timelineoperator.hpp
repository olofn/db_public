#pragma once

#include "core/operator.hpp"

class TimelineOperator: public Operator
{
public:
    TimelineOperator();
    void process(int tick);
    void render();
    int startTick;
    void cascadeProcess(int tick);
    void broadcastChannelValue(int channel, float value);

    bool shouldRender;
};