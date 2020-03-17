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
    // check if vertical
    if (start.x == end.x && start.y != end.y)
    {
        int height = abs(start.y - end.y);

        // check if drawing from lower-to-higher
        if (start.y > end.y)
        {
            paint.DrawVerticalLine(end.x, end.y, height, BLACK);
        }
        // drawing from higher-to-lower
        else
        {
            paint.DrawVerticalLine(start.x, start.y, height, BLACK);
        }
    }
    // check if horizontal
    else if (start.y == end.y && start.x != end.x)
    {
        int width = abs(start.x - end.x);

        // check if drawing from right-to-left
        if (start.x > end.x)
        {
            paint.DrawHorizontalLine(end.x, end.y, width, BLACK);
        }
        // drawing from left-to-right
        else
        {
            paint.DrawHorizontalLine(start.x, start.y, width, BLACK);
        }
    }
    else
    {
        paint.DrawLine(start.x, start.y, end.x, end.y, BLACK);
    }
}

void display_draw_text(point_t start, uint8_t font_size, const char *text, uint8_t option_flag)
{
    sFONT *sfont_ptr;
    switch (font_size)
    {
    case 8:
        sfont_ptr = &Font8;
        break;

    case 12:
        sfont_ptr = &Font12;
        break;

    case 16:
        sfont_ptr = &Font16;
        break;

    case 20:
        sfont_ptr = &Font20;
        break;

    case 24:
        sfont_ptr = &Font24;
        break;

    default:
        sfont_ptr = &Font16;
        break;
    }
    if (option_flag == CENTER_X)
    {
        const int padding = (DISPLAY_WIDTH - (sfont_ptr->Width * (strlen(text)))) / 2 - 1;
        paint.DrawStringAt(padding, start.y, text, sfont_ptr, BLACK);
    }
    else if (option_flag == CENTER_SELF_X)
    {
        const int padding = (sfont_ptr->Width * (strlen(text))) / 2;
        paint.DrawStringAt(start.x - padding, start.y, text, sfont_ptr, BLACK);
    }
    else if (option_flag == CENTER_SELF_Y)
    {
        const int padding = sfont_ptr->Height / 2;
        paint.DrawStringAt(start.x, start.y - padding, text, sfont_ptr, BLACK);
    }
    else if (option_flag == CENTER_SELF_XY)
    {
        const int padding_x = (sfont_ptr->Width * (strlen(text))) / 2;
        const int padding_y = sfont_ptr->Height / 2;
        paint.DrawStringAt(start.x - padding_x, start.y - padding_y, text, sfont_ptr, BLACK);
    }
    else
    {
        paint.DrawStringAt(start.x, start.y, text, sfont_ptr, BLACK);
    }
}

void display_draw_filled_circle(point_t center, int radius)
{
    paint.DrawFilledCircle(center.x, center.y, radius, BLACK);
}

bool display_init()
{
    bool status = (!epd.Init(lut_full_update) && !epd.Init(lut_partial_update));

    if (status)
    {
        display_clear();
        paint.SetRotate(ROTATE_0);

        epd.ClearFrameMemory(BLACK); // bit set = white, bit reset = black
        epd.DisplayFrame();
        epd.ClearFrameMemory(BLACK); // bit set = white, bit reset = black
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