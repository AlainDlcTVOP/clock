#include <canvas.h>

#ifndef INTEGRATION_TEST
static datetime_t (*get_current_time)(void);

bool canvas_init(datetime_t (*get_time)(void))
{
    bool status = true;
    if (status)
    {
        get_current_time = get_time;
    }
    return status;
}

void canvas_end(void)
{
    ;
}
#endif