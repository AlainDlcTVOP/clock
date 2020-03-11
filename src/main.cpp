#include <canvas.h>
#include <terminal.h>
#include <timeservice.h>

#define DELAY 2000
#define DISPLAY_ERROR "Failed to initialize the display!\n"

void setup()
{
    terminal_begin();
    timeservice_delay(DELAY);

    if (!canvas_init(timeservice_get_date_time) || !timeservice_timer_begin(canvas_update))
    {
        while (true)
        {
            terminal_show_error(DISPLAY_ERROR);
            timeservice_delay(DELAY);
        }
    }
}

void loop()
{
    terminal_show_menu();
    char command = terminal_get_command();

    if (DATETIME_SET == command)
    {
        timeservice_set_date_time(terminal_get_date_time());
    }
    else if (DATETIME_GET == command)
    {
        terminal_show_date_time(timeservice_get_date_time());
    }
}