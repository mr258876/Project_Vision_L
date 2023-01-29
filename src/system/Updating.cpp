#include "system/Updating.h"

bool updateFileAvaliable()
{
    int file_res;
    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
        file_res = access("/s/Update.bin", F_OK);
    }
    xSemaphoreGive(SDMutex);
    if (file_res == -1)
    {
        return false;
    }

    FILE *f;
    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
        f = fopen("/s/Update.bin", "rb");
    }
    xSemaphoreGive(SDMutex);
    if (!f)
    {
        ESP_LOGE("updateFileAvaliable", "Unable to open Update.bin!");
        return false;
    }
    char buf[sizeof(esp_image_header_t) + sizeof(esp_image_segment_header_t) + sizeof(esp_app_desc_t)];

    int bytes_read;
    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
        bytes_read = fread(buf, 1, sizeof(esp_image_header_t) + sizeof(esp_image_segment_header_t) + sizeof(esp_app_desc_t), f);
    }
    xSemaphoreGive(SDMutex);
    if (bytes_read < sizeof(esp_image_header_t) + sizeof(esp_image_segment_header_t) + sizeof(esp_app_desc_t))
    {
        ESP_LOGE("updateFileAvaliable", "Error reading Update.bin!");
        return false;
    }

    unsigned int identity_version;
    unsigned int major_version;
    unsigned int minor_version;
    esp_app_desc_t new_app_info;
    memcpy(&new_app_info, &buf[sizeof(esp_image_header_t) + sizeof(esp_image_segment_header_t)], sizeof(esp_app_desc_t));

    int ver_check_res = sscanf(new_app_info.version, "L%u.%u.%u", &identity_version, &major_version, &minor_version);
    return ver_check_res > 2;
}

void tsk_performUpdate(void *parameter)
{
    Vision_update_info_t *stats = (Vision_update_info_t *)parameter;

    FILE *f;
    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
        f = fopen("/s/Update.bin", "rb");
    }
    xSemaphoreGive(SDMutex);
    if (!f)
    {
        stats->result = UPDATE_FILE_ERR;
        vTaskDelete(NULL);
    }

    // 获取文件大小
    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
        fseek(f, 0, SEEK_END);        // 定位文件指针到文件尾
        stats->totalBytes = ftell(f); // 获取文件指针偏移量，即文件大小
        fseek(f, 0, SEEK_SET);        // 定位回文件头
    }
    xSemaphoreGive(SDMutex);

    /* 启动OTA */
    esp_ota_handle_t ota_handle;
    const esp_partition_t *update_partition = esp_ota_get_next_update_partition(NULL);
    if (esp_ota_begin(update_partition, stats->totalBytes, &ota_handle)) // <- ESP_OK=0
    {
        stats->result = UPDATE_OTA_START_FAIL;
        vTaskDelete(NULL);
    }

    char buf[OTA_BUFFER_SIZE];
    int read_bytes;
    while (1)
    {
        xSemaphoreTake(SDMutex, portMAX_DELAY);
        {
            read_bytes = fread(buf, 1, OTA_BUFFER_SIZE, f);
        }
        xSemaphoreGive(SDMutex);
        if (read_bytes == 0)
        {
            if (stats->writtenBytes == stats->totalBytes)
                break;
            else
            {
                esp_ota_abort(ota_handle);
                xSemaphoreTake(SDMutex, portMAX_DELAY);
                {
                    fclose(f);
                }
                xSemaphoreGive(SDMutex);
                stats->result = UPDATE_OTA_ABORTED;
                vTaskDelete(NULL);
            }
        }

        if (esp_ota_write(ota_handle, buf, read_bytes)) // <- ESP_OK=0
        {
            esp_ota_abort(ota_handle);
            xSemaphoreTake(SDMutex, portMAX_DELAY);
            {
                fclose(f);
            }
            xSemaphoreGive(SDMutex);
            stats->result = UPDATE_OTA_ABORTED;
            vTaskDelete(NULL);
        }
        stats->writtenBytes += read_bytes;
    }

    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
        fclose(f);
        remove("/s/Update.bin");
    }
    xSemaphoreGive(SDMutex);

    if (esp_ota_end(ota_handle))
    {
        stats->result = UPDATE_VALIDATE_FAIL;
        vTaskDelete(NULL);
    }

    esp_ota_set_boot_partition(update_partition);

    stats->result = UPDATE_SUCCESS;
    vTaskDelete(NULL);
}

void checkUpdate()
{
    char url[strlen(getFileDownloadPrefix()) + 33];
    char *updateChannel;
    switch (setting_updateChannel)
    {
    case 1:
        updateChannel = OTA_BETA_CHANNEL_JSON_PATH;
        break;
    default:
        updateChannel = OTA_STABLE_CHANNEL_JSON_PATH;
        break;
    }
    sprintf(url, "%s%s", getFileDownloadPrefix(), updateChannel);
    if (downloadGithubFile(url, "/s/Update.json")) // <- DOWNLOAD_RES_OK=0
        return;

    FILE *f;
    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
        f = fopen("/s/Update.json", "r");
    }
    xSemaphoreGive(SDMutex);

    if (!f)
    {
        xSemaphoreTake(SDMutex, portMAX_DELAY);
        {
            fclose(f);
        }
        xSemaphoreGive(SDMutex);
        return;
    }

    char buf[512];
    fread(buf, 1, 512, f);

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, buf, 512);

    if (error)
    {
        ESP_LOGE("checkUpdate", "deserializeJson() failed:%s", error.c_str());
        return;
    }
    else
    {
        xSemaphoreTake(SDMutex, portMAX_DELAY);
        remove("/s/Update.json");
        xSemaphoreGive(SDMutex);
    }

    /* 资源文件更新 */
    long static_resources_ver = doc["static_resources_ver"];
    if (static_resources_ver && static_resources_ver > info_static_resources_ver)
    {
        fileCheckResults[1] = VISION_FILE_SYS_FILE_CRITICAL;
    }

    /* 系统更新 */
    const char *ver = doc["ver"];
    if (!ver)
    {
        // 无版本号直接跳过
        return;
    }
    else
    {
        unsigned int new_identity_version;
        unsigned int new_major_version;
        unsigned int new_minor_version;

        int ver_check_res = sscanf(ver, "L%u.%u.%u", &new_identity_version, &new_major_version, &new_minor_version);
        if (ver_check_res < 3)
        {
            // 版本号不正确
            return;
        }

        unsigned int identity_version;
        unsigned int major_version;
        unsigned int minor_version;
        sscanf(info_appVersion, "L%u.%u.%u", &identity_version, &major_version, &minor_version);

        if (identity_version != new_identity_version && major_version >= new_major_version && minor_version >= new_minor_version)
        {
            // 版本号没有更新
            return;
        }
    }

    JsonArray local_path = doc["local_path"];
    JsonArray download_path = doc["download_path"];
    if (local_path.size() == 0 || download_path.size() == 0 || local_path.size() != download_path.size())
    {
        return;
    }

    for (size_t i = 0; i < local_path.size(); i++)
    {
        const char *dp = download_path[i];
        const char *lp = local_path[i];

        char url[strlen(getFileDownloadPrefix()) + strlen(dp) + 1];
        sprintf(url, "%s%s", getFileDownloadPrefix(), dp);
        updateFileDownload(url, lp, i == 0); // <-最后一个文件下载好后自动重启，重启检查更新文件无误后开始更新
    }
}