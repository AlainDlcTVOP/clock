#ifndef TERMINAL_H
#define TERMINAL_H

#include <common.h>

#define NEW_LINE '\n'
#define DATETIME_SET 'S'
#define DATETIME_GET 'G'

void terminal_begin(void);
void terminal_show_menu(void);
char terminal_get_command(void);
datetime_t terminal_get_date_time(void);
void terminal_show_error(const char *error);
void terminal_show_date_time(datetime_t datetime);

#endif