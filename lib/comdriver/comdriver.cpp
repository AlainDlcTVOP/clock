#include <comdriver.h>

#define BAUD_RATE 9600

char comdriver_read(void)
{
    return Serial.available() ? Serial.read() : 0;
}

void comdriver_begin(void)
{
    Serial.begin(BAUD_RATE);
}

void comdriver_write(const char *text)
{
    Serial.print(text);
}

void comdriver_clear(void)
{
    Serial.clear();
}