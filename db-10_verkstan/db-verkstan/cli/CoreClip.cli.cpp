#include "cli/CoreClip.hpp"

namespace Verkstan
{
    CoreClip::CoreClip()
    {
       
    }

    CoreClip::~CoreClip()
    {

    }

    float CoreClip::GetValue(int tick)
    {
        return coreClip->getValue(tick);
    }

    void CoreClip::SetCoreClip(Core::Clip* coreClip)
    {
        this->coreClip = coreClip;
    }

    int CoreClip::GetStart()
    {
        return coreClip->start;
    }

    void CoreClip::SetStart(int start)
    {
        coreClip->start = start;
    }

    int CoreClip::GetEnd()
    {
        return coreClip->end;
    }

    void CoreClip::SetEnd(int end)
    {
        coreClip->end = end;
    }

    unsigned char CoreClip::GetChannel()
    {
        return coreClip->channel;
    }

    void CoreClip::SetChannel(unsigned char channel)
    {
        coreClip->channel = channel;
    }
}