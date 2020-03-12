#include <unity.h>
#include <canvas.h>
#include <terminal.h>
#include <timeservice.h>

#ifndef INTEGRATION_TEST
datetime_t timeservice_get_date_time(void)
{
    return {.second = second(), .minute = minute(), .hour = hour(), .day = day(), .month = month(), .year = year()};
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
    TEST_ASSERT_TRUE( canvas_init(timeservice_get_date_time) );

    canvas_end();
}

/*int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_init_canvas);

    return UNITY_END();
}*/

#ifndef INTEGRATION_TEST
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
#ifndef INTEGRATION_TEST
    UNITY_END();
#else
    return UNITY_END();
#endif
}