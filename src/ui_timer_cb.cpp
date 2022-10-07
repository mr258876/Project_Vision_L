#include <Arduino.h>
#include "ui.h"

void cb_timer_ResinTimer(lv_timer_t *timer);

void cb_timer_ClockTimer(lv_timer_t *timer)
{
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        lv_img_set_angle(ui_ClockHour, timeinfo.tm_hour % 12 * 300 + timeinfo.tm_min * 5 + 2250);
        lv_img_set_angle(ui_ClockMinute, timeinfo.tm_min * 60 + timeinfo.tm_sec + 450);

        int opaList[] = {0, 0, 0, 0};

        int dayMinute = timeinfo.tm_hour * 60 + timeinfo.tm_min;
        int timeSeg = floor(dayMinute / 360);
        opaList[timeSeg] = 255 - (255 / 360.0 * (dayMinute % 360));
        if (timeSeg == 3)
        {
            opaList[0] = (255 / 360.0 * (dayMinute % 360));
        }
        else
        {
            opaList[timeSeg + 1] = (255 / 360.0 * (dayMinute % 360));
        }

        lv_obj_set_style_img_opa(ui_ClockIconNight, opaList[0], LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_opa(ui_ClockIconMorning, opaList[1], LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_opa(ui_ClockIconNoon, opaList[2], LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_opa(ui_ClockIconDusk, opaList[3], LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}