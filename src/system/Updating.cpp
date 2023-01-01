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
    char url[strlen(getFileDownloadPrefix()) + 13];
    sprintf(url, "%s/Update.json", getFileDownloadPrefix());
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

    JsonArray files = doc["files"];
    if (files.size() == 0)
    {
        return;
    }

    uint download_err = 0;
    for (size_t i = 0; i < files.size(); i++)
    {
        char url[strlen(getFileDownloadPrefix()) + strlen(files[i][0]) + 1];
        const char *download_path = files[i][0];
        sprintf(url, "%s%s", getFileDownloadPrefix(), download_path);
        download_err = download_err | downloadGithubFile(url, files[i][1]);
        if (download_err)
        {
            break;
        }
    }

    if (download_err > 0)
    {
        for (size_t i = 0; i < files.size(); i++)
        {
            xSemaphoreTake(SDMutex, portMAX_DELAY);
            remove(files[i][1]);
            xSemaphoreGive(SDMutex);
        }
        return;
    }

    esp_restart();  // 文件下载好后重启，重启检查更新文件无误后开始更新
}