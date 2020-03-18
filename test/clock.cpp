#include <unity.h>
#include <canvas.h>
#include <terminal.h>

#define TEST_DATETIME_STRING "2011-12-03 09:05:03"
#define TERMINAL_GOOD_DATETIME_TEST TEST_DATETIME_STRING "\n"
#define TERMINAL_BAD_LENGTH_LONG_DATETIME_TEST TEST_DATETIME_STRING "1\n"

#define TERMINAL_BAD_DATE_DATETIME_TEST "1969-01-01 00:00:00\n"
#define TERMINAL_BAD_FORMAT_DATETIME_TEST "aaaa29zQ _-00:00:00\n"
#define TERMINAL_BAD_LENGTH_SHORT_DATETIME_TEST "2011-12-03 09:05:0\n"
#define TERMINAL_BAD_DATETIME_TEST_EXPECTED "1970-01-01 00:00:00\n"

#define TERMINAL_DATETIME_RESPONSE "Current datetime: "

#define INPUT_BUFFER_SIZE 128
#define OUTPUT_BUFFER_SIZE 128

#define DELAY 3000

static io_interface_t io_interface;

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

datetime_t timeservice_get_date_time(void)
{
    return {.second = 11, .minute = 11, .hour = 11, .day = 11, .month = 11, .year = 2011};
}

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

void test_terminal_process(const char *datetime_string)
{
    // Test the set command
    memset(comdriver_input_buffer, 0, INPUT_BUFFER_SIZE); // Clear input buffer
    comdriver_input_buffer[0] = DATETIME_SET;             // Set DATETIME_SET in buffer
    const char command_set = terminal_get_command();      // Prints the input prompt and returns the command
    TEST_ASSERT_EQUAL_CHAR(DATETIME_SET, command_set);

    // Test the get command
    memset(comdriver_input_buffer, 0, INPUT_BUFFER_SIZE); // Clear input buffer
    comdriver_input_buffer[0] = DATETIME_GET;             // Set DATETIME_GET in buffer
    const char command_get = terminal_get_command();      // Prints the input prompt and returns the command
    TEST_ASSERT_EQUAL_CHAR(DATETIME_GET, command_get);

    // Test the datetime read after previous datetime write
    memset(comdriver_input_buffer, 0, INPUT_BUFFER_SIZE);     // Clear input buffer
    strcpy(comdriver_input_buffer, datetime_string);          // Enters the datetime
    const datetime_t datetime_set = terminal_get_date_time(); // Returns datetime
    memset(comdriver_output_buffer, 0, OUTPUT_BUFFER_SIZE);   // Clear output buffer
    terminal_show_date_time(datetime_set);                    // Print datetime
}

void test_terminal()
{
    io_interface = {
        .io_begin = comdriver_begin_spy,
        .io_read = comdriver_read_spy,
        .io_write = comdriver_write_spy,
        .io_clear = comdriver_clear_spy,
    };
    terminal_begin(&io_interface);

    // Test good datetime
    test_terminal_process(TERMINAL_GOOD_DATETIME_TEST);
    TEST_ASSERT_EQUAL_STRING(TERMINAL_DATETIME_RESPONSE TERMINAL_GOOD_DATETIME_TEST, comdriver_output_buffer);

    // Test long input length
    test_terminal_process(TERMINAL_BAD_LENGTH_LONG_DATETIME_TEST);
    TEST_ASSERT_EQUAL_STRING(TERMINAL_DATETIME_RESPONSE TERMINAL_GOOD_DATETIME_TEST, comdriver_output_buffer);

    // Test too low date
    test_terminal_process(TERMINAL_BAD_DATE_DATETIME_TEST);
    TEST_ASSERT_EQUAL_STRING(TERMINAL_DATETIME_RESPONSE TERMINAL_BAD_DATETIME_TEST_EXPECTED, comdriver_output_buffer);

    // Test bad input against format
    test_terminal_process(TERMINAL_BAD_FORMAT_DATETIME_TEST);
    TEST_ASSERT_EQUAL_STRING(TERMINAL_DATETIME_RESPONSE TERMINAL_BAD_DATETIME_TEST_EXPECTED, comdriver_output_buffer);

    // Test short input length
    test_terminal_process(TERMINAL_BAD_LENGTH_SHORT_DATETIME_TEST);
    TEST_ASSERT_EQUAL_STRING(TERMINAL_DATETIME_RESPONSE TERMINAL_BAD_DATETIME_TEST_EXPECTED, comdriver_output_buffer);
}

void test_init_canvas()
{
    TEST_ASSERT_TRUE(canvas_init(timeservice_get_date_time));

#ifdef INTEGRATION_TEST
    canvas_update();
    canvas_end();
#endif
}

#ifdef INTEGRATION_TEST
void loop()
{
}

void setup()
{
    delay(DELAY);
#else int main()
{
#endif
    UNITY_BEGIN();
    RUN_TEST(test_terminal);
    RUN_TEST(test_init_canvas);
#ifdef INTEGRATION_TEST
    UNITY_END();
#else
    return UNITY_END();
#endif
}