#ifndef _APISERVER_H_
#define _APISERVER_H_

#include <esp_http_server.h>
#include <esp_app_format.h>
#include <esp_ota_ops.h>

#include <ArduinoJson.h>
#include "rtos_externs.h"
#include "The_Vision_L_globals.h"

void startAPIServer();
void endAPIServer();

#endif