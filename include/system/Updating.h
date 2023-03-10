#ifndef _UPDATING_H_
#define _UPDATING_H_

#include "rtos_externs.h"

#include <LinkedList.h>

#include <esp_flash.h>
#include <esp_flash_encrypt.h>
#include <esp_ota_ops.h>

#include <ArduinoJson.h>

#define OTA_BUFFER_SIZE 1024

enum Vision_update_res_t
{
    UPDATE_VALIDATE_FAIL = -4,
    UPDATE_UPDATE_ABORTED = -3,
    UPDATE_FILE_ERR = -2,
    UPDATE_CONFIG_ERR = -1,
    UPDATE_NO_UPDATE = 0,
    UPDATE_SUCCESS = 1,
};

struct Vision_update_info_t
{
    String filePath;                               // Update file size
    size_t offset = 0;                             // Partition start position
    size_t partitionSize = 0;                      // Partition size
    size_t totalBytes = 0;                         // Bytes to write
    size_t writtenBytes = 0;                       // Bytes written
    int code = 0;                                  // Error code performing flash operations
    Vision_update_res_t result = UPDATE_NO_UPDATE; // Update status
};

int checkUpdateConfig(LinkedList<Vision_update_info_t> *listptr);
void tsk_performUpdate(void *parameter);

/*
    @brief check whether there's any update
    @return bool whether there's any update
*/
bool checkUpdate();

#endif