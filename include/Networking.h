#ifndef _NETWORKING_H_
#define _NETWORKING_H_

#include <Arduino.h>

#include <WiFi.h>
#include <The_Vision_L_globals.h>
#include <rtos_externs.h>

#include "TimeManager.h"

void wifiEvent_handler(WiFiEvent_t e);

bool connectWiFi();
bool disConnectWiFi();

void wifiConfigure(void *parameter);
void stopWifiConfigure(void *parameter);

#endif