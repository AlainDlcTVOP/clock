#include <terminal.h>
#include <comdriver.h>

#define DATETIME_FORMAT "YYYY-MM-DD HH:MM:SS"

static datetime_t strtotime(char *buffer)
{
    datetime_t datetime;
    sscanf(buffer, "%d-%d-%d %d:%d:%d", &datetime.year, &datetime.month, &datetime.day,
                                        &datetime.hour, &datetime.minute, &datetime.second);

    return datetime;
}

void terminal_show_menu(void)
{
    comdriver_write("S) Set datetime\n");
    comdriver_write("G) Get datetime\n");
}

char terminal_get_command(void)
{
    char command = 0;

    comdriver_write("Enter the command: ");
    while (command != DATETIME_SET && command != DATETIME_GET && command != NEW_LINE)
    {
        command = toupper(comdriver_read());
        
        char output[2] = {0};
        sprintf(output, "%c", command);
        comdriver_write(output);
    }

    comdriver_write("\n");

    return command;
}

datetime_t terminal_get_date_time(void)
{
    char buffer[sizeof(DATETIME_FORMAT)] = {};

    comdriver_write("\nEnter the current datetime (YYYY-MM-DD HH:MM:SS): ");

    uint8_t chars_read = 0;
    char input = 0;
    while (input != NEW_LINE && chars_read < sizeof(DATETIME_FORMAT))
    {
        input = comdriver_read();
        if (input)
        {
        buffer[chars_read] = input;

        char output[2] = {0};
        sprintf(output, "%c", input);
        comdriver_write(output);
        chars_read++;
        }
    }

    comdriver_write(buffer);

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
    comdriver_write("Current datetime: ");
    comdriver_write(buffer);
    comdriver_write("\n");

}

void terminal_show_error(const char *error)
{
    comdriver_write(error);
}

void terminal_begin(void)
{
    comdriver_begin();
}