#include <terminal.h>

#define DATETIME_FORMAT "YYYY-MM-DD HH:MM:SS"

static char (*io_read)(void);
static void (*io_clear)(void);
static void (*io_begin)(void);
static void (*io_write)(const char *text);

static datetime_t strtotime(char *buffer)
{
    datetime_t datetime;
    sscanf(buffer, "%d-%d-%d %d:%d:%d", &datetime.year, &datetime.month, &datetime.day,
                                        &datetime.hour, &datetime.minute, &datetime.second);

    return datetime;
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

inline bool isnum(char input)
{
    if (input >= '0' && input <= '9')
    {
        return true;
    }
    return false;
}

inline bool ischar(char input, uint8_t chars_read)
{
    if (input == '-' && (chars_read == 4 || chars_read == 7) )
    {
        return true;
    }
    else if (input == ' ' && (chars_read == 10) )
    {
        return true;
    }
    else if (input == ':' && (chars_read == 13 || chars_read == 16) )
    {
        return true;
    }
    return false;
}

bool valid_input(char input, uint8_t chars_read)
{
    if (chars_read < 4)
    {
        return isnum(input);
    }
    else if (chars_read == 4) // Minus
    {
        return ischar(input, chars_read);
    }
    else if (chars_read > 4 && chars_read < 7)
    {
        return isnum(input);
    }
    else if (chars_read == 7) // Minus
    {
        return ischar(input, chars_read);
    }
    else if (chars_read > 7 && chars_read < 10)
    {
        return isnum(input);
    }
    else if (chars_read == 10) // Space
    {
        return ischar(input, chars_read);
    }
    else if (chars_read > 10 && chars_read < 13)
    {
        return isnum(input);
    }
    else if (chars_read == 13) // colon
    {
        return ischar(input, chars_read);
    }
    else if (chars_read > 13 && chars_read < 16)
    {
        return isnum(input);
    }
    else if (chars_read == 16) // colon
    {
        return ischar(input, chars_read);
    }
    else if (chars_read > 16 && chars_read < 19)
    {
        return isnum(input);
    }
    return false;
}

datetime_t terminal_get_date_time(void)
{
    char buffer[sizeof(DATETIME_FORMAT)] = {};

    // TEST
    io_write("\nEnter the current datetime (YYYY-MM-DD HH:MM:SS): ");

    uint8_t chars_read = 0;
    char input = 0;
    while (input != NEW_LINE && chars_read < sizeof(DATETIME_FORMAT))
    {
        input = io_read();
        if (valid_input(input, chars_read))
        {
            buffer[chars_read] = input;

            char output[2] = {0};
            sprintf(output, "%c", input);
            io_write(output);
            chars_read++;
        }
    }
    io_write("\n");
    io_write(buffer);
    io_write("\n");

    /*for (uint8_t chars_read = 0; chars_read < sizeof(DATETIME_FORMAT); chars_read++)
    {
        char read_char = comdriver_read();
        if (!read_char)
            return {0};

        buffer[chars_read] = read_char;
    }*/

    return strtotime(buffer);
}

void terminal_show_date_time(datetime_t datetime)
{
    char buffer[sizeof(DATETIME_FORMAT)] = {};
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", datetime.year, datetime.month, datetime.day,
                                                     datetime.hour, datetime.minute, datetime.second);
    io_write("Current datetime: ");
    io_write(buffer);
    io_write("\n");
}

void terminal_show_error(const char *error)
{
    io_write(error);
}

void terminal_begin(io_interface_t io_interface)
{
    io_begin = io_interface.io_begin;
    io_write = io_interface.io_write;
    io_clear = io_interface.io_clear;
    io_read = io_interface.io_read;
    io_begin();
}