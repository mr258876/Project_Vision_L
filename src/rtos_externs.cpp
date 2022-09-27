#include "rtos_externs.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

/* mutex */
SemaphoreHandle_t LVGLMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t LCDMutex = xSemaphoreCreateMutex();
SemaphoreHandle_t MjpegReadMutex = xSemaphoreCreateMutex();

/* tsk handle */
TaskHandle_t LVGLloopHandle;
TaskHandle_t playVideoHandle;