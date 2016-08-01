#include "core/operators/timelineoperator.hpp"

#include "core/core.hpp"

TimelineOperator::TimelineOperator()
:startTick(-1),
shouldRender(false)
{

}

void TimelineOperator::render()
{
    if (startTick < 0)
        return;

    for (int i = 0; i < numberOfInputs; i++)
        getInput(i)->render();
}

void TimelineOperator::cascadeProcess(int tick)
{
    for (int i = 0; i < numberOfInputs; i++)
        coreOperators[inputs[i]]->cascadeProcess(tick);

    process(tick);
}

void TimelineOperator::process(int tick)
{
    if (getByteProperty(0) <= 0)
    {
        startTick = -1;
        return;
    }

    if (startTick == -1)
        startTick = tick;

    int relativeTick = tick % (ticks + 1);

    for (int i = 0; i < numberOfClips; i++)
    {
        Clip* clip = coreClips[timelineClips[i]];

        if (clip->start <= relativeTick && clip->end > relativeTick)
            Operator::broadcastChannelValue(clip->channel, clip->getValue(relativeTick - clip->start));
    }
}

void TimelineOperator::broadcastChannelValue(int channel, float value)
{
   if (startTick < 0)
        return;

    for (int i = 0; i < numberOfClips; i++)
        if (coreClips[timelineClips[i]]->channel == channel)
            return;

    Operator::broadcastChannelValue(channel, value);
}
