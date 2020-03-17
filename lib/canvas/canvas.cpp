#include <canvas.h>

#define TIME_FORMAT "HH:MM:SS"

#define DISPLAY_RELATIVE DISPLAY_HEIGHT / 100.0

#define TEXT_PLACEMENT_YEAR               \
    {                                     \
        0, (int)(DISPLAY_RELATIVE * 78.0) \
    }
#define TEXT_PLACEMENT_MONTH              \
    {                                     \
        0, (int)(DISPLAY_RELATIVE * 68.0) \
    }
#define TEXT_PLACEMENT_DAY                \
    {                                     \
        0, (int)(DISPLAY_RELATIVE * 60.0) \
    }
#define TEXT_PLACEMENT_DTIME \
    {                        \
        0, 140               \
    }

#define FONT_SMALL 12
#define FONT_NORMAL 16
#define FONT_LARGE 20

#define CANVAS_OUTER_BORDER 8
#define CANVAS_WIDTH (DISPLAY_WIDTH - 2 * CANVAS_OUTER_BORDER)

#define SECTION_BORDER 2
//#define CLOCK_SECTION_WIDTH (CANVAS_WIDTH - 2 * CLOCK_SECTION_BORDER)

#define CLOCK_ORIGO \
    (point_t) { DISPLAY_WIDTH / 2 - 1, 64 }
#define CLOCK_RADIUS (CANVAS_WIDTH - 4) / 2.0
#define DOT_LARGE 3
#define DOT_MEDIUM 2
#define DOT_SMALL 1
#define HOURS 12
#define QUARTERS 4
#define HOUR_INTERVAL 30 // (360/12)
#define MINUTE_INTERVAL (HOUR_INTERVAL / 5.0)
#define HOUR_HAND_LENGTH (CLOCK_RADIUS * 0.5)
#define MINUTE_HAND_LENGTH (CLOCK_RADIUS * 0.75)

static datetime_t (*get_current_time)(void);

const char *months[] =
    {
        "January", "Febuary", "March", "April",
        "May", "June", "july", "August",
        "September", "October", "November", "December"};

static inline point_t coords_of_circle(point_t origo, double degrees, double radius)
{
    return {
        .x = origo.x + (int)round(radius * cos(PI * degrees / 180.0)),
        .y = origo.y + (int)round(radius * sin(PI * degrees / 180.0))};
}

void draw_clock()
{
    point_t clock_dot;
    //double angle = 0;

    for (int dot_large = 0; dot_large < HOURS; dot_large++)
    {
        //angle = dot_large * HOUR_INTERVAL;
        const double hour_angle = dot_large * HOUR_INTERVAL;
        //clock_dot = coords_of_circle(CLOCK_ORIGO, angle, CLOCK_RADIUS);
        clock_dot = coords_of_circle(CLOCK_ORIGO, dot_large * HOUR_INTERVAL, CLOCK_RADIUS);
        display_draw_filled_circle(clock_dot, DOT_MEDIUM);
        //angle += MINUTE_INTERVAL;

        for (int dot_small = 1; dot_small <= QUARTERS; dot_small++)
        {
            const double minute_angle = hour_angle + (dot_small * MINUTE_INTERVAL);
            //clock_dot = coords_of_circle(CLOCK_ORIGO, angle, CLOCK_RADIUS);
            clock_dot = coords_of_circle(CLOCK_ORIGO, minute_angle, CLOCK_RADIUS);
            display_draw_filled_circle(clock_dot, DOT_SMALL);
            //angle += MINUTE_INTERVAL;
        }
    }
}

void draw_clock_hands(datetime_t datetime)
{
    const double hour_degrees = (0.5 * (60 * (datetime.hour % 12) + datetime.minute)) - 90.0;
    const double minute_degrees = (6.0 * datetime.minute) - 90.0;

    if (hour_degrees != minute_degrees)
    {
        const point_t hour_hand = coords_of_circle(CLOCK_ORIGO, hour_degrees, HOUR_HAND_LENGTH);
        display_draw_line(CLOCK_ORIGO, hour_hand);
    }

    const point_t minute_hand = coords_of_circle(CLOCK_ORIGO, minute_degrees, MINUTE_HAND_LENGTH);
    display_draw_line(CLOCK_ORIGO, minute_hand);
}

void canvas_update(void)
{
    display_clear();

    datetime_t datetime = get_current_time();

    char yearbuffer[5] = {};
    sprintf(yearbuffer, "%d", datetime.year);
    char daybuffer[3] = {};
    sprintf(daybuffer, "%.2d", datetime.day);

    char timebuffer[sizeof(TIME_FORMAT)] = {};
    sprintf(timebuffer, "%.2d:%.2d:%.2d", datetime.hour, datetime.minute, datetime.second);

    display_draw_text(TEXT_PLACEMENT_YEAR, FONT_NORMAL, yearbuffer, CENTER_X);
    display_draw_text(TEXT_PLACEMENT_MONTH, FONT_LARGE, months[datetime.month - 1], CENTER_X);
    display_draw_text(TEXT_PLACEMENT_DAY, FONT_LARGE, daybuffer, CENTER_X);

    display_draw_text(TEXT_PLACEMENT_DTIME, FONT_NORMAL, timebuffer, CENTER_X);

    draw_clock();
    draw_clock_hands(datetime);

    display_draw_filled_circle(CLOCK_ORIGO, DOT_LARGE);
    display_refresh(false);
}

bool canvas_init(datetime_t (*get_time)(void))
{
    bool status = display_init();
    if (status)
    {
        get_current_time = get_time;
    }
    return status;
}

void canvas_end(void)
{
}