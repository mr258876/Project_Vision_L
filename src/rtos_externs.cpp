#include "rtos_externs.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

/* mutex */
SemaphoreHandle_t LVGLMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t MjpegMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t MjpegReadMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t NoteDataMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t WeatherDataMutex = xSemaphoreCreateMutex();

SemaphoreHandle_t WiFiConnectMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t APIStartupMutex = xSemaphoreCreateMutex();

/* SPI */
SemaphoreHandle_t SDMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t FlashMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t LCDMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t *LCDMutexptr = nullptr;

/* tsk handle */
TaskHandle_t playVideoHandle;
TaskHandle_t lvglLoopHandle;
TaskHandle_t screenFlushLoopHandle;
TaskHandle_t APILoopHandle;
TaskHandle_t wifiConfigHandle;

esp_timer_handle_t resinCalcTimer;
esp_timer_handle_t resinSyncTimer;
esp_timer_handle_t weatherSyncTimer;