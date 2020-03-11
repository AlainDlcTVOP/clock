#ifndef COMMDRIVER_H
#define COMMDRIVER_H

#include <Arduino.h>

char comdriver_read(void);
void comdriver_clear(void);
void comdriver_begin(void);
void comdriver_write(const char *text);

#endif