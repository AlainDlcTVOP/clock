#include <unity.h>
#include <canvas.h>
#include <terminal.h>
#include <timeservice.h>

static char comdriver_input_buffer[32] = {};
static char comdriver_output_buffer[32] = {};
static uint8_t read_index = 0;

char comdriver_read_spy(void)
{
    char read_char = comdriver_input_buffer[read_index];
    if (read_char == 0)
    {
        read_index = 0;
        return 0;
    }
    read_index++;

    return read_char;
}

void comdriver_clear_spy(void)
{
    read_index = 0;
    memset(comdriver_input_buffer, 0, 32);
    memset(comdriver_output_buffer, 0, 32);
}

void comdriver_begin_spy(void)
{
    comdriver_clear_spy();
}

void comdriver_write_spy(const char *text)
{
    strcpy(comdriver_output_buffer, text);
}

io_interface_t io_interface = {
    .io_begin = comdriver_begin_spy,
    .io_read = comdriver_read_spy,
    .io_write = comdriver_write_spy,
    .io_clear = comdriver_clear_spy,
};

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

void test_init_canvas()
{
    TEST_ASSERT_TRUE(canvas_init(timeservice_get_date_time));

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

    /*int main()
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

    RUN_TEST(test_init_canvas);

    return UNITY_END();
}*/

#ifdef INTEGRATION_TEST
    void loop()
    {
    }

    void setup()
    {
        delay(3000);
#else
    int main()
    {
#endif
        UNITY_BEGIN();
        RUN_TEST(test_init_canvas);
#ifdef INTEGRATION_TEST
        UNITY_END();
#else
        return UNITY_END();
#endif
    }