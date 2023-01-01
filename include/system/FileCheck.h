#ifndef _BOOTUP_H_
#define _BOOTUP_H_

#include <Arduino.h>
#include "rtos_externs.h"
#include "The_Vision_L_globals.h"

#include <esp_http_client.h>
#include "TLScert.h"

#include "lvgl.h"
#include "ui/ui.h"
#include "ui/ui_multiLanguage.h"

#define FILE_DOWNLOAD_RECV_BUFFER_SIZE 1024

enum Vision_FileCheck_result_t : uint8_t
{
    VISION_FILE_NOT_CHECK = 255,            // 未测试
    VISION_FILE_OK = 0,                     // 文件正常
    VISION_FILE_SYS_FILE_ERR = 0b1,         // 一般系统文件缺失
    VISION_FILE_SYS_FILE_CRITICAL = 0b10,   // 关键系统文件缺失
    VISION_FILE_PLAYLIST_ERR = 0b100,       // 播放列表部分文件缺失(无可播放文件)
    VISION_FILE_PLAYLIST_CRITICAL = 0b1000, // 播放列表关键文件缺失(播放列表配置文件无法解析)
    VISION_FILE_CONF_CRITICAL = 0b10000     // 配置文件异常
};

typedef Vision_FileCheck_result_t (*Vision_FileCheck_cb_t)(bool filePassedCheck);

struct Vision_FileCheck_t
{
    const char *localPath;         // local path with driver name
    const char *downloadPath;      // without prefix
    Vision_FileCheck_cb_t file_cb; // file callback
};

extern Vision_FileCheck_result_t fileCheckResults[];

uint checkSDFiles();
uint fixMissingFiles();

enum Vision_FileCheck_download_res_t : uint8_t
{
    DOWNLOAD_RES_OK = 0,
    DOWNLOAD_RES_FILE_OPEN_FAIL,
    DOWNLOAD_RES_OUT_OF_MEM,
    DOWNLOAD_RES_HTTP_OPEN_FAIL,
    DOWNLOAD_RES_HTTP_READ_FAIL,
    DOWNLOAD_RES_FILE_WRITE_FAIL,
    DOWNLOAD_RES_NOT_CHUNKED_ENCODING,
};

/*
    @brief function to download a file
    @param url: file url
    @param path_to_save: path to save file, starts with mount point("/s/...." or "/f/....")
    @param TLScert: certicifate for HTTPS
    @return reference to Vision_FileCheck_download_res_t
*/
uint downloadFile(const char *url, const char *path_to_save, const char *TLScert = nullptr);

uint downloadGithubFile(const char *url, const char *path_to_save);

const char *getFileDownloadPrefix();

#endif