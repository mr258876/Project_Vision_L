#include <Arduino.h>
#include <WiFi.h>
#include "ui.h"
#include "ui_multiLanguage.h"
#include "The_Vision_L_globals.h"
#include "rtos_externs.h"

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

void cb_timer_SettingDispTimer(lv_timer_t *timer)
{
    // 网络状态
    lv_label_set_text(ui_SettingPanel1Label4, info_macAddress);
    switch (WiFi.status())
    {
    case WL_IDLE_STATUS:
        lv_label_set_text(ui_SettingPanel1Label2, lang[curr_lang][61]);
        lv_label_set_text(ui_SettingPanel1Label6, "N/A");
        break;
    case WL_CONNECTED:
        lv_label_set_text_fmt(ui_SettingPanel1Label2, lang[curr_lang][60], WiFi.SSID());
        lv_label_set_text(ui_SettingPanel1Label6, WiFi.localIP().toString().c_str());
        break;
    case WL_CONNECTION_LOST:
    case WL_CONNECT_FAILED:
    case WL_DISCONNECTED:
        lv_label_set_text_fmt(ui_SettingPanel1Label2, lang[curr_lang][63], WiFi.SSID());
        lv_label_set_text(ui_SettingPanel1Label6, "N/A");
        break;
    case WL_NO_SSID_AVAIL:
        lv_label_set_text_fmt(ui_SettingPanel1Label2, lang[curr_lang][62], WiFi.SSID());
        lv_label_set_text(ui_SettingPanel1Label6, "N/A");
        break;
    default:
        lv_label_set_text_fmt(ui_SettingPanel1Label2, lang[curr_lang][59], WiFi.SSID());
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
    lv_dropdown_set_selected(ui_SettingPanel2DP1Dropdown1, curr_lang);

    // 硬件版本
    lv_label_set_text_fmt(ui_SettingInfoPanelAboutLabel4, lang[curr_lang][66], info_hwType); // "HW version:" 
}

void cb_timer_ClockTimerSecond(lv_timer_t *timer)
{
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        lv_img_set_angle(ui_ClockSecond, timeinfo.tm_sec * 60 + (info_isSquareLCD ? 450 : 0));
    }
}

void cb_timer_ClockTimerMinute(lv_timer_t *timer)
{
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        lv_img_set_angle(ui_ClockMinute, timeinfo.tm_min * 60 + timeinfo.tm_sec + (info_isSquareLCD ? 450 : 0));
    }
}

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