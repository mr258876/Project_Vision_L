#include "conf.h"
#include "rtos_externs.h"
#include "The_Vision_L_globals.h"

#include "system/Updating.h"

#include <FS.h>
#include <SD.h>
#include <SD_MMC.h>

#include <ff.h>
#include <diskio.h>

#include <LinkedList.h>
#include <Preferences.h>

#include "LCDPanels.h"
#include <LovyanGFX.hpp>

////////////////////////
//
//  Typedef
//
////////////////////////
enum Vision_HW_result_t
{
  VISION_HW_OK = 0,             // 硬件正常
  VISION_HW_SD_ERR = 0b1,       // SD卡初始化失败
  VISION_HW_PROX_ERR = 0b10,    // 距离传感器初始化失败
  VISION_HW_ACCEL_ERR = 0b100,  // 重力传感器初始化失败
  VISION_HW_SPIFFS_ERR = 0b1000 // SPIFFS分区初始化失败
};

////////////////////////
//
//  Variables
//
////////////////////////

/* LCD screen */
static LGFX_Device gfx;
static LGFX_Sprite canvas;

////////////////////////
//
//  Function Declartions
//
////////////////////////
static uint checkHardware();
static void prepareUpdate();
static void performUpdate();
static int verifyApp();
static bool checkRecPartition();
static bool fixRecPartition();

static void drawUI();
static void LGFXLoop(void *parameter);

////////////////////////
//
//  Functions
//
////////////////////////

/* Setup Function */
void setup()
{
  // get rec version
  const esp_app_desc_t *running_app_info = esp_ota_get_app_description();
  strcpy(info_recVersion, running_app_info->version);

  // Enable Serial output
  Serial.begin(115200);

  // Init NVS
  prefs.begin("Project_Vision", false);
  info_hwType = prefs.getUInt("hwType", 0);

  // Check Hardware Pinout
  if (!info_hwType)
  {
    uint8_t ht = getHWType();
    info_hwType = ht;
    prefs.putUInt("hwType", info_hwType);
  }
  ESP_LOGI("getPinout", "HW_version:%d", info_hwType);
  getVisionPinout(&po, info_hwType);

  // SPI Mutex
  if (po.LCD_shared_spi)
  {
    LCDMutexptr = &SDMutex;
  }
  else
  {
    LCDMutexptr = &LCDMutex;
  }

  // SD card Pull-Ups
  pinMode(po.SD_DAT0, INPUT_PULLUP);
  pinMode(po.SD_DAT3, INPUT_PULLUP);
  pinMode(po.SD_CLK, INPUT_PULLUP);
  pinMode(po.SD_CMD, INPUT_PULLUP);
  if (po.SD_DAT1)
    pinMode(po.SD_DAT1, INPUT_PULLUP);
  if (po.SD_DAT2)
    pinMode(po.SD_DAT2, INPUT_PULLUP);

  // Init Display
  LCDinit(&gfx, po.LCD_panel, po.LCD_spi_host, po.LCD_DC, po.LCD_RST, po.LCD_CS, po.LCD_CLK, po.LCD_MOSI, po.LCD_MISO, po.LCD_shared_spi, po.LCD_clock_speed);
  gfx.init();
  gfx.setColorDepth(8);
  gfx.setSwapBytes(false);
  gfx.fillScreen(TFT_BLACK);
  drawUI();

  ledcAttachPin(po.LCD_BL, 1); // assign TFT_BL pin to channel 2
  ledcSetup(1, 48000, 8);      // 48 kHz PWM, 8-bit resolution
  ledcWrite(1, 255);           // brightness 0 - 255

  // SD card init
  if (po.SD_use_sdmmc)
  {
    if (po.SD_use_1_bit)
    {
      SD_MMC.setPins(po.SD_CLK, po.SD_CMD, po.SD_DAT0);
    }
    else
    {
      SD_MMC.setPins(po.SD_CLK, po.SD_CMD, po.SD_DAT0, po.SD_DAT1, po.SD_DAT2, po.SD_DAT3);
    }
    SD_MMC.begin("/s", po.SD_use_1_bit, false, SDMMC_FREQ_HIGHSPEED);
  }
  else
  {
    SPI.begin(po.SD_CLK, po.SD_DAT0, po.SD_CMD, po.SD_DAT3);
    SD.begin(po.SD_DAT3, SPI, 40000000, "/s");
  }

  ////////// End of Boot Process //////////

  bool info_hasUpdated = prefs.getBool("hasUpdated", false);
  if (info_hasUpdated)
  {
    // 若更新标志位为true则为刚更新过，检查app分区（自动更新前app应将此标志位设为false）
    verifyApp();
  }

  prepareUpdate();
}

#ifdef USE_TASK_MONITOR
uint8_t CPU_RunInfo[512];
#endif
void loop()
{
#ifdef USE_TASK_MONITOR
  /* Enable FreeRTOS runtime stats in menuconfig before use */
  ESP_LOGI("loop", "Free MEM:%d\n", esp_get_free_heap_size());
  ESP_LOGI("loop", "Max Free Block:%d\n", heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT));

  memset(CPU_RunInfo, 0, 512);
  vTaskList((char *)&CPU_RunInfo); // 获取任务运行时间信息
  printf("---------------------------------------------\r\n");
  printf("任务名       任务状态     优先级     剩余栈     任务序号\r\n");
  printf("%s", CPU_RunInfo);
  printf("---------------------------------------------\r\n");
  memset(CPU_RunInfo, 0, 512);
  vTaskGetRunTimeStats((char *)&CPU_RunInfo);
  printf("任务名         运行计数     使用率\r\n");
  printf("%s", CPU_RunInfo);
  printf("---------------------------------------------\r\n\n");

  vTaskDelay(pdMS_TO_TICKS(2000));
#else
  vTaskDelete(NULL);
#endif
}

////////////////////////
//
//  Hardware Checkup
//
////////////////////////
static uint checkHardware()
{
  int err = VISION_HW_OK;

  /* check sd card */
  sdcard_type_t cardType;
  xSemaphoreTake(SDMutex, portMAX_DELAY);
  {
    if (po.SD_use_sdmmc)
      cardType = SD_MMC.cardType();
    else
      cardType = SD.cardType();
  }
  xSemaphoreGive(SDMutex);
  switch (cardType)
  {
  case CARD_NONE:
  case CARD_UNKNOWN:
    err = err | VISION_HW_SD_ERR;
    ESP_LOGE("checkHardware", "Bad SD Card!");
    break;
  default:
    break;
  }

  return err;
}

static void prepareUpdate()
{
  int hwErr = 0;
  String errMsg = "";

  /* 硬件检查 */
  xSemaphoreTake(LGFXMutex, portMAX_DELAY);
  {
    canvas.print("Check hardware...");
  }
  xSemaphoreGive(LGFXMutex);

  hwErr = checkHardware();
  if (hwErr)
  {
    xSemaphoreTake(LGFXMutex, portMAX_DELAY);
    {
      canvas.setTextColor(TFT_RED, TFT_BLACK);
      canvas.print("fail\n");
      canvas.setTextColor(TFT_WHITE);
      canvas.print("No SD card!\n");
    }
    xSemaphoreGive(LGFXMutex);

    verifyApp();
    return;
  }

  xSemaphoreTake(LGFXMutex, portMAX_DELAY);
  {
    canvas.setTextColor(TFT_GREEN, TFT_BLACK);
    canvas.print("ok\n");
    canvas.setTextColor(TFT_WHITE);
  }
  xSemaphoreGive(LGFXMutex);

  if (!checkRecPartition())
  {
    xSemaphoreTake(LGFXMutex, portMAX_DELAY);
    {
      canvas.setTextColor(TFT_YELLOW, TFT_BLACK);
      canvas.println("Recovery not in correct partition.");
      canvas.setTextColor(TFT_WHITE);
    }
    xSemaphoreGive(LGFXMutex);
    if (fixRecPartition())
    {
      xSemaphoreTake(LGFXMutex, portMAX_DELAY);
      {
        canvas.println("Fixing recovery.");
      }
      xSemaphoreGive(LGFXMutex);

      performUpdate();
    }
    else
    {
      xSemaphoreTake(LGFXMutex, portMAX_DELAY);
      {
        canvas.setTextColor(TFT_RED, TFT_BLACK);
        canvas.println("recovery.bin missing! Could not fix recovery.");
        canvas.setTextColor(TFT_WHITE);
      }
      xSemaphoreGive(LGFXMutex);
    }
    return;
  }

  /* 读取update.json并检查文件大小 */
  int check_res = checkUpdateConfig(&updateList);
  if (check_res == 1)
  {
    performUpdate();
  }
  else if (check_res == 0)
  {
    xSemaphoreTake(LGFXMutex, portMAX_DELAY);
    {
      canvas.setTextColor(TFT_YELLOW, TFT_BLACK);
      canvas.print("Update files not detected.\n");
      canvas.setTextColor(TFT_WHITE);
    }
    xSemaphoreGive(LGFXMutex);

    verifyApp();
    return;
  }
  else
  {
    xSemaphoreTake(LGFXMutex, portMAX_DELAY);
    {
      canvas.setTextColor(TFT_RED, TFT_BLACK);
      canvas.printf("Update file error! Result was: [%d]\n", check_res);
      canvas.setTextColor(TFT_WHITE);
    }
    xSemaphoreGive(LGFXMutex);
  }
}

static void performUpdate()
{
  xSemaphoreTake(LGFXMutex, portMAX_DELAY);
  {
    canvas.println("Update files detected, preparing update.");
    canvas.setTextColor(TFT_YELLOW, TFT_BLACK);
    canvas.println("DO NOT POWER OFF!");
    canvas.setTextColor(TFT_WHITE);
  }
  xSemaphoreGive(LGFXMutex);

  bool hasError = false;
  for (size_t i = 0; i < updateList.size(); i++)
  {
    Vision_update_info_t update_info = updateList.get(i);
    xSemaphoreTake(LGFXMutex, portMAX_DELAY);
    canvas.printf("Writing %s at %#x.", update_info.filePath.c_str(), update_info.offset);
    xSemaphoreGive(LGFXMutex);

    /* 创建执行更新任务 */
    xTaskCreatePinnedToCore(tsk_performUpdate,
                            "tsk_performUpdate",
                            4096,
                            &update_info,
                            1,
                            NULL,
                            0);
    while (!update_info.result)
    {
      xSemaphoreTake(LGFXMutex, portMAX_DELAY);
      canvas.print(".");
      xSemaphoreGive(LGFXMutex);
      vTaskDelay(pdMS_TO_TICKS(500));
    }

    /* 显示结果 */
    if (update_info.result == UPDATE_SUCCESS)
    {
      xSemaphoreTake(LGFXMutex, portMAX_DELAY);
      {
        canvas.setTextColor(TFT_GREEN);
        canvas.println("ok");
        canvas.setTextColor(TFT_WHITE);
      }
      xSemaphoreGive(LGFXMutex);
    }
    else
    {
      xSemaphoreTake(LGFXMutex, portMAX_DELAY);
      {
        canvas.setTextColor(TFT_RED);
        canvas.println("fail!");
        canvas.printf("result was:%d, code:%#x\n", update_info.result, update_info.code);
        canvas.setTextColor(TFT_WHITE);
      }
      xSemaphoreGive(LGFXMutex);
      hasError = true;
      break;
    }
  }

  if (!hasError)
  {
    xSemaphoreTake(LGFXMutex, portMAX_DELAY);
    {
      canvas.setTextColor(TFT_GREEN, TFT_BLACK);
      canvas.println("Update success!");
      canvas.setTextColor(TFT_YELLOW, TFT_BLACK);
      canvas.println("Cleaning files...");
    }
    xSemaphoreGive(LGFXMutex);

    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
      for (size_t i = 0; i < updateList.size(); i++)
      {
        Vision_update_info_t update_info = updateList.get(i);
        remove(update_info.filePath.c_str());
      }
      remove("/s/update.json");
    }
    xSemaphoreGive(SDMutex);

    xSemaphoreTake(LGFXMutex, portMAX_DELAY);
    {
      canvas.println("Rebooting in 5 secs.");
    }
    xSemaphoreGive(LGFXMutex);
    vTaskDelay(pdMS_TO_TICKS(5000));

    prefs.putBool("hasUpdated", true);

    esp_restart();
  }
  else
  {
    xSemaphoreTake(LGFXMutex, portMAX_DELAY);
    {
      canvas.setTextColor(TFT_RED, TFT_BLACK);
      canvas.println("Update failed!");
    }
    xSemaphoreGive(LGFXMutex);
  }
}

static int verifyApp()
{
  xSemaphoreTake(LGFXMutex, portMAX_DELAY);
  {
    canvas.println("Check app partition...");
  }
  xSemaphoreGive(LGFXMutex);

  // get ota partition
  const esp_partition_t *ota_partition = esp_partition_find_first(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_0, NULL);
  if (!ota_partition)
  {
    // 未找到ota分区
    xSemaphoreTake(LGFXMutex, portMAX_DELAY);
    {
      canvas.setTextColor(TFT_RED, TFT_BLACK);
      canvas.println("App partition not found!");
      canvas.setTextColor(TFT_WHITE);
    }
    xSemaphoreGive(LGFXMutex);
    return -1;
  }

  if (ota_partition == esp_ota_get_running_partition())
  {
    // 当前分区为ota0分区
    xSemaphoreTake(LGFXMutex, portMAX_DELAY);
    {
      canvas.setTextColor(TFT_YELLOW, TFT_BLACK);
      canvas.println("Recovery in App partition! Reboot might solve this problem.");
      canvas.setTextColor(TFT_WHITE);
    }
    xSemaphoreGive(LGFXMutex);
    return -2;
  }

  // get app version
  esp_app_desc_t ota_app_info;
  int opt_res = esp_ota_get_partition_description(ota_partition, &ota_app_info);
  if (opt_res)
  {
    // 读取分区信息出错
    xSemaphoreTake(LGFXMutex, portMAX_DELAY);
    {
      canvas.setTextColor(TFT_RED, TFT_BLACK);
      canvas.printf("Failed to read app info! [%d]\n", opt_res);
      canvas.setTextColor(TFT_WHITE);
    }
    xSemaphoreGive(LGFXMutex);
    return -2;
  }

  strcpy(info_appVersion, ota_app_info.version);
  xSemaphoreTake(LGFXMutex, portMAX_DELAY);
  {
    canvas.setTextColor(TFT_GREEN, TFT_BLACK);
    canvas.printf("App found. ver:%s\n", info_appVersion);
    canvas.setTextColor(TFT_WHITE);
  }
  xSemaphoreGive(LGFXMutex);

  esp_ota_img_states_t app_status;
  esp_ota_get_state_partition(ota_partition, &app_status);
  xSemaphoreTake(LGFXMutex, portMAX_DELAY);
  {
    canvas.setTextColor(TFT_GREEN, TFT_BLACK);
    canvas.printf("App status:%d\n", app_status);
    canvas.setTextColor(TFT_WHITE);
  }
  xSemaphoreGive(LGFXMutex);

  esp_ota_set_boot_partition(ota_partition);
  xSemaphoreTake(LGFXMutex, portMAX_DELAY);
  {
    canvas.print("App set to active!\n");
    canvas.setTextColor(TFT_YELLOW, TFT_BLACK);
    canvas.print("Rebooting in 5 secs.\n");
  }
  xSemaphoreGive(LGFXMutex);
  vTaskDelay(pdMS_TO_TICKS(5000));
  esp_restart();

  return 0;
}

static bool checkRecPartition()
{
  const esp_partition_t *running_partition = esp_ota_get_running_partition();
  if (running_partition->subtype == ESP_PARTITION_SUBTYPE_APP_FACTORY || running_partition->subtype == ESP_PARTITION_SUBTYPE_APP_OTA_0)
    return true;
  return false;
}

static bool fixRecPartition()
{
  FILE *f;
  xSemaphoreTake(SDMutex, portMAX_DELAY);
  {
    f = fopen("/s/The Vision L/update/recovery.bin", "rb");
  }
  xSemaphoreGive(SDMutex);

  if (!f)
    return false;

  size_t file_size;
  xSemaphoreTake(SDMutex, portMAX_DELAY);
  {
    fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    fclose(f);
  }
  xSemaphoreGive(SDMutex);

  Vision_update_info_t file_info;
  file_info.filePath = "/s/The Vision L/update/recovery.bin";
  file_info.offset = 0x10000;
  file_info.partitionSize = 0x60000;
  file_info.totalBytes = file_size;
  updateList.add(file_info);

  return true;
}

////////////////////////
//
//  User Interface
//
////////////////////////
static void drawUI()
{
  gfx.setTextSize(2);
  gfx.setTextDatum(top_center);
  gfx.drawString("Recovery mode", 120, 20);
  gfx.setTextColor(TFT_RED, TFT_BLACK);
  gfx.setTextDatum(bottom_center);
  gfx.setTextSize(1.75);
  gfx.drawCenterString("DO NOT POWER OFF!", 120, 210);
  gfx.setCursor(60, 235);
  gfx.setTextSize(1);
  gfx.setTextColor(TFT_WHITE, TFT_BLACK);
  gfx.printf("rec ver.%s\n", info_recVersion);

  gfx.drawFastHLine(36, 36, 168, 0xFFFFFFU);
  gfx.drawFastHLine(36, 204, 168, 0xFFFFFFU);
  gfx.drawFastVLine(36, 36, 168, 0xFFFFFFU);
  gfx.drawFastVLine(204, 36, 168, 0xFFFFFFU);

  canvas.setColorDepth(8);
  canvas.createSprite(165, 165);

  xTaskCreatePinnedToCore(LGFXLoop, "LGFXLoop", 2048, NULL, 0, NULL, 1);
}

static void LGFXLoop(void *parameter)
{
  while (1)
  {
    xSemaphoreTake(LGFXMutex, portMAX_DELAY);
    {
      while (canvas.getCursorY() > 151)
      {
        canvas.copyRect(0, 0, 165, 152, 0, 8);
        canvas.setCursor(canvas.getCursorX(), canvas.getCursorY() - 8);
      }

      xSemaphoreTake(*LCDMutexptr, portMAX_DELAY);
      {
        canvas.pushSprite(&gfx, 38, 38);
      }
      xSemaphoreGive(*LCDMutexptr);
    }
    xSemaphoreGive(LGFXMutex);
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}