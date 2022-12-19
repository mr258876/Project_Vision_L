#ifndef _APISERVER_H_
#define _APISERVER_H_

#include <esp_http_server.h>
#include <esp_app_format.h>
#include <esp_ota_ops.h>

#include <ArduinoJson.h>
#include "rtos_externs.h"
#include "The_Vision_L_globals.h"
#include "ui_multiLanguage.h"

#include <sys/types.h>
#include <dirent.h>

#include "lvgl.h"

/*  file send/receive buffer size */
#define FILE_SCRATCH_BUFSIZE 4096
#define FILE_SCRATCH_FALLBACK_BUFSIZE 1024

void startAPIServer();
void endAPIServer();

#endif