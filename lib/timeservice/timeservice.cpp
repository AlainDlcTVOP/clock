#include <timeservice.h>

#define ONE_SECOND 1000000

static IntervalTimer interval_timer;

void timeservice_timer_end(void)
{
    interval_timer.end();
}

bool timeservice_timer_begin(void (*func)(void))
{
    return interval_timer.begin(func, ONE_SECOND);
}

datetime_t timeservice_get_date_time(void)
{
    return {.second = second(), .minute = minute(), .hour = hour(), .day = day(), .month = month(), .year = year()};
}

void timeservice_set_date_time(datetime_t datetime)
{
    setTime(datetime.hour, datetime.minute, datetime.second, datetime.day, datetime.month, datetime.year);
}

void timeservice_delay(uint32_t ms)
{
    delay(ms);
}