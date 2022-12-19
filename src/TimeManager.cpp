#include "TimeManager.h"

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
    sntp_setservername(0, "pool.ntp.org");
    sntp_setservername(1, "time.windows.com");
    sntp_setservername(2, "time.apple.com");
    sntp_setservername(3, "time.cloudflare.com");
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);

    if (setting_timeZone.isEmpty())
    {
        switch (curr_lang)
        {
        case 1:
            setenv("TZ", "CST-8", 1);
            break;
        default:
            setenv("TZ", "BST-0", 1);
            break;
        }
    }
    tzset();

    sntp_init();
}