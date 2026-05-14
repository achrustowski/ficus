#ifndef TIMER_H_
#define TIMER_H_

#include "structs.h"

void timer_start(Timer* timer, double timer_length);
bool timer_done(Timer timer);
double timer_get(Timer timer);

#endif
