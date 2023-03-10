#ifndef _RTOS_EXTERNS_H_
#define _RTOS_EXTERNS_H_

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

extern SemaphoreHandle_t LGFXMutex;

// SPI 互斥锁
extern SemaphoreHandle_t SDMutex;
extern SemaphoreHandle_t FlashMutex;
extern SemaphoreHandle_t LCDMutex;
extern SemaphoreHandle_t *LCDMutexptr;  // In case when SD & LCD share one SPI bus

#endif