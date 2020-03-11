#include <display.h>
#include <epd2in9.h>
#include <epdpaint.h>

#define BYTE 8
#define BLACK 0
#define WHITE 1

static uint8_t buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / BYTE];
static Paint paint(buffer, DISPLAY_WIDTH, DISPLAY_HEIGHT);
static Epd epd;

void display_draw_line(point_t start, point_t end)
{
}

void display_draw_text(point_t start, uint8_t font_size, const char *text)
{
}

void display_draw_filled_circle(point_t center, int radius)
{
}

bool display_init()
{
    bool status = false;

    return status;
}

void display_refresh(bool full)
{
}

void display_clear(void)
{
}