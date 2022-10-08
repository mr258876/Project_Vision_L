#include "rtos_externs.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

/* mutex */
SemaphoreHandle_t LVGLMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t LCDMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t MjpegMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t MjpegReadMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t NoteDataMutex = xSemaphoreCreateMutex();

/* tsk handle */
TaskHandle_t playVideoHandle;
TaskHandle_t lvglLoopHandle;

esp_timer_handle_t resinCalcTimer;
esp_timer_handle_t resinSyncTimer;
esp_timer_handle_t resinDisplayTimer;