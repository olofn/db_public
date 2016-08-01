#include "cli/CoreGeneratorClip.hpp"

namespace Verkstan
{
    CoreGeneratorClip::CoreGeneratorClip()
    {
        coreGeneratorClip = new Core::GeneratorClip();
        for (int i = 0; i < DB_MAX_CLIPS; i++)
        {   
            if (Core::coreClips[i] == 0)
            {
                Core::coreClips[i] = coreGeneratorClip;
                id = i;
                break;
            }
        }

        SetCoreClip(coreGeneratorClip);
    }

    CoreGeneratorClip::~CoreGeneratorClip()
    {
       Core::coreClips[id] = 0;
       delete coreGeneratorClip;
    }

    unsigned short CoreGeneratorClip::Id::get()
    {
        return id;
    }

    int CoreGeneratorClip::GetPeriod()
    {
        return coreGeneratorClip->period;
    }

    void CoreGeneratorClip::SetPeriod(int newPeriod)
    {
        coreGeneratorClip->period = newPeriod;
    }

    int CoreGeneratorClip::GetGeneratorType()
    {
        return coreGeneratorClip->type;
    }

    void CoreGeneratorClip::SetGeneratorType(int type)
    {
        coreGeneratorClip->type = type;
    }
}