#include "The_Vision_L_globals.h"
#include "rtos_externs.h"

#include <esp_ota_ops.h>

#include <ArduinoJson.h>
#include "system/FileCheck.h"

enum Vision_update_res_t {
    UPDATE_VALIDATE_FAIL = -4,
    UPDATE_OTA_ABORTED = -3,
    UPDATE_OTA_START_FAIL = -2,
    UPDATE_FILE_ERR = -1,
    UPDATE_NO_UPDATE = 0,
    UPDATE_SUCCESS = 1,
};

struct Vision_update_info_t
{
    size_t totalBytes = 0;
    size_t writtenBytes = 0;
    Vision_update_res_t result = UPDATE_NO_UPDATE;
};

bool updateFileAvaliable(const char* filePath);
void tsk_performUpdate(void *parameter);

/* 
    @brief check whether there's any update
    @return bool whether there's any update
*/
bool checkUpdate();