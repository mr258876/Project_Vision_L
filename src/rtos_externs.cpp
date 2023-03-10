#include "rtos_externs.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

SemaphoreHandle_t LGFXMutex = xSemaphoreCreateMutex();

/* SPI */
SemaphoreHandle_t SDMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t FlashMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t LCDMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t *LCDMutexptr = nullptr;
