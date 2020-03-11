#include <canvas.h>

static datetime_t (*get_current_time)(void);

void canvas_update(void)
{
    display_clear();

    display_refresh(true);
}

bool canvas_init(datetime_t (*get_time)(void))
{
    bool status = display_init();
    if (status)
    {
        get_current_time = get_time;
    }
    return status;
}

void canvas_end(void)
{
}