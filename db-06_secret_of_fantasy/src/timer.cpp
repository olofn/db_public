#include <allegro.h>

#include "timer.hpp"

static volatile long currentTick = 0;

static void timerCallback()
{
	++currentTick;
}
END_OF_FUNCTION(timerCallback)

long getTick()
{
	return currentTick;
}

void resetTimer()
{
	currentTick = 0;
}

void initTimer()
{
	install_timer();
	LOCK_VARIABLE(currentTick);
	LOCK_FUNCTION(timerCallback);
	install_int_ex(timerCallback, BPS_TO_TIMER(TICKS_PER_SECOND));
}
