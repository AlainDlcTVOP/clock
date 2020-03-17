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

    canvas_end();
}

/*int main()
{
    UNITY_BEGIN();

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