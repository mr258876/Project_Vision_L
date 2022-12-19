#include <Arduino.h>
#include "ui.h"
#include "ui_multiLanguage.h"
#include "The_Vision_L_globals.h"
#include "rtos_externs.h"

/* 树脂显示刷新 */
void cb_timer_ResinDispTimer(lv_timer_t *timer)
{
    if (xSemaphoreTake(NoteDataMutex, portMAX_DELAY) == pdTRUE)
    {
        if (info_updatingResinData)
        {
            lv_label_set_text(ui_NoteUpdateTimeLabel, lang[curr_lang][44]); // LV_SYMBOL_REFRESH "正在更新..."
        }
        else
        {
            if (nd._last_update_time > 0)
                lv_label_set_text_fmt(ui_NoteUpdateTimeLabel, lang[curr_lang][43], (int)((time(NULL) - nd._last_update_time) / 60)); // "%d分钟前更新"
            else
                lv_label_set_text(ui_NoteUpdateTimeLabel, lang[curr_lang][45]); // "数据未初始化"
        }

        lv_label_set_text_fmt(ui_NoteResinLabel, "%d/%d", nd.resinRemain, nd.resinMax);
        lv_label_set_text_fmt(ui_NoteExpeditionsLabel, "%d/%d", nd.expeditionFinished, nd.expeditionOngoing);

        if (nd.homecoinMax < 1000)
        {
            lv_label_set_text_fmt(ui_NoteHomeCoinLabel, "%d/%d", nd.homecoinRemain, nd.homecoinMax);
        }
        else
        {
            if (nd.homecoinRemain < 1000)
                lv_label_set_text_fmt(ui_NoteHomeCoinLabel, "%d/%.1fK", nd.homecoinRemain, (nd.homecoinMax / 1000.0));
            else
                lv_label_set_text_fmt(ui_NoteHomeCoinLabel, "%.1fK/%.1fK", (nd.homecoinRemain / 1000.0), (nd.homecoinMax / 1000.0));
        }

        if (nd.hasTransformer)
        {
            if (nd.transformerRecoverTime > 86400)
            {
                lv_label_set_text_fmt(ui_NoteTransformerLabel, lang[curr_lang][46], (int)(nd.transformerRecoverTime / 86400)); // "%d天"
            }
            else if (nd.transformerRecoverTime > 3600)
            {
                lv_label_set_text_fmt(ui_NoteTransformerLabel, lang[curr_lang][47], (int)(nd.transformerRecoverTime / 3600)); // "%d小时"
            }
            else if (nd.transformerRecoverTime > 60)
            {
                lv_label_set_text_fmt(ui_NoteTransformerLabel, lang[curr_lang][48], (int)(nd.transformerRecoverTime / 60)); // "%d分钟"
            }
            else
            {
                lv_label_set_text(ui_NoteTransformerLabel, lang[curr_lang][49]); // "已就绪"
            }
        }
        else
        {
            lv_label_set_text(ui_NoteTransformerLabel, lang[curr_lang][50]); // "未解锁"
        }

        xSemaphoreGive(NoteDataMutex);
    }
}

/* 设置菜单值刷新 */
void cb_timer_SettingDispTimer(lv_timer_t *timer)
{
    // API服务器相关
    switch (info_APIstatus)
    {
    case 0:
        lv_obj_clear_state(ui_SettingPanel0SW1Switch1, LV_STATE_CHECKED);
        lv_obj_clear_flag(ui_SettingPanel0Label2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_SettingPanel0QR1, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(ui_SettingPanel0Label2, lang[curr_lang][73]); // "实用程序未启用。"
        break;
    case 1:
        lv_obj_add_state(ui_SettingPanel0SW1Switch1, LV_STATE_CHECKED); // 通过API服务器状态设置开关状态
        lv_obj_add_flag(ui_SettingPanel0Label2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_SettingPanel0QR1, LV_OBJ_FLAG_HIDDEN);
        lv_qrcode_update(ui_SettingPanel0QR1, info_APIaddress, strlen(info_APIaddress)); // "http://127.127.127.127"
        break;
    case 2:
        lv_obj_clear_flag(ui_SettingPanel0Label2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_SettingPanel0QR1, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(ui_SettingPanel0Label2, lang[curr_lang][71]); // "实用程序正在启动..."
        break;
    case 3:
        lv_obj_clear_flag(ui_SettingPanel0Label2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_SettingPanel0QR1, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(ui_SettingPanel0Label2, lang[curr_lang][74]); // "实用程序正在停止..."
        break;
    default:
        lv_obj_clear_state(ui_SettingPanel0SW1Switch1, LV_STATE_CHECKED);
        lv_obj_clear_flag(ui_SettingPanel0Label2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_SettingPanel0QR1, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(ui_SettingPanel0Label2, lang[curr_lang][72]); // "错误：\n未连接到无线网络，\n实用程序无法启动。"
        break;
    }

    // 网络状态
    lv_label_set_text(ui_SettingPanel1Label4, info_macAddress);
    switch (info_wifiStatus)
    {
    case 0: // WL_IDLE_STATUS
        lv_label_set_text(ui_SettingPanel1Label2, lang[curr_lang][61]);
        lv_label_set_text(ui_SettingPanel1Label6, "N/A");
        break;
    case 3: // WL_CONNECTED
        lv_label_set_text_fmt(ui_SettingPanel1Label2, lang[curr_lang][60], info_SSID);
        lv_label_set_text(ui_SettingPanel1Label6, info_ipv4Address);
        break;
    case 5: // WL_CONNECTION_LOST
    case 4: // WL_CONNECT_FAILED
    case 6: // WL_DISCONNECTED
        lv_label_set_text_fmt(ui_SettingPanel1Label2, lang[curr_lang][63], info_SSID);
        lv_label_set_text(ui_SettingPanel1Label6, "N/A");
        break;
    case 1: // WL_NO_SSID_AVAIL
        lv_label_set_text_fmt(ui_SettingPanel1Label2, lang[curr_lang][62], info_SSID);
        lv_label_set_text(ui_SettingPanel1Label6, "N/A");
        break;
    default:
        lv_label_set_text_fmt(ui_SettingPanel1Label2, lang[curr_lang][59], info_SSID);
        lv_label_set_text(ui_SettingPanel1Label6, "N/A");
        break;
    }

    // 距离传感器使能
    if (info_hasProx)
    {
        if (setting_autoBright)
        {
            lv_obj_add_state(ui_SettingPanel2SW1Switch1, LV_STATE_CHECKED);
        }
        else
        {
            lv_obj_clear_state(ui_SettingPanel2SW1Switch1, LV_STATE_CHECKED);
        }
    }
    else
    {
        lv_obj_add_state(ui_SettingPanel2SW1Switch1, LV_STATE_DISABLED);
    }
    // 重力传感器使能
    if (info_hasAccel)
    {
        if (setting_useAccel)
        {
            lv_obj_add_state(ui_SettingPanel2SW2Switch1, LV_STATE_CHECKED);
        }
        else
        {
            lv_obj_clear_state(ui_SettingPanel2SW2Switch1, LV_STATE_CHECKED);
        }
    }
    else
    {
        lv_obj_add_state(ui_SettingPanel2SW2Switch1, LV_STATE_DISABLED);
    }

    // 语言选择菜单
    // lv_dropdown_set_selected(ui_SettingPanel2DP1Dropdown1, curr_lang);   // <- 已移动至cb_event_SettingScreen. 在此处更新已选择语言会导致语言菜单一直跳回curr_lang。

    // 硬件版本
    lv_label_set_text_fmt(ui_SettingInfoPanelAboutLabel4, lang[curr_lang][66], info_hwType); // "HW version:"
}

/* 主题时钟秒针刷新 */
void cb_timer_ClockTimerSecond(lv_timer_t *timer)
{
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        lv_img_set_angle(ui_ClockSecond, timeinfo.tm_sec * 60 + (info_isSquareLCD ? 450 : 0));
    }
}

/* 主题时钟分针刷新 */
void cb_timer_ClockTimerMinute(lv_timer_t *timer)
{
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        lv_img_set_angle(ui_ClockMinute, timeinfo.tm_min * 60 + timeinfo.tm_sec + (info_isSquareLCD ? 450 : 0));
    }
}

/* 主题时钟时针/四角图标刷新 */
void cb_timer_ClockTimerHour(lv_timer_t *timer)
{
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        lv_img_set_angle(ui_ClockHour, timeinfo.tm_hour % 12 * 300 + timeinfo.tm_min * 5 + 1800 + (info_isSquareLCD ? 450 : 0));

        int opaList[] = {0, 0, 0, 0};
        lv_obj_t *iconList[] = {ui_ClockIconNight, ui_ClockIconMorning, ui_ClockIconNoon, ui_ClockIconDusk};

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

        for (size_t i = 0; i < 4; i++)
        {
            if (opaList[i] > 0)
            {
                lv_obj_clear_flag(iconList[i], LV_OBJ_FLAG_HIDDEN);
                lv_obj_set_style_img_opa(iconList[i], opaList[i], LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            else
            {
                lv_obj_add_flag(iconList[i], LV_OBJ_FLAG_HIDDEN);
            }
        }
    }
}

/* 数字时钟刷新 */
static int lastWeekday = -1;
static int lastHour = -1;
static int lastMin = -1;
void cb_timer_DigitalClockTimer(lv_timer_t *timer)
{
    if (*((bool *)timer->user_data))
    {
        lastWeekday = -1;
        lastHour = -1;
        lastMin = -1;
        *((bool *)timer->user_data) = false;
    }

    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        /* Time */
        if (lastHour < 0)
        {
            lv_label_set_text_fmt(ui_DigitalClockTimeLabelHour, "%d", timeinfo.tm_hour);
            lv_label_set_text_fmt(ui_DigitalClockTimeLabelHourShadow, "%d", timeinfo.tm_hour);
            lv_label_set_text_fmt(ui_DigitalClockTimeLabelMin, "%02d", timeinfo.tm_min);
            lv_label_set_text_fmt(ui_DigitalClockTimeLabelMinShadow, "%02d", timeinfo.tm_min);
            lastHour = timeinfo.tm_hour;
            lastMin = timeinfo.tm_min;
        }

        if (lastHour != timeinfo.tm_hour)
        {
            lv_label_set_text_fmt(ui_DigitalClockTimeLabelHour, "%d\n%d", lastHour, timeinfo.tm_hour);
            lv_label_set_text_fmt(ui_DigitalClockTimeLabelHourShadow, "%d\n%d", lastHour, timeinfo.tm_hour);
            aniDigitalClockLinear_Animation(ui_DigitalClockTimeLabelHour, 0);
            aniDigitalClockLinear_Animation(ui_DigitalClockTimeLabelHourShadow, 0);
            lastHour = timeinfo.tm_hour;
        }
        if (lastMin != timeinfo.tm_min)
        {
            lv_label_set_text_fmt(ui_DigitalClockTimeLabelMin, "%02d\n%02d", lastMin, timeinfo.tm_min);
            lv_label_set_text_fmt(ui_DigitalClockTimeLabelMinShadow, "%02d\n%02d", lastMin, timeinfo.tm_min);
            aniDigitalClockLinear_Animation(ui_DigitalClockTimeLabelMin, 0);
            aniDigitalClockLinear_Animation(ui_DigitalClockTimeLabelMinShadow, 0);
            lastMin = timeinfo.tm_min;
        }

        if (lv_obj_has_flag(ui_DigitalClockTimeLabelColon, LV_OBJ_FLAG_HIDDEN))
        {
            lv_obj_clear_flag(ui_DigitalClockTimeLabelColon, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_DigitalClockTimeLabelColonShadow, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
            lv_obj_add_flag(ui_DigitalClockTimeLabelColon, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_DigitalClockTimeLabelColonShadow, LV_OBJ_FLAG_HIDDEN);
        }

        /* Weekday */
        if (lastWeekday < 0)
        {
            lv_label_set_text(ui_DigitalClockWeekdayLabel, lang[curr_lang][75 + timeinfo.tm_wday]);
            lv_label_set_text(ui_DigitalClockWeekdayLabelShadow, lang[curr_lang][75 + timeinfo.tm_wday]);
            lastWeekday = timeinfo.tm_wday;
        }

        if (lastWeekday != timeinfo.tm_wday)
        {
            lv_label_set_text_fmt(ui_DigitalClockWeekdayLabel, "%s\n%s", lang[curr_lang][75 + lastWeekday], lang[curr_lang][75 + timeinfo.tm_wday]);
            lv_label_set_text_fmt(ui_DigitalClockWeekdayLabelShadow, "%s\n%s", lang[curr_lang][75 + lastWeekday], lang[curr_lang][75 + timeinfo.tm_wday]);
            aniDigitalClockLinear_Animation(ui_DigitalClockWeekdayLabel, 0);
            aniDigitalClockLinear_Animation(ui_DigitalClockWeekdayLabelShadow, 0);
        }

        /* Date */
        switch (curr_lang)
        {
        case 1: // YYYY年\nMM月DD日
            lv_label_set_text_fmt(ui_DigitalClockDateLabel, lang[curr_lang][82], 1900 + timeinfo.tm_year, 1 + timeinfo.tm_mon, timeinfo.tm_mday);
            lv_label_set_text_fmt(ui_DigitalClockDateLabelShadow, lang[curr_lang][82], 1900 + timeinfo.tm_year, 1 + timeinfo.tm_mon, timeinfo.tm_mday);
            break;
        default: // MMM DD,\nYYYY
            lv_label_set_text_fmt(ui_DigitalClockDateLabel, lang[curr_lang][82], lang[curr_lang][83 + timeinfo.tm_mon], timeinfo.tm_mday, 1900 + timeinfo.tm_year);
            lv_label_set_text_fmt(ui_DigitalClockDateLabelShadow, lang[curr_lang][82], lang[curr_lang][83 + timeinfo.tm_mon], timeinfo.tm_mday, 1900 + timeinfo.tm_year);
            break;
        }
    }
}

/* 数字时钟树脂显示刷新 */
void cb_timer_DigitalClockResinTimer(lv_timer_t *timer)
{
    if (xSemaphoreTake(NoteDataMutex, portMAX_DELAY) == pdTRUE)
    {
        lv_label_set_text_fmt(ui_DigitalClockResinLabelResin, "%d", nd.resinRemain);
        lv_label_set_text_fmt(ui_DigitalClockResinLabelExpe, "%d/%d", nd.expeditionFinished, nd.expeditionOngoing);

        if (nd.homecoinRemain < 1000)
            lv_label_set_text_fmt(ui_DigitalClockResinLabelHomecoin, "%d", nd.homecoinRemain);
        else
            lv_label_set_text_fmt(ui_DigitalClockResinLabelHomecoin, "%.1fK", (nd.homecoinRemain / 1000.0));

        if (nd.hasTransformer)
        {
            if (nd.transformerRecoverTime > 86400)
            {
                lv_label_set_text_fmt(ui_DigitalClockResinLabelTrans, lang[curr_lang][46], (int)(nd.transformerRecoverTime / 86400)); // "%d天"
            }
            else if (nd.transformerRecoverTime > 3600)
            {
                lv_label_set_text_fmt(ui_DigitalClockResinLabelTrans, lang[curr_lang][47], (int)(nd.transformerRecoverTime / 3600)); // "%d小时"
            }
            else if (nd.transformerRecoverTime > 60)
            {
                lv_label_set_text_fmt(ui_DigitalClockResinLabelTrans, lang[curr_lang][48], (int)(nd.transformerRecoverTime / 60)); // "%d分钟"
            }
            else
            {
                lv_label_set_text(ui_DigitalClockResinLabelTrans, lang[curr_lang][49]); // "已就绪"
            }
        }
        else
        {
            lv_label_set_text(ui_DigitalClockResinLabelTrans, lang[curr_lang][50]); // "未解锁"
        }

        xSemaphoreGive(NoteDataMutex);
    }

    if (lv_obj_has_flag(ui_DigitalClockResinLabelResin, LV_OBJ_FLAG_HIDDEN))
    {
        lv_obj_add_flag(ui_DigitalClockResinIconExpe, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_DigitalClockResinLabelExpe, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_DigitalClockResinIconTrans, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_DigitalClockResinLabelTrans, LV_OBJ_FLAG_HIDDEN);

        lv_obj_clear_flag(ui_DigitalClockResinIconResin, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_DigitalClockResinLabelResin, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_DigitalClockResinIconHomecoin, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_DigitalClockResinLabelHomecoin, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_clear_flag(ui_DigitalClockResinIconExpe, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_DigitalClockResinLabelExpe, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_DigitalClockResinIconTrans, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_DigitalClockResinLabelTrans, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_flag(ui_DigitalClockResinIconResin, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_DigitalClockResinLabelResin, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_DigitalClockResinIconHomecoin, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_DigitalClockResinLabelHomecoin, LV_OBJ_FLAG_HIDDEN);
    }
}

/* 天气图标对照表 */
const void *weather_img_table[] = {
    &ui_img_weather_clear_sky,
    &ui_img_weather_partly_cloudy,
    &ui_img_weather_overcast,
    &ui_img_weather_rain_showers,
    &ui_img_weather_thunderstorm,
    &ui_img_weather_hail,
    &ui_img_weather_sleet,
    &ui_img_weather_slight_rain,
    &ui_img_weather_moderate_rain,
    &ui_img_weather_heavy_rain,
    &ui_img_weather_rainstorm,
    &ui_img_weather_snow_showers,
    &ui_img_weather_slight_snow_fall,
    &ui_img_weather_moderate_snow_fall,
    &ui_img_weather_heavy_snow_fall,
    &ui_img_weather_snowstorm,
    &ui_img_weather_fog,
    &ui_img_weather_freezing_drizzle,
    &ui_img_weather_sandstorm,
    &ui_img_weather_sand,
    &ui_img_weather_haze,
};

/* 数字时钟天气显示刷新 */
void cb_timer_DigitalClockWeatherTimer(lv_timer_t *timer)
{
    if (flag_ui_font_HanyiWenhei20)
    {
        if (wp->getCity().isEmpty())
        {
            lv_label_set_text(ui_DigitalClockWeatherCityLabel, "未来");
        }
        else
        {
            lv_label_set_text(ui_DigitalClockWeatherCityLabel, wp->getCity().c_str());
        }
        lv_obj_set_style_text_font(ui_DigitalClockWeatherCityLabel, &ui_font_HanyiWenhei20, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    else
    {
        lv_obj_add_flag(ui_DigitalClockWeatherCityLabel, LV_OBJ_FLAG_HIDDEN);
    }

    lv_img_set_src(ui_DigitalClockWeatherIcon, weather_img_table[(int)weather.weather]);
    lv_label_set_text_fmt(ui_DigitalClockWeatherTempLabel, "%d°", weather.temp);
    lv_label_set_text_fmt(ui_DigitalClockWeatherAirLabel, "%d", weather.aqi);
}