#include <terminal.h>

#define DATETIME_FORMAT "YYYY-MM-DD HH:MM:SS"
#define DATETIME_SIZE sizeof(DATETIME_FORMAT)
#define ENDL_SIZE sizeof('\n')

#define UNIX_DATETIME \
    (datetime_t) { .second = 0, .minute = 0, .hour = 0, .day = 1, .month = 1, .year = 1970 }

static char (*io_read)(void);
static void (*io_clear)(void);
static void (*io_begin)(void);
static void (*io_write)(const char *text);

static datetime_t strtotime(char *buffer)
{
    datetime_t datetime;
    sscanf(buffer, "%d-%d-%d %d:%d:%d", &datetime.year, &datetime.month, &datetime.day,
           &datetime.hour, &datetime.minute, &datetime.second);

    if (datetime.year < 1970)
    {
        return UNIX_DATETIME;
    }
    else
    {
        return datetime;
    }
}

void terminal_show_menu(void)
{
    io_write("S) Set datetime\n");
    io_write("G) Get datetime\n");
}

char terminal_get_command(void)
{
    char command = 0;

    io_write("Enter the command: ");
    while (command != DATETIME_SET && command != DATETIME_GET && command != NEW_LINE)
    {
        command = toupper(io_read());

        char output[2] = {0};
        sprintf(output, "%c", command);
        io_write(output);
    }

    io_write("\n");

    return command;
}

static bool isvalid(char input, uint8_t chars_read)
{
    const char *correct_char;
    correct_char = &DATETIME_FORMAT[chars_read];

    if (isdigit(input) && isalpha(*correct_char))
        return true;
    else if (isblank(input) && isblank(*correct_char))
        return true;
    else if (input == ':' && *correct_char == ':')
        return true;
    else if (input == '-' && *correct_char == '-')
        return true;
    else
        return false;
}

datetime_t terminal_get_date_time(void)
{
    char buffer[DATETIME_SIZE] = {};

    // TEST
    io_write("\nEnter the current datetime (YYYY-MM-DD HH:MM:SS): ");

    uint8_t chars_read = 0;
    char input = 0;
    while (input != NEW_LINE && chars_read < DATETIME_SIZE)
    {
        input = io_read();
        if (isvalid(input, chars_read))
        {
            buffer[chars_read] = input;

            char output[2] = {0};
            sprintf(output, "%c", input);
            io_write(output);
            chars_read++;
        }
    }
    if (chars_read < DATETIME_SIZE - ENDL_SIZE)
    {
        return UNIX_DATETIME;
    }
    io_write("\n");
    io_write(buffer);
    io_write("\n");

    return strtotime(buffer);
}

void terminal_show_date_time(datetime_t datetime)
{
    char buffer[DATETIME_SIZE] = {};
    sprintf(buffer, "%.4d-%.2d-%.2d %.2d:%.2d:%.2d", datetime.year, datetime.month, datetime.day,
            datetime.hour, datetime.minute, datetime.second);
    io_write("Current datetime: ");
    io_write(buffer);
    io_write("\n");
}

void terminal_show_error(const char *error)
{
    io_write(error);
}

void terminal_begin(io_interface_t *io_interface)
{
    io_begin = io_interface->io_begin;
    io_write = io_interface->io_write;
    io_clear = io_interface->io_clear;
    io_read = io_interface->io_read;
    io_begin();
}