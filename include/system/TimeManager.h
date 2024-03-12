#ifndef _TIMEMANAGER_H_
#define _TIMEMANAGER_H_

#include <time.h>
#include <esp_netif.h>
#include <sys/time.h>
#include <esp_sntp.h>

#include "The_Vision_L_globals.h"
#include "ui/ui_multiLanguage.h"


void syncTime_async();

void syncTime_NTP_async();
void syncTime_BT_async();

#endif