#include <canvas.h>
#include <comdriver.h>
#include <terminal.h>
#include <timeservice.h>

#define DELAY 2000
#define DISPLAY_ERROR "Failed to initialize the display!\n"

void setup()
{
    io_interface_t io_interface =
        {
            .io_begin = comdriver_begin,
            .io_read = comdriver_read,
            .io_write = comdriver_write,
            .io_clear = comdriver_clear,
        };

    terminal_begin(&io_interface);
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
        datetime_t datetime = terminal_get_date_time();
        timeservice_set_date_time(datetime);
    }
    else if (DATETIME_GET == command)
    {
        datetime_t datetime = timeservice_get_date_time();
        terminal_show_date_time(datetime);
    }
}