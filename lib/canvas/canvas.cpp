#include <canvas.h>

#define DATE_FORMAT "YYYY-MM-DD"
#define TIME_FORMAT "HH-MM-SS"

static datetime_t (*get_current_time)(void);

void canvas_update(void)
{
    display_clear();

    datetime_t datetime = get_current_time();
    char datebuffer[sizeof(DATE_FORMAT)] = {};
    sprintf(datebuffer, "%.4d-%.2d-%.2d", datetime.year, datetime.month, datetime.day);

    char timebuffer[sizeof(TIME_FORMAT)] = {};
    sprintf(timebuffer, "%.2d:%.2d:%.2d", datetime.hour, datetime.minute, datetime.second);

    display_draw_text({4, 4}, 16, datebuffer);
    display_draw_text({4, 30}, 16, timebuffer);
    display_draw_circle({15, 50}, 30);
    display_draw_line({15, 50}, {15, 50});
    display_refresh(false);
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