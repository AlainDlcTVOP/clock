#include <canvas.h>

#define YEAR_SIZE sizeof("YYYY")
#define MONTH_SIZE sizeof("MM")
#define DAY_SIZE sizeof("DD")

#define TIME_SIZE sizeof("HH:MM:SS")

#define FONT_SMALL 12
#define FONT_NORMAL 16
#define FONT_LARGE 20
#define FONT_ROW_SPACING 24

#define CANVAS_OUTER_BORDER 8
#define CANVAS_WIDTH (DISPLAY_WIDTH - 2 * CANVAS_OUTER_BORDER)

#define SECTION_BORDER 45

#define DATE_SECTION_HEIGHT 90

#define TEXT_PLACEMENT_DTIME \
    (point_t) { -1, DATE_SECTION_HEIGHT + SECTION_BORDER }
#define TEXT_PLACEMENT_DAY \
    (point_t) { -1, TEXT_PLACEMENT_DTIME.y + SECTION_BORDER }
#define TEXT_PLACEMENT_MONTH \
    (point_t) { -1, TEXT_PLACEMENT_DAY.y + FONT_ROW_SPACING }
#define TEXT_PLACEMENT_YEAR \
    (point_t) { -1, TEXT_PLACEMENT_MONTH.y + FONT_ROW_SPACING }

#define CLOCK_ORIGO \
    (point_t) { DISPLAY_WIDTH / 2 - 1, 64 }
#define CLOCK_RADIUS (CANVAS_WIDTH - 4) / 2.0

#define DOT_LARGE 4
#define DOT_MEDIUM 2
#define DOT_SMALL 1

#define HOURS 12
#define MINS_PER_HOUR 60
#define QUARTERS 4
#define HOUR_INTERVAL 30 // (360/12)
#define MINUTE_INTERVAL (HOUR_INTERVAL / 5.0)
#define HOUR_HAND_LENGTH (CLOCK_RADIUS * 0.55)
#define MINUTE_HAND_LENGTH (CLOCK_RADIUS * 0.85)
#define DEG_PER_TURN 360
#define CLOCK_ANGLE_OFFSET -90.0
#define DEG_PER_HOURS (DEG_PER_TURN / (HOURS * (double)MINS_PER_HOUR))
#define DEG_PER_MINS (DEG_PER_TURN / MINS_PER_HOUR)

#define MONTH_OFFSET -1

static datetime_t (*get_current_time)(void);

const char *months[] = {
    "January",
    "Febuary",
    "March",
    "April",
    "May",
    "June",
    "july",
    "August",
    "September",
    "October",
    "November",
    "December",
};

static inline point_t coords_of_circle(point_t origo, double degrees, double radius)
{
    return {
        .x = origo.x + (int)round(radius * cos(radians(degrees))),
        .y = origo.y + (int)round(radius * sin(radians(degrees)))};
}

void draw_clock()
{
    point_t clock_dot;

    for (int dot_large = 0; dot_large < HOURS; dot_large++)
    {
        const double hour_angle = dot_large * HOUR_INTERVAL;
        clock_dot = coords_of_circle(CLOCK_ORIGO, dot_large * HOUR_INTERVAL, CLOCK_RADIUS);
        display_draw_filled_circle(clock_dot, DOT_MEDIUM);

        for (int dot_small = 1; dot_small <= QUARTERS; dot_small++)
        {
            const double minute_angle = hour_angle + (dot_small * MINUTE_INTERVAL);
            clock_dot = coords_of_circle(CLOCK_ORIGO, minute_angle, CLOCK_RADIUS);
            display_draw_filled_circle(clock_dot, DOT_SMALL);
        }
    }
}

void draw_clock_hands(datetime_t datetime)
{
    const double hour_degrees = (DEG_PER_HOURS * (MINS_PER_HOUR * (datetime.hour % HOURS) + datetime.minute)) + CLOCK_ANGLE_OFFSET;
    const double minute_degrees = (DEG_PER_MINS * datetime.minute) + CLOCK_ANGLE_OFFSET;

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

    char yearbuffer[YEAR_SIZE] = {};
    sprintf(yearbuffer, "%d", datetime.year);
    char daybuffer[DAY_SIZE] = {};
    sprintf(daybuffer, "%.2d", datetime.day);

    char timebuffer[TIME_SIZE] = {};
    sprintf(timebuffer, "%.2d:%.2d:%.2d", datetime.hour, datetime.minute, datetime.second);

    display_draw_text(TEXT_PLACEMENT_YEAR, FONT_NORMAL, yearbuffer);
    display_draw_text(TEXT_PLACEMENT_MONTH, FONT_LARGE, months[datetime.month + MONTH_OFFSET]);
    display_draw_text(TEXT_PLACEMENT_DAY, FONT_LARGE, daybuffer);

    display_draw_text(TEXT_PLACEMENT_DTIME, FONT_NORMAL, timebuffer);

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