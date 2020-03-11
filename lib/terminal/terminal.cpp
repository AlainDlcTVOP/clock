#include <terminal.h>
#include <comdriver.h>

#define DATETIME_FORMAT "YYYY-MM-DD HH:MM:SS"

static datetime_t strtotime(char *buffer)
{
    datetime_t datetime = {.second = 0, .minute = 0, .hour = 0, .day = 0, .month = 0, .year = 0};

    return datetime;
}

void terminal_show_menu(void)
{
}

char terminal_get_command(void)
{
    char command = 0;

    return command;
}

datetime_t terminal_get_date_time(void)
{
    char buffer[sizeof(DATETIME_FORMAT)] = {};

    return strtotime(buffer);
}

void terminal_show_date_time(datetime_t datetime)
{
}

void terminal_show_error(const char *error)
{
    comdriver_write(error);
}

void terminal_begin(void)
{
    comdriver_begin();
}