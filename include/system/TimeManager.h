#ifndef _TIMEMANAGER_H_
#define _TIMEMANAGER_H_

#include <time.h>
#include <esp_netif.h>
#include <sys/time.h>
#include <esp_sntp.h>

#include "The_Vision_L_globals.h"
#include "ui/ui_multiLanguage.h"

#include <NimBLEDevice.h>

const NimBLEUUID CURRENT_TIME_SERVICE_UUID((uint16_t)0x1805);
const NimBLEUUID CURRENT_TIME_CHARACTERISTIC_UUID((uint16_t)0x2A2B);

void syncTime_NTP_async();
void syncTime_BT();

#endif