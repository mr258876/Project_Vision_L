#include "system/Updating.h"

int checkUpdateConfig(LinkedList<Vision_update_info_t> *listptr)
{
    FILE *f = nullptr;
    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
        f = fopen("/s/update.json", "r");
    }
    xSemaphoreGive(SDMutex);

    if (!f)
        return UPDATE_NO_UPDATE;

    char conf_buf[1025];
    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
        fread(conf_buf, 1, 1024, f);
    }
    xSemaphoreGive(SDMutex);

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, conf_buf, 1024);

    if (error)
    {
        ESP_LOGE("checkUpdateConfig", "deserialize error");
        return UPDATE_CONFIG_ERR;
    }

    JsonArray files = doc["files"];
    if (!files || files.size() < 1)
    {
        ESP_LOGE("checkUpdateConfig", "no update file record");
        return UPDATE_CONFIG_ERR;
    }

    struct stat stat_buf;
    Vision_update_info_t file_info;
    for (size_t i = 0; i < files.size(); i++)
    {
        JsonArray file_record = files[i];
        if (!file_record || file_record.size() != 4)
            return UPDATE_CONFIG_ERR;

        const char *fn = file_record[0];
        size_t file_size = file_record[1];
        const char *offset16 = file_record[2];
        const char *partition_size16 = file_record[3];
        size_t offset = 0;
        size_t partition_size = 0;

        if (!fn || !file_size || !offset16 || !partition_size16)
        {
            ESP_LOGE("checkUpdateConfig", "missing parameter");
            return UPDATE_CONFIG_ERR;
        }

        if (sscanf(offset16, "0x%x", &offset) != 1)
        {
            ESP_LOGE("checkUpdateConfig", "error reading offset");
            return UPDATE_CONFIG_ERR;
        }

        if (sscanf(partition_size16, "0x%x", &partition_size) != 1)
        {
            ESP_LOGE("checkUpdateConfig", "error reading partition_size");
            return UPDATE_CONFIG_ERR;
        }

        file_info.filePath = fn;
        file_info.offset = offset;
        file_info.partitionSize = partition_size;
        file_info.totalBytes = file_size;
        listptr->add(file_info);
    }

    return UPDATE_SUCCESS;
}

void tsk_performUpdate(void *parameter)
{
    Vision_update_info_t *stats = (Vision_update_info_t *)parameter;

    FILE *f;
    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
        f = fopen(stats->filePath.c_str(), "rb");
    }
    xSemaphoreGive(SDMutex);
    if (!f)
    {
        stats->result = UPDATE_FILE_ERR;
        vTaskDelete(NULL);
    }

    esp_flash_t *flash = esp_flash_default_chip;
    size_t offset = stats->offset;
    size_t partition_size = stats->partitionSize;
    size_t bytes_write = 0;

    /* 擦除分区 */
    int res = esp_flash_erase_region(flash, offset, partition_size);
    if (res)
    {
        stats->code = res;
        stats->result = UPDATE_UPDATE_ABORTED;
        vTaskDelete(NULL);
    }

    /* 写入分区 */
    char buf[1024];
    size_t bytes_read = 0;
    while (1)
    {
        stats->writtenBytes += bytes_read;

        xSemaphoreTake(SDMutex, portMAX_DELAY);
        {
            bytes_read = fread(buf, 1, 1024, f);
        }
        xSemaphoreGive(SDMutex);
        if (!bytes_read)
        {
            break;
        }

        res = esp_flash_write(flash, buf, offset + bytes_write, bytes_read);
        if (res)
        {
            stats->code = res;
            stats->result = UPDATE_UPDATE_ABORTED;
            vTaskDelete(NULL);
        }

        bytes_write += bytes_read;
    }

    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
        fclose(f);
    }
    xSemaphoreGive(SDMutex);

    stats->result = UPDATE_SUCCESS;
    vTaskDelete(NULL);
}