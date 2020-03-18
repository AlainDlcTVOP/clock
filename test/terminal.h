#ifndef TERMINAL_H
#define TERMINAL_H

#include <common.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define NEW_LINE '\n'
#define DATETIME_SET 'S'
#define DATETIME_GET 'G'

typedef struct
{
    void (*io_begin)(void);
    char (*io_read)(void);
    void (*io_write)(const char *text);
    void (*io_clear)(void);
} io_interface_t;

void terminal_begin(io_interface_t io_interface);
void terminal_show_menu(void);
char terminal_get_command(void);
datetime_t terminal_get_date_time(void);
void terminal_show_error(const char *error);
void terminal_show_date_time(datetime_t datetime);

#endif