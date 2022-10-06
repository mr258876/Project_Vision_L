#ifndef PROJECT_VISION_L_MUTEXES
#define PROJECT_VISION_L_MUTEXES

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

// FreeRTOS互斥锁
extern SemaphoreHandle_t LVGLMutex;
extern SemaphoreHandle_t LCDMutex;
extern SemaphoreHandle_t MjpegMutex;
extern SemaphoreHandle_t MjpegReadMutex;
extern SemaphoreHandle_t NoteDataMutex;

// FreeRTOS任务句柄
extern TaskHandle_t playVideoHandle;
extern TaskHandle_t showDailyNoteLoopHandle;
extern TaskHandle_t lvglLoopHandle;

// ESP Timer 计时器
extern esp_timer_handle_t resinCalcTimer;
extern esp_timer_handle_t resinSyncTimer;
extern esp_timer_handle_t resinDisplayTimer;

#endif