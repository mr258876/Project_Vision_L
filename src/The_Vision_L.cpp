#include "conf.h"
#include "rtos_externs.h"
#include "The_Vision_L_globals.h"

#include "system/FileCheck.h"
#include "system/TimeManager.h"
#include "system/Networking.h"
#include "system/Updating.h"

#include <FS.h>
#include <SD.h>
#include <SD_MMC.h>
#include <SPIFFS.h>

#include <ff.h>
#include <diskio.h>

#include <lvgl.h>
#include "ui/lv_fs_fatfs.h"
#include "ui/ui.h"
#include "ui/ui_multiLanguage.h"
#include "ui/ui_supply_functions.h"

#include <LinkedList.h>
#include <Preferences.h>

#include "LCDPanels.h"
#include <LovyanGFX.hpp>
#include "BrightnessController.h"

#include "mjpeg/MjpegClass.h"

#include <Wire.h>
#include <APDS9930.h>
#undef DEFAULT_ATIME
#define DEFAULT_ATIME 0xDB // <- 将亮度传感器采样时间改为100ms

#include <OneButton.h>
#include <kxtj3-1057.h>
#undef getName

#include "hoyoverse/Hoyoverse.h"
#include "api/APIServer.h"
#include "weather/MojiTianqi.h"
#include "weather/OpenMeteo.h"

// #include "sound/DACOutput.h"
// #include "sound/WAVFileReader.h"

// Freertos
#include <rtc_wdt.h>

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
//  Structs
//
////////////////////////
struct ScreenFlushMsg
{
  lv_disp_drv_t *disp;
  lv_color_t *color_p;
  lv_coord_t x1;
  lv_coord_t x2;
  lv_coord_t y1;
  lv_coord_t y2;
};

////////////////////////
//
//  Variables
//
////////////////////////
/* Pwr button & Audio */
static OneButton *pwrButton;

/* LCD screen */
static LGFX_Device gfx;

/* LVGL Stuff */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_color_t *disp_draw_buf_2;
static lv_disp_drv_t disp_drv;
bool isInLVGL = true;

/* Mjpeg stuff */
uint8_t *vFileReadBuf = (uint8_t *)malloc(MJPEG_BUFFER_SIZE);
bool mjpegInited = false;

/* Proximity sensor Object */
APDS9930 apds;
OneButton *proxButton = NULL;
BrightnessController brightControl;

/* Accelmeter Object */
#define LOW_POWER
KXTJ3 acc(0x0E);
int rotation = 0;

/* Audio */
// SampleSource *wav;
// DACOutput *aOut;

////////////////////////
//
//  Function Declartions
//
////////////////////////
static void loadSettings();
static uint checkHardware();
static bool getDailyNote(Notedata *nd, String *errMsg);
static void resinCalc(void *parameter);
static void resinSync(void *parameter);
static void weatherSync(void *parameter);

static void setAPIserver_async(void *parameter);

static void mjpegInit();
static void leaveVideoScreen(void *parameter);
static void loadVideoScreen(void *parameter);
static void playVideo(void *parameter);

static void getDailyNoteFromResinScreen(void *parameter);

static void lvglLoop(void *parameter);
static void screenAdjustLoop(void *parameter);

static void onChangeVideo();
static void onSingleClick();
static void onDoubleClick();
static void onMultiClick();

////////////////////////
//
//  Functions
//
////////////////////////
/**
 * @brief Custom scren update function for LVGL
 */
void disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  lv_coord_t w = (area->x2 - area->x1 + 1);
  lv_coord_t h = (area->y2 - area->y1 + 1);

  if (xSemaphoreTake(*LCDMutexptr, portMAX_DELAY) == pdTRUE)
  {
    gfx.setAddrWindow(area->x1, area->y1, w, h);
    gfx.pushPixelsDMA((uint16_t *)&color_p->full, w * h);
    xSemaphoreGive(*LCDMutexptr);
  }
  lv_disp_flush_ready(disp);
}

/* Setup Function */
void setup()
{
  // Disable watchdog write protect to feed manually
  rtc_wdt_protect_off();

  // Enable Serial output
  Serial.begin(115200);

  // Init NVS
  prefs.begin("Project_Vision", false);
  loadSettings();

  // Check Hardware Pinout
  if (!info_hwType)
  {
    uint8_t ht = getHWType();
    info_hwType = ht;
    prefs.putUInt("hwType", info_hwType);
  }
  ESP_LOGI("getPinout", "HW_version:%d", info_hwType);
  getVisionPinout(&po, info_hwType);

  if (po.LCD_panel)
  {
    info_isSquareLCD = false;
  }
  else
  {
    info_isSquareLCD = true;
  }

  // I2C pins
  if (po.I2C_SDA && po.I2C_SCL)
  {
    Wire.setPins(po.I2C_SDA, po.I2C_SCL);
  }

  // Buttons
  pwrButton = new OneButton(po.PWR_BTN, true);

  // Audio Output
  // if (po.AUDIO_OUT)
  // {
  //   aOut = new DACOutput();
  //   aOut->init(po.AUDIO_OUT);
  // }

  // SPI Mutex
  if (po.LCD_shared_spi)
  {
    LCDMutexptr = &SDMutex;
  }
  else
  {
    LCDMutexptr = &LCDMutex;
  }

  // Internal flash init
  // 内部flash不使用fatfs
  if (SPIFFS.begin(true, "/f"))
  {
    ESP_LOGI("setup", "SPIFFS partition mounted!");
  }
  else
  {
    ESP_LOGE("setup", "SPIFFS partition mount failed!");
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
  gfx.setColorDepth(16);
  gfx.setSwapBytes(false);
  gfx.fillScreen(TFT_BLACK);

  ledcAttachPin(po.LCD_BL, 1);            // assign TFT_BL pin to channel 2
  ledcSetup(1, 48000, 8);                 // 48 kHz PWM, 8-bit resolution
  ledcWrite(1, setting_screenBrightness); // brightness 0 - 255
  switch (po.LCD_panel)
  {
  case LCD_ST7789:
    brightControl.setMaxScreenNit(500);
    brightControl.setDisplayNit_BrightnessLevelFunction(brightness_nit_level_curve_ST7789);
    break;
  case LCD_GC9A01:
    brightControl.setMaxScreenNit(400);
    brightControl.setDisplayNit_BrightnessLevelFunction(brightness_nit_level_curve_ST7789);
    break;
  default:
    break;
  }

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
    sdfs = &SD_MMC;
  }
  else
  {
    SPI.begin(po.SD_CLK, po.SD_DAT0, po.SD_CMD, po.SD_DAT3);
    SD.begin(po.SD_DAT3, SPI, 40000000, "/s");
    sdfs = &SD;
  }

  // WiFi init
  WiFi.onEvent(wifiEvent_handler); // 注册事件处理程序

  // LVGL init
  lv_init();

  screenWidth = gfx.width();
  screenHeight = gfx.height();

  if (!vFileReadBuf)
  {
    ESP_LOGE("setup", "Video file buffer allocate failed!");
  }

  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 30, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  disp_draw_buf_2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 30, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

  if (!disp_draw_buf || !disp_draw_buf_2)
  {
    ESP_LOGE("setup", "LVGL disp_draw_buf allocate failed!");
  }
  else
  {
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, disp_draw_buf_2, screenWidth * 30);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.sw_rotate = 0;
    disp_drv.full_refresh = 0;

    lv_disp_drv_register(&disp_drv);

    /* Initialize input device driver */
    // lv_indev_button_encoder_init();

    /* Initialize file system */
    lv_fs_fatfs_init();

    ui_init();

    /* Create lvgl task */
    xTaskCreatePinnedToCore(lvglLoop,        // 任务函数
                            "lvglLoop",      // 任务名称
                            8192,            // 任务堆栈大小
                            NULL,            // 任务参数
                            1,               // 任务优先级
                            &lvglLoopHandle, // 任务句柄
                            1);              // 执行任务核心

    LV_LOG_INFO("LVGL booted.");
  }
}

uint8_t CPU_RunInfo[512];
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

// Load Settings From NVS
static void loadSettings()
{
  info_hwType = prefs.getUInt("hwType", 0);
  info_deviceGuid = prefs.getString("deviceGuid", "");

  curr_lang = prefs.getUInt("language", 1);

  // get device name
  uint8_t sta_mac[8];
  WiFi.macAddress(sta_mac);
  setting_deviceName = prefs.getString("deviceName", String("Vision_") + String(sta_mac[4], HEX) + String(sta_mac[5], HEX));

  // get mac address
  String mac = String(sta_mac[0], HEX);
  for (size_t i = 1; i < 6; i++)
  {
    if ((sta_mac[i]) < 16)
      mac.concat(0);
    mac.concat(String(sta_mac[i], HEX));
  }
  mac.toUpperCase();
  strcpy(info_macAddress, mac.c_str());

  // get setting values
  setting_autoBright = prefs.getBool("useAutoBright", true);
  setting_useAccel = prefs.getBool("useAccelMeter", true);

  setting_screenDirection = prefs.getUInt("screenDirection", 0);
  setting_screenBrightness = prefs.getUInt("screenBrightness", LCD_BRIGHTNESS);

  setting_soundMuted = prefs.getBool("soundMuted", false);
  setting_soundVolume = prefs.getUInt("soundVolume", 75);

  setting_resinSyncPeriod = prefs.getULong("resinSyncPeriod", 1800000000);

  setting_useDigitalClock = prefs.getBool("useDigitalClock", false);

  setting_timeZone = prefs.getString("timeZone", "");

  setting_autoUpdate = prefs.getBool("autoUpdate", true);
  setting_updateChannel = prefs.getUInt("updateChannel", 0);

  setting_proxThres = prefs.getUInt("proxThres", 210);

  // get app version
  const esp_app_desc_t *running_app_info = esp_ota_get_app_description();
  strcpy(info_appVersion, running_app_info->version);

  // get Hoyolab conf
  String hoyolab_uid = prefs.getString("hoyolabUID", "");
  String hoyolab_cookie = prefs.getString("hoyolabCookie", "");
  hyc.begin(hoyolab_cookie.c_str(), hoyolab_uid.c_str());
  if (info_deviceGuid.length() == 32)
  {
    hyc.setDeviceGuid(info_deviceGuid.c_str());
  }
  else
  {
    // gengrate a new guid if not exist
    info_deviceGuid = HoyoverseClient::generateGuid();
    prefs.putString("deviceGuid", info_deviceGuid);
    hyc.setDeviceGuid(info_deviceGuid.c_str());
  }

  // get weather conf
  setting_weatherProvider = 0; // <- Mojitianqi not avaliable since Feb 10, 2023
  // setting_weatherProvider = prefs.getInt("weatherProvider", -1);
  // if (setting_weatherProvider == -1)
  // {
  //   setting_weatherProvider = curr_lang;
  // }
  String cityName = prefs.getString("weatherCity", "");
  float latitude = prefs.getFloat("weatherLat", NULL);
  float longitude = prefs.getFloat("weatherLon", NULL);
  switch (setting_weatherProvider)
  {
  case 0:
    wp = &OpenMeteo;
    break;
  default:
    wp = &MojiTianqi;
    break;
  }
  wp->setCity(cityName.c_str());
  wp->setCoordinate(latitude, longitude);
}

static void mjpegInit()
{
  // Mjpeg初始化
  int fileNo = prefs.getUInt("currFileId", 0);
  if (!mjpeg.setup(filePaths.get(fileNo).c_str(), vFileReadBuf, &gfx, true, screenWidth, screenHeight))
  {
    ESP_LOGE("mjpegInit", "Mjpeg decoder init failed!");
  }

  // Create task of video playing
  xTaskCreatePinnedToCore(playVideo,        // 任务函数
                          "playVideo",      // 任务名称
                          2048,             // 任务堆栈大小
                          NULL,             // 任务参数
                          2,                // 任务优先级
                          &playVideoHandle, // 任务句柄
                          1);               // 执行任务核心
}

////////////////////////
//
//  Hardware Checkup
//
////////////////////////
static uint checkHardware()
{
  int err = VISION_HW_OK;
  if (po.I2C_SDA && po.I2C_SCL)
  {
    /* check proximity sensor */
    xSemaphoreTake(I2CMutex, portMAX_DELAY);
    {
      if (apds.begin())
      {
        info_hasProx = true;
      }
      else
      {
        info_hasProx = false;
        err = (err | VISION_HW_PROX_ERR);
        ESP_LOGE("checkHardware", "Prox sensor init failed!");
      }
      /* check accel meter */
      if (acc.begin(ACC_SAMPLE_RATE, ACC_RANGE) == 0)
        info_hasAccel = true;
      else
      {
        info_hasAccel = false;
        err = err | VISION_HW_ACCEL_ERR;
        ESP_LOGE("checkHardware", "Accel Meter init failed!");
      }
    }
    xSemaphoreGive(I2CMutex);
  }
  else
  {
    setting_autoBright = false;
    setting_useAccel = false;
  }

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
    info_hasSD = false;
    err = err | VISION_HW_SD_ERR;
    ESP_LOGE("checkHardware", "Bad SD Card!");
    break;
  default:
    info_hasSD = true;
  }

  /* check SPIFFS */
  if (!SPIFFS.totalBytes())
  {
    err = err | VISION_HW_SPIFFS_ERR;
    ESP_LOGE("checkHardware", "SPIFFS Fail!");
  }

  return err;
}

void hardwareSetup(void *parameter)
{
  uint hwErr = 0;
  uint fileErr = 0;
  uint weatherErr = 0;
  bool hasWifi = false;
  String errMsg = "";

  /* 硬件检查 */
  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_label_set_text(ui_StartupLabel2, lang[curr_lang][4]); // "正在检查硬件..."
    xSemaphoreGive(LVGLMutex);
  }
  hwErr = checkHardware();

  /* 文件检查 */
  if (!(hwErr & VISION_HW_SD_ERR))
  {
    /* 更新Recovery */
    if (updateFileAvaliable("/s/Recovery.bin"))
    {
      xSemaphoreTake(LVGLMutex, portMAX_DELAY);
      {
        lv_label_set_text_fmt(ui_StartupLabel1, lang[curr_lang][6], 0); //"正在升级(%d%%)..."
        lv_label_set_text(ui_StartupLabel2, lang[curr_lang][7]);        // "请不要关闭电源\n或拔出SD卡"
      }
      xSemaphoreGive(LVGLMutex);

      Vision_update_info_t update_info;

      /* 创建执行更新任务 */
      xTaskCreatePinnedToCore(tsk_performUpdate, "tsk_performUpdate", 4096, &update_info, 1, NULL, 0);
      while (!update_info.result)
      {
        xSemaphoreTake(LVGLMutex, portMAX_DELAY);
        lv_label_set_text_fmt(ui_StartupLabel1, lang[curr_lang][6], (int)(100.0 * update_info.writtenBytes / (update_info.totalBytes + 1))); //"正在升级(%d%%)..."
        xSemaphoreGive(LVGLMutex);
        vTaskDelay(pdMS_TO_TICKS(100));
      }

      /* 显示结果 */
      if (update_info.result == UPDATE_SUCCESS)
      {
        esp_restart();
      }
      else
      {
        xSemaphoreTake(LVGLMutex, portMAX_DELAY);
        {
          mbox = lv_msgbox_create(ui_StartupScreen, lang[curr_lang][18], lang[curr_lang][19], {}, false); // LV_SYMBOL_WARNING " 更新失败"  "请通过串口手动更新固件"
          lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_obj_center(mbox);
        }
        xSemaphoreGive(LVGLMutex);
        vTaskDelete(NULL);
      }
    }

    /* 更新App */
    if (updateFileAvaliable("/s/Update.bin"))
    {
      xSemaphoreTake(LVGLMutex, portMAX_DELAY);
      {
        lv_label_set_text_fmt(ui_StartupLabel1, lang[curr_lang][6], 0); //"正在升级(%d%%)..."
        lv_label_set_text(ui_StartupLabel2, lang[curr_lang][7]);        // "请不要关闭电源\n或拔出SD卡"
      }
      xSemaphoreGive(LVGLMutex);

      FILE *f;
      size_t file_size = 0;
      xSemaphoreTake(SDMutex, portMAX_DELAY);
      {
        f = fopen("/s/Update.bin", "rb");
        fseek(f, 0, SEEK_END);
        file_size = ftell(f);
        fclose(f);
      }
      xSemaphoreGive(SDMutex);

      const esp_partition_t *curr_part = esp_ota_get_running_partition();
      char offset_str[11];
      char part_size_str[11];
      sprintf(offset_str, "%#x", curr_part->address);
      sprintf(part_size_str, "%#x", curr_part->size);

      StaticJsonDocument<192> doc;
      JsonArray files = doc.createNestedArray("files");
      JsonArray files_0 = files.createNestedArray();
      files_0.add("/s/Update.bin");
      files_0.add(file_size);
      files_0.add(offset_str);
      files_0.add(part_size_str);

      char json_buf[256];
      serializeJson(doc, json_buf);

      xSemaphoreTake(SDMutex, portMAX_DELAY);
      {
        f = fopen("/s/update.json", "w");
        fwrite(json_buf, 1, strlen(json_buf), f);
        fclose(f);
      }
      xSemaphoreGive(SDMutex);

      esp_ota_set_boot_partition(esp_partition_find_first(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_FACTORY, NULL));
      esp_restart();
    }

    /* 检查文件 */
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_label_set_text(ui_StartupLabel2, lang[curr_lang][5]); //"正在检查文件..."
      xSemaphoreGive(LVGLMutex);
    }
    fileErr = checkSDFiles();
  }

  // 若检查到错误则停止启动
  if (hwErr & VISION_HW_SPIFFS_ERR)
  {
    ESP_LOGE("hardwareSetup", "Hardware err Detected!!!");
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      mbox = lv_msgbox_create(ui_StartupScreen, lang[curr_lang][8], errMsg.c_str(), {}, false); // LV_SYMBOL_WARNING " 发现如下问题,启动已终止:"
      lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_center(mbox);
      xSemaphoreGive(LVGLMutex);
    }
    vTaskDelete(NULL);
  }

  // 检查网络配置
  if (prefs.getUInt("wifiConfigured", 0) == 0)
  {
    // 若无已保存网络则进入配网
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      cb_loadWifiConfigInfoStartupScreen(NULL);
      xSemaphoreGive(LVGLMutex);
    }

    wifiConfigure(NULL);

    vTaskDelete(NULL);
  }
  else
  {
    // 若有已保存网络则尝试联网
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_label_set_text(ui_StartupLabel2, lang[curr_lang][14]); // "连接至网络..."
      xSemaphoreGive(LVGLMutex);
    }
    hasWifi = connectWiFi();
  }

  if (hasWifi)
  {
    /* 对时 */
    if (!info_timeSynced)
    {
      if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
      {
        lv_label_set_text(ui_StartupLabel2, lang[curr_lang][95]); // "正在对时..."
        xSemaphoreGive(LVGLMutex);
      }

      syncTime_NTP_async();
      unsigned long time_startNTP = millis();
      while (1)
      {
        if (info_timeSynced || millis() - time_startNTP > 20000)
        {
          break;
        }
        vTaskDelay(50);
      }
    }

    /* 查询树脂 */
    if (info_timeSynced) // <- 未对时无法生成动态盐值
    {
      xSemaphoreTake(LVGLMutex, portMAX_DELAY);
      lv_label_set_text(ui_StartupLabel2, lang[curr_lang][96]); // "查询树脂..."
      xSemaphoreGive(LVGLMutex);
    }
    getDailyNote(&nd, &errMsg);

    /* 查询天气 */
    if (info_timeSynced) // <- 未对时无法进入数字时钟界面
    {
      xSemaphoreTake(LVGLMutex, portMAX_DELAY);
      lv_label_set_text(ui_StartupLabel2, lang[curr_lang][97]); // "查询天气..."
      xSemaphoreGive(LVGLMutex);
    }
    weatherErr = wp->getCurrentWeather(&weather);

    /* 检查更新 */
    bool hasUpdate = false;
    if (setting_autoUpdate && !(hwErr & VISION_HW_SD_ERR)) // 没有SD卡无法自动更新
    {
      if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
      {
        lv_label_set_text(ui_StartupLabel2, lang[curr_lang][110]); // "正在检查更新..."
        xSemaphoreGive(LVGLMutex);
      }
      hasUpdate = checkUpdate();
    }

    /* 下载缺失文件 */
    fileErr = fileErr | checkFileStatus();
    if ((fileErr & VISION_FILE_SYS_FILE_ERR || fileErr & VISION_FILE_SYS_FILE_CRITICAL || fileErr & VISION_FILE_STATIC_FILE_ERR || hasUpdate) && !(hwErr & VISION_HW_SD_ERR))
    {
      Vision_download_info_t info;
      xSemaphoreTake(LVGLMutex, portMAX_DELAY);
      {
        lv_label_set_text_fmt(ui_StartupLabel2, lang[curr_lang][98], 0, 0); // "下载文件 %d/%d"
      }
      xSemaphoreGive(LVGLMutex);

      xTaskCreatePinnedToCore(tsk_fixMissingFiles,
                              "tsk_fixMissingFiles",
                              4096,
                              &info,
                              2,
                              NULL,
                              0);

      size_t last_writtenBytes = 0;
      while (info.result == DOWNLOAD_RES_DOWNLOADING)
      {
        xSemaphoreTake(LVGLMutex, portMAX_DELAY);
        {
          lv_label_set_text_fmt(ui_StartupLabel2, lang[curr_lang][98], info.current_file_no, info.total_file_count); // "下载文件 %d/%d"
        }
        xSemaphoreGive(LVGLMutex);
        last_writtenBytes = info.writtenBytes;
        vTaskDelay(pdMS_TO_TICKS(1000));
      }

      fileErr = checkFileStatus();
    }

    /* 关闭Wifi */
    if (hasWifi)
    {
      disConnectWiFi();
    }
  }

  if (!(hwErr & VISION_HW_PROX_ERR))
  {
    apds.enableLightSensor(false);
    apds.enableProximitySensor(true);
    apds.setProximityIntLowThreshold(0);
    apds.setProximityIntHighThreshold(setting_proxThres);
    pinMode(po.PROX_INT, INPUT_PULLUP);
    proxButton = new OneButton(po.PROX_INT, true);
    proxButton->attachDoubleClick(onChangeVideo);
  }

  pinMode(po.PWR_BTN, INPUT);
  pwrButton->attachClick(onSingleClick);
  pwrButton->attachDoubleClick(onDoubleClick);
  pwrButton->attachMultiClick(onMultiClick);

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_label_set_text(ui_StartupLabel2, lang[curr_lang][3]); // "请稍候..."
    xSemaphoreGive(LVGLMutex);
  }

  /* 显示错误信息 */
  if (hwErr || fileErr || weatherErr || !hasWifi || !errMsg.isEmpty())
  {
    if (hwErr & VISION_HW_SD_ERR)
      errMsg.concat(lang[curr_lang][12]); // "未检测到SD卡\n"
    if (hwErr & VISION_HW_PROX_ERR)
      errMsg.concat(lang[curr_lang][9]); // "距离传感器初始化失败\n"
    if (hwErr & VISION_HW_ACCEL_ERR)
      errMsg.concat(lang[curr_lang][10]); // "加速度计初始化失败\n"
    if (hwErr & VISION_HW_SPIFFS_ERR)
      errMsg.concat(lang[curr_lang][57]); // "SPIFFS分区初始化失败\n"

    if (fileErr & VISION_FILE_SYS_FILE_ERR)
      errMsg.concat(lang[curr_lang][99]); // "系统文件缺失，部分功能不可用\n"
    if (fileErr & VISION_FILE_SYS_FILE_CRITICAL)
      errMsg.concat(lang[curr_lang][100]); // "关键性文件缺失，请参阅帮助文档\n"
    if (fileErr & VISION_FILE_PLAYLIST_ERR)
      errMsg.concat(lang[curr_lang][13]); // "没有可播放的文件"
    if (fileErr & VISION_FILE_PLAYLIST_CRITICAL)
      errMsg.concat(lang[curr_lang][101]); // "播放列表配置错误，请参阅帮助文档\n"
    if (fileErr & VISION_FILE_CONF_CRITICAL)
      errMsg.concat(lang[curr_lang][102]); // "配置文件错误，请参阅帮助文档\n"
    if (fileErr & VISION_FILE_STATIC_FILE_ERR)
      errMsg.concat(lang[curr_lang][99]); // "系统文件缺失，部分功能不可用\n"

    if (hasWifi)
      switch (weatherErr)
      {
      case WEATHER_RESULT_NO_CITY:
        errMsg.concat(lang[curr_lang][103]); // 天气：未配置城市
        break;
      case WEATHER_RESULT_OUT_OF_MEM:
        errMsg.concat(lang[curr_lang][104]); // 天气：内存不足
        break;
      case WEATHER_RESULT_HTTP_OPEN_FAIL:
        errMsg.concat(lang[curr_lang][105]); // 天气：HTTP请求失败
        break;
      case WEATHER_RESULT_HTTP_READ_FAIL:
        errMsg.concat(lang[curr_lang][106]); // 天气：HTTP读取失败
        break;
      case WEATHER_RESULT_JSON_DESER_FAIL:
        errMsg.concat(lang[curr_lang][107]); // 天气：JSON解析失败
        break;
      case WEATHER_RESULT_RESP_ERR:
        errMsg.concat(lang[curr_lang][108]); // 天气：响应异常
        errMsg.concat('(');
        errMsg.concat(weather.respCode);
        errMsg.concat(")\n");
        break;
      }
    else
    {
      errMsg.concat(lang[curr_lang][21]); // "无法连接至网络\n"
    }

    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      mbox = lv_msgbox_create(ui_StartupScreen, lang[curr_lang][54], errMsg.c_str(), {}, false); // LV_SYMBOL_WARNING " 错误"
      lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_center(mbox);
      xSemaphoreGive(LVGLMutex);
    }
    vTaskDelay(5000);
  }

  /* 启动硬件循环任务(按键、重力传感器、距离传感器) */
  xTaskCreatePinnedToCore(screenAdjustLoop, // 任务函数
                          "screenAdjLoop",  // 任务名称
                          4096,             // 任务堆栈大小
                          NULL,             // 任务参数
                          1,                // 任务优先级
                          NULL,             // 任务句柄
                          0);               // 执行任务核心

  // 每30s计算一次树脂数据
  esp_timer_create_args_t resinCalc_timer_args = {
      .callback = &resinCalc,
      .name = "resinCalc"};
  ESP_ERROR_CHECK(esp_timer_create(&resinCalc_timer_args, &resinCalcTimer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(resinCalcTimer, 30000000));

  // 每30分钟同步一次树脂数据
  esp_timer_create_args_t resinSync_timer_args = {
      .callback = &resinSync,
      .name = "resinSync"};
  ESP_ERROR_CHECK(esp_timer_create(&resinSync_timer_args, &resinSyncTimer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(resinSyncTimer, setting_resinSyncPeriod));

  // 每30分钟同步一次天气数据
  esp_timer_create_args_t weatherSync_timer_args = {
      .callback = &weatherSync,
      .name = "weatherSync"};
  ESP_ERROR_CHECK(esp_timer_create(&weatherSync_timer_args, &weatherSyncTimer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(weatherSyncTimer, setting_weatherSyncPeriod));

  if (!(hwErr & VISION_HW_SD_ERR) && !((fileErr & VISION_FILE_PLAYLIST_ERR) || (fileErr & VISION_FILE_PLAYLIST_CRITICAL)))
  {
    // 若有SD卡且播放列表不为空则进行播放
    loadVideoScreen(NULL);
  }
  else
  {
    // 否则切换到菜单屏
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      cleanObj(ui_StartupScreen);
      ui_MenuScreen_screen_init();                                        // 加载菜单屏
      lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true); // 切换屏幕
      xSemaphoreGive(LVGLMutex);
    }
  }

  vTaskDelete(NULL);
}

static void leaveVideoScreen(void *parameter)
{
  // 暂停解码
  if (xSemaphoreTake(MjpegMutex, portMAX_DELAY) == pdTRUE)
  {
    vTaskSuspend(playVideoHandle);
    mjpeg.pause();
    xSemaphoreGive(MjpegMutex);
  }

  // 切换屏幕
  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_group_remove_all_objs(ui_group);
    cleanObj(ui_VideoScreen);
    ui_MenuScreen_screen_init();
    lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
    xSemaphoreGive(LVGLMutex);
  }

  vTaskResume(lvglLoopHandle);
  isInLVGL = true;

  vTaskDelete(NULL);
}

static void loadVideoScreen(void *parameter)
{
  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_group_remove_all_objs(ui_group);                                  // 删除控制组内对象
    cleanObj(lv_scr_act());                                              // 释放资源
    ui_VideoScreen_screen_init();                                        // 初始化下个要显示的屏幕
    lv_scr_load_anim(ui_VideoScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true); // 切换屏幕
    lv_task_handler();                                                   // 调用任务处理器使LVGL完成操作
    vTaskSuspend(lvglLoopHandle);                                        // 挂起LVGL
    isInLVGL = false;                                                    // LVGL标志位设为false

    xSemaphoreGive(LVGLMutex);
  }

  if (mjpegInited)
  {
    // 恢复解码器工作
    vTaskResume(playVideoHandle);
    mjpeg.resume();
  }
  else
  {
    // 初始化解码器
    mjpegInit();
    mjpegInited = true;
  }

  vTaskDelete(NULL);
}

static void getDailyNoteFromResinScreen(void *parameter)
{
  String errMsg = "";
  bool updateRes = false;

  info_updatingResinData = true;

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_label_set_text(ui_NoteUpdateTimeLabel, lang[curr_lang][44]); // LV_SYMBOL_REFRESH "正在更新..."
    xSemaphoreGive(LVGLMutex);
  }

  updateRes = getDailyNote(&nd, &errMsg);

  info_updatingResinData = false;

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    if (!updateRes)
    {
      mbox = lv_msgbox_create(lv_scr_act(), lang[curr_lang][15], errMsg.c_str(), {}, false); // LV_SYMBOL_WARNING " 获取数据失败:"
      lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_center(mbox);
      lv_obj_move_foreground(mbox);
      lv_timer_t *ui_timer_ObjDelTimer = lv_timer_create(cb_timer_ScrDelTimer, 5000, mbox); // 创建定时器异步删除屏幕
    }

    lv_timer_ready(ui_timer_ResinDispTimer); // 立即更新树脂显示

    xSemaphoreGive(LVGLMutex);
  }

  vTaskDelete(NULL);
}

////////////////////
//
//  LVGL Callbacks
//
////////////////////

void cb_hardwareSetup(lv_event_t *e)
{
  xTaskCreatePinnedToCore(hardwareSetup,   // 任务函数
                          "hardwareSetup", // 任务名称
                          8192,            // 任务堆栈大小
                          NULL,            // 任务参数
                          1,               // 任务优先级
                          NULL,            // 任务句柄
                          0);              // 执行任务核心
}

void cb_getDailyNoteFromResinScreen(lv_event_t *e)
{
  xTaskCreatePinnedToCore(getDailyNoteFromResinScreen, // 任务函数
                          "getDailyNoteFRS",           // 任务名称
                          6144,                        // 任务堆栈大小
                          NULL,                        // 任务参数
                          1,                           // 任务优先级
                          NULL,                        // 任务句柄
                          0);                          // 执行任务核心
}

void cb_loadVideoScreen(lv_event_t *e)
{
  DSTATUS status;

  if (info_hasSD)
  {
    xSemaphoreTake(SDMutex, portMAX_DELAY);
    {
      status = disk_status(0); // 只有一个fatfs驱动器
      xSemaphoreGive(SDMutex);
    }
  }
  else
    status = STA_NOINIT;

  if (status == STA_NOINIT)
  {
    // SD卡状态异常进入错误信息页面
    cb_loadSDErrorInfo(e);
    return;
  }

  if (filePaths.size() < 1)
  {
    // 播放列表为空进入错误信息页面
    cb_loadPlaylistErrorInfo(e);
    return;
  }

  xTaskCreatePinnedToCore(loadVideoScreen,   // 任务函数
                          "loadVideoScreen", // 任务名称
                          3072,              // 任务堆栈大小
                          NULL,              // 任务参数
                          2,                 // 任务优先级
                          NULL,              // 任务句柄
                          1);                // 执行任务核心
}

void cb_startWifiReConfigure(lv_event_t *e)
{
  xTaskCreatePinnedToCore(wifiConfigure,     // 任务函数
                          "wifiConfigure",   // 任务名称
                          4096,              // 任务堆栈大小
                          NULL,              // 任务参数
                          1,                 // 任务优先级
                          &wifiConfigHandle, // 任务句柄
                          0);                // 执行任务核心
}

void cb_stopWifiReConfigure(lv_event_t *e)
{
  xTaskCreatePinnedToCore(stopWifiConfigure,   // 任务函数
                          "stopWifiConfigure", // 任务名称
                          4096,                // 任务堆栈大小
                          NULL,                // 任务参数
                          1,                   // 任务优先级
                          NULL,                // 任务句柄
                          0);                  // 执行任务核心
}

void cb_setAPIserver(bool status)
{
  info_setAPIstart = status;
  xTaskCreatePinnedToCore(setAPIserver_async,   // 任务函数
                          "setAPIserver_async", // 任务名称
                          4096,                 // 任务堆栈大小
                          NULL,                 // 任务参数
                          1,                    // 任务优先级
                          NULL,                 // 任务句柄
                          0);                   // 执行任务核心
}

uint16_t cb_readProx()
{
  uint16_t val;
  xSemaphoreTake(I2CMutex, portMAX_DELAY);
  val = apds.readProximity();
  xSemaphoreGive(I2CMutex);
  return val;
}

void cb_setProxThres(uint16_t val)
{
  setting_proxThres = val;
  prefs.putUInt("proxThres", val);
  apds.setProximityIntHighThreshold(setting_proxThres);
}

void setAPIserver_async(void *parameter)
{
  xSemaphoreTake(APIStartupMutex, portMAX_DELAY);
  {
    if (info_setAPIstart)
    {
      if (info_APIstatus == 1)
      {
        xSemaphoreGive(APIStartupMutex);
        vTaskDelete(NULL);
      }

      info_APIstatus = 2;
      if (connectWiFi())
      {
        startAPIServer();
        info_APIstatus = 1;
        sprintf(info_APIaddress, "http://%s", info_ipv4Address);
      }
      else
      {
        info_APIstatus = -1;
      }
    }
    else
    {
      if (info_APIstatus == 0)
      {
        xSemaphoreGive(APIStartupMutex);
        vTaskDelete(NULL);
      }

      info_APIstatus = 3;
      endAPIServer();
      info_APIstatus = 0;
      disConnectWiFi();
    }
  }
  xSemaphoreGive(APIStartupMutex);

  vTaskDelete(NULL);
}

////////////////////
//
//  Loop Functions
//
////////////////////
static void lvglLoop(void *parameter)
{
  while (1)
  {
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_timer_handler(); /* let the GUI do its work */
      xSemaphoreGive(LVGLMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

static void screenAdjustLoop(void *parameter)
{
  float accX = 0;
  float accY = 0;

  float ambientLightLux = 0;
  while (1)
  {
    pwrButton->tick();

    if (info_hasProx)
    {
      if (proxButton)
      {
        proxButton->tick();
      }

      if (!digitalRead(po.PROX_INT))
      {
        xSemaphoreTake(I2CMutex, portMAX_DELAY);
        {
          if (apds.readProximity() < setting_proxThres)
          {
            apds.clearProximityInt();
          }
        }
        xSemaphoreGive(I2CMutex);
      }
    }

    if (info_hasProx && setting_autoBright)
    {
      xSemaphoreTake(I2CMutex, portMAX_DELAY);
      {
        apds.readAmbientLightLux(ambientLightLux);
        // ESP_LOGI("screenAdjustLoop", "Lux: %f", ambientLightLux);
      }
      xSemaphoreGive(I2CMutex);

      ledcWrite(1, brightControl.updateBrightness(ambientLightLux, (setting_screenBrightness - 127) * 1.0 / 127));
    }
    else
    {
      ledcWrite(1, setting_screenBrightness);
    }

    if (info_hasAccel && setting_useAccel)
    {
      xSemaphoreTake(I2CMutex, portMAX_DELAY);
      {
        accX = acc.axisAccel(X);
        accY = acc.axisAccel(Y);
      }
      xSemaphoreGive(I2CMutex);

      int toRotate = rotation;
      if (accX >= ACC_THRES && accY >= ACC_THRES)
      {
        toRotate = 3;
      }
      else if (accX >= ACC_THRES && accY < -ACC_THRES)
      {
        toRotate = 2;
      }
      else if (accX < -ACC_THRES && accY >= ACC_THRES)
      {
        toRotate = 0;
      }
      else if (accX < -ACC_THRES && accY < -ACC_THRES)
      {
        toRotate = 1;
      }

      if (toRotate != rotation)
      {
        if (isInLVGL)
          xSemaphoreTake(LVGLMutex, portMAX_DELAY);
        xSemaphoreTake(*LCDMutexptr, portMAX_DELAY);
        {
          gfx.setRotation(toRotate);
          rotation = toRotate;
          lv_obj_invalidate(lv_scr_act());
        }
        xSemaphoreGive(*LCDMutexptr);
        if (isInLVGL)
          xSemaphoreGive(LVGLMutex);
      }
    }

    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

//********************//
//  Video Play Loop
//
//********************//
static unsigned long vfile_ms;
static unsigned long vfile_frame_start_ms;
static unsigned long vfile_frame_end_ms;
static void playVideo(void *parameter)
{
  ESP_LOGI("playVideo", "MJPEG video start");
  vfile_ms = millis();
  while (1)
  {
    vfile_frame_start_ms = millis();
    if (xSemaphoreTake(MjpegMutex, portMAX_DELAY) == pdTRUE)
    {
      if (xSemaphoreTake(MjpegReadMutex, portMAX_DELAY) == pdTRUE)
      {
        if (mjpeg.readMjpegBuf())
        {
          xSemaphoreGive(MjpegReadMutex);
          mjpeg.drawJpg();
        }
        else
        {
          xSemaphoreGive(MjpegReadMutex);
          if (!mjpeg.reload())
          {
            ESP_LOGE("playVideo", "Unable to reload video file!");
            break;
          }
          ESP_LOGI("playVideo", "Video actual play time:%ds", (int)((millis() - vfile_ms) / 1000));
          vfile_ms = millis();
        }
      }
      xSemaphoreGive(MjpegMutex);
    }

    vfile_frame_end_ms = millis();
    if ((vfile_frame_end_ms - vfile_frame_start_ms) < (1000 / VIDEO_FPS))
    {
      vTaskDelay(pdMS_TO_TICKS(1000 / VIDEO_FPS + vfile_frame_start_ms - vfile_frame_end_ms));
    }
    // ESP_LOGI("playVideo", "Current FPS:%d", (int)(1000 / (vfile_frame_end_ms - vfile_frame_start_ms)));
  }
  vTaskDelete(NULL);
}

////////////////////////
//
//  Resin Functions
//
////////////////////////
static bool getDailyNote(Notedata *nd, String *errMsg)
{
  if (!connectWiFi())
  {
    errMsg->concat(lang[curr_lang][20]); // "无法连接至网络\n"
    return false;
  }

  bool res = true;

  struct tm timeinfo;
  if (!info_timeSynced)
  {
    ESP_LOGE("getDailyNote", "Time not obtained");
    res = false;
    errMsg->concat(lang[curr_lang][21]); // "同步时间失败\n"
  }
  else if (getLocalTime(&timeinfo, 50)) // <- 获取时间50ms超时
  {
    info_timeSynced = true;
    int r = 0;
    if (xSemaphoreTake(NoteDataMutex, portMAX_DELAY) == pdTRUE)
    {
      r = hyc.syncDailyNote(nd);
      xSemaphoreGive(NoteDataMutex);
    }

    if (r < 0)
    {
      if (nd->respCode == 1034)
      {
        errMsg->concat(lang[curr_lang][53]); // "错误1034：\n请使用米游社app查看体力后重试\n"
      }
      else
      {
        errMsg->concat(lang[curr_lang][22]); // "网络响应异常"
        errMsg->concat('(');
        errMsg->concat(nd->respCode);
        errMsg->concat(")\n");
      }
      res = false;
    }
    else if (r == 0)
    {
      errMsg->concat(lang[curr_lang][23]); //"未配置cookie\n"
      res = false;
    }
  }

  disConnectWiFi();

  return res;
}

static void resinCalc(void *parameter)
{
  if (xSemaphoreTake(NoteDataMutex, portMAX_DELAY) == pdTRUE)
  {
    HoyoverseClient::updateDailyNote(&nd);
    xSemaphoreGive(NoteDataMutex);
  }
}

static void resinSync(void *parameter)
{
  if (info_timeSynced && connectWiFi())
  {
    if (xSemaphoreTake(NoteDataMutex, portMAX_DELAY) == pdTRUE)
    {
      hyc.syncDailyNote(&nd);
      xSemaphoreGive(NoteDataMutex);
    }
    disConnectWiFi();
  }
}

static void weatherSync(void *parameter)
{
  if (connectWiFi())
  {
    wp->getCurrentWeather(&weather);
    disConnectWiFi();
  }
}

static void onChangeVideo()
{
  if (isInLVGL)
  {
    // 若在lvgl中则忽略距离传感器双击
    return;
  }

  int fileNo = prefs.getUInt("currFileId", 0);
  if (fileNo + 1 < filePaths.size())
  {
    fileNo += 1;
  }
  else
  {
    fileNo = 0;
  }

  if (xSemaphoreTake(MjpegReadMutex, portMAX_DELAY) == pdTRUE)
  {
    if (mjpeg.switchFile(filePaths.get(fileNo).c_str()))
    {
      vfile_ms = millis();
      prefs.putUInt("currFileId", fileNo);
    }
    xSemaphoreGive(MjpegReadMutex);
  }
}

////////////////////////
//
//  Button Callbacks
//
////////////////////////
static bool inEditMode = false;
static void onSingleClick()
{
  if (!isInLVGL)
  {
    return;
  }

  xSemaphoreTake(LVGLMutex, portMAX_DELAY);
  {
    if (inEditMode)
    {
      lv_group_send_data(lv_group_get_default(), LV_KEY_RIGHT);
    }
    else
    {
      lv_group_send_data(lv_group_get_default(), LV_KEY_NEXT);
      lv_group_focus_next(lv_group_get_default());
    }
  }
  xSemaphoreGive(LVGLMutex);
}

static void onDoubleClick()
{
  if (!isInLVGL)
  {
    // 若在视频播放界面则返回主菜单
    xTaskCreatePinnedToCore(leaveVideoScreen, "leaveVideoScr", 3072, NULL, 2, NULL, 1);
  }

  xSemaphoreTake(LVGLMutex, portMAX_DELAY);
  {
    if (inEditMode)
    {
      lv_group_send_data(lv_group_get_default(), LV_KEY_ENTER);
      inEditMode = false;
      xSemaphoreGive(LVGLMutex);
      return;
    }
    else if (lv_obj_is_editable(lv_group_get_focused(lv_group_get_default())))
    {
      lv_group_send_data(lv_group_get_default(), LV_KEY_ENTER);
      inEditMode = true;
      xSemaphoreGive(LVGLMutex);
      return;
    }
    else
    {
      lv_event_send(lv_group_get_focused(lv_group_get_default()), LV_EVENT_CLICKED, NULL);
    }
  }
  xSemaphoreGive(LVGLMutex);
}

static void onMultiClick()
{
  if (!isInLVGL)
  {
    // 若在视频播放界面则切换视频
    onChangeVideo();
  }

  xSemaphoreTake(LVGLMutex, portMAX_DELAY);
  {
    if (inEditMode)
    {
      lv_group_send_data(lv_group_get_default(), LV_KEY_LEFT);
    }
    else
    {
      lv_group_send_data(lv_group_get_default(), LV_KEY_PREV);
      lv_group_focus_prev(lv_group_get_default());
    }
  }
  xSemaphoreGive(LVGLMutex);
}