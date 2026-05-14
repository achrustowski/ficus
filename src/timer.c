#include "timer.h"
#include "structs.h"

void timer_start(Timer* timer, double timer_length)
{
    timer->start_time = GetTime();
    timer->life_time = timer_length;
    timer->started = true;
}

bool timer_done(Timer timer)
{
    if (timer.started)
    {
        return GetTime() - timer.start_time >= timer.life_time;
    }
    return false;
}

double timer_get(Timer timer)
{
    return GetTime() - timer.start_time;
}
