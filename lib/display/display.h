#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 296

#define CENTER_X 1
#define CENTER_SELF_X 2
#define CENTER_SELF_Y 3
#define CENTER_SELF_XY 4

typedef struct
{
    int x;
    int y;
} point_t;

bool display_init(void);
void display_clear(void);
void display_refresh(bool full);
void display_draw_line(point_t start, point_t end);
void display_draw_filled_circle(point_t center, int radius);
void display_draw_text(point_t start, uint8_t font_size, const char *text);

#endif