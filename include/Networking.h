#ifndef _NETWORKING_H_
#define _NETWORKING_H_

#include <WiFi.h>
#include <The_Vision_L_globals.h>
#include <rtos_externs.h>

void wifiEvent_handler(WiFiEvent_t e);

bool connectWiFi();
bool disConnectWiFi();

void wifiConfigure(void *parameter);
void stopWifiConfigure(void *parameter);

#endif