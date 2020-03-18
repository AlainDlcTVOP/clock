#ifndef CANVAS_H
#define CANVAS_H

#include <common.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void canvas_end(void);
void canvas_update(void);
bool canvas_init(datetime_t (*get_time)(void));

#endif