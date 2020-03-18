#include <unity.h>
#include <canvas.h>
#include <terminal.h>
//#include <timeservice.h>
#include <stdio.h>
#include <string.h>

#define TERMINAL_DATETIME_TEST "2011-12-03 09:05:03\n"
#define TERMINAL_DATETIME_TEST_RESPONSE "Current datetime: 2011-12-03 09:05:03\n"

#define INPUT_BUFFER_SIZE 128
#define OUTPUT_BUFFER_SIZE 128

#define DELAY 3000

static char comdriver_input_buffer[INPUT_BUFFER_SIZE] = {};
static char comdriver_output_buffer[OUTPUT_BUFFER_SIZE] = {};

void shift_left_by_one(char buffer[], int n)
{
    for (int i = 0; i < n - 1; i++)
        buffer[i] = buffer[i + 1];
}

char comdriver_read_spy(void)
{
    const char read_char = *comdriver_input_buffer;
    if (read_char == 0)
    {
        return 0;
    }
    shift_left_by_one(comdriver_input_buffer, INPUT_BUFFER_SIZE);

    return read_char;
}

void comdriver_clear_spy(void)
{
    memset(comdriver_input_buffer, 0, INPUT_BUFFER_SIZE);
    memset(comdriver_output_buffer, 0, OUTPUT_BUFFER_SIZE);
}

void comdriver_begin_spy(void)
{
    comdriver_clear_spy();
}

void comdriver_write_spy(const char *text)
{
    if (strlen(comdriver_output_buffer) + strlen(text) < OUTPUT_BUFFER_SIZE)
    {
        strcat(comdriver_output_buffer, text);
    }
}

#ifndef INTEGRATION_TEST
datetime_t timeservice_get_date_time(void)
{
    return {.second = 11, .minute = 11, .hour = 11, .day = 11, .month = 11, .year = 2011};
}
#endif

void setUp()
{
}

void tearDown()
{
}

#ifndef INTEGRATION_TEST
void delay(int)
{
    ;
}
#endif

void test_terminal()
{
    io_interface_t io_interface = {
        .io_begin = comdriver_begin_spy,
        .io_read = comdriver_read_spy,
        .io_write = comdriver_write_spy,
        .io_clear = comdriver_clear_spy,
    };
    terminal_begin(io_interface);

    comdriver_input_buffer[0] = DATETIME_SET;
    const char command = terminal_get_command(); // Prints the input datetime prompt and returns the command
    TEST_ASSERT_EQUAL_CHAR(DATETIME_SET, command);

    memset(comdriver_input_buffer, 0, INPUT_BUFFER_SIZE);   // Clear input buffer
    strcpy(comdriver_input_buffer, TERMINAL_DATETIME_TEST); // Enters the datetime

    const datetime_t datetime = terminal_get_date_time(); // Returns datetime

    memset(comdriver_output_buffer, 0, OUTPUT_BUFFER_SIZE);
    terminal_show_date_time(datetime);
    TEST_ASSERT_EQUAL_STRING(TERMINAL_DATETIME_TEST_RESPONSE, comdriver_output_buffer);
}

/*void test_init_canvas()
{
    TEST_ASSERT_TRUE(canvas_init(timeservice_get_date_time));

    canvas_end();
}*/

#ifdef INTEGRATION_TEST
void loop()
{
}

void setup()
{
    delay(DELAY);
#else
int main()
{
#endif
    UNITY_BEGIN();
    RUN_TEST(test_terminal);
#ifdef INTEGRATION_TEST
    UNITY_END();
#else
    return UNITY_END();
#endif
}