#include "core/metronome.hpp"
#include "core/externals.hpp"
#include "core/core.hpp"

int lastSystemTickCount = 0;
float leftOvers = 0.0f;
int BPM = 120;
int tick = 0;
      
int getTick()
{
    int currentSystemTickCount = GetTickCount();
    int ms = currentSystemTickCount - lastSystemTickCount;
    int tpm = BPM * DB_TICKS_PER_BEAT;
    float tps = tpm / 60.0f;
    float tpms = tps / 1000.0f;

    int tickAddition = (int)(tpms * ms) + (int)leftOvers;
    tick += tickAddition;
    leftOvers -= (int)leftOvers;
    leftOvers +=  (tpms * ms) - (int)(tpms * ms);

    lastSystemTickCount = currentSystemTickCount;

        return tick;     
}

void startMetronome()
{
    lastSystemTickCount = GetTickCount();
}
