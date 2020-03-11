#ifndef TIMESERVICE_H
#define TIMESERVICE_H

#include <common.h>
#include <Arduino.h>
#include <TimeLib.h>

void timeservice_timer_end(void);
void timeservice_delay(uint32_t ms);
datetime_t timeservice_get_date_time(void);
bool timeservice_timer_begin(void (*func)(void));
void timeservice_set_date_time(datetime_t datetime);

#endif