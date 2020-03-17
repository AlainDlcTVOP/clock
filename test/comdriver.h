#ifndef COMMDRIVER_H
#define COMMDRIVER_H

char comdriver_read(void);
void comdriver_clear(void);
void comdriver_begin(void);
void comdriver_write(const char *text);

#endif