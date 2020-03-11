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
    bool status = (!epd.Init(lut_full_update) && !epd.Init(lut_full_update));

    if (status)
    {
        display_clear();

        paint.SetRotate(ROTATE_0);

        epd.ClearFrameMemory(BLACK);
        epd.DisplayFrame();
        epd.ClearFrameMemory(BLACK);
        epd.DisplayFrame();
    }
    return status;
}

void display_refresh(bool full)
{

    epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();
    if (full)
    {
        epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
        epd.DisplayFrame();
    }
}

void display_clear(void)
{
    paint.Clear(WHITE);
}