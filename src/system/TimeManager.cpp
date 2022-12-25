#include "system/TimeManager.h"

void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI("Networking", "Time synced!");
    info_timeSynced = true;
}

void syncTime_NTP_async()
{
    esp_netif_init();
    if (sntp_enabled())
    {
        sntp_stop();
    }

    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    switch (curr_lang)
    {
        /* 根据语言设置ntp服务器 */
    case 1:
        sntp_setservername(0, "cn.ntp.org.cn");
        sntp_setservername(1, "time.pool.aliyun.com");
        break;
    default:
        sntp_setservername(0, "pool.ntp.org");
        sntp_setservername(1, "time.windows.com");
        sntp_setservername(2, "time.apple.com");
        sntp_setservername(3, "time.cloudflare.com");
        break;
    }
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);

    if (setting_timeZone.isEmpty())
    {
        switch (curr_lang)
        {
        case 1:
            setenv("TZ", "UTC-8", 1);
            break;
        default:
            setenv("TZ", "UTC+0", 1);
            break;
        }
    }
    else
    {
        setenv("TZ", setting_timeZone.c_str(), 1);
    }
    
    tzset();

    sntp_init();
}