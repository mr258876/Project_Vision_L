#include "conf.h"
#include "rtos_externs.h"
#include "The_Vision_L_globals.h"

#include <FS.h>
#include <SD.h>
#include <SD_MMC.h>

#include <Update.h>

#include <lvgl.h>
#include "lv_fs_fatfs.h"
#include "ui.h"
#include "ui_supply_functions.h"

#include <ArduinoJson.h>
#include "LinkedList.h"
#include <Preferences.h>

#include "LCD.h"
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

#include "MjpegClass.h"

#if defined(_CONFIG_PROX_LIGHT_USE_APDS9960_)
#include "APDS9960.h"
#elif defined(_CONFIG_PROX_LIGHT_USE_APDS9930_)
#include "APDS9930.h"
#endif

#include <OneButton.h>
#include <kxtj3-1057.h>
#undef getName

#include <WiFi.h>
#include <esp_now.h>

#include "Hoyoverse.h"

// Freertos
#include "rtc_wdt.h"

////////////////////////
//
//  Typedef
//
////////////////////////
typedef enum
{
  VISION_HW_OK = 0,
  VISION_HW_SENSOR_ERR,
  VISION_HW_SD_ERR
} vision_hw_result_t;

typedef enum
{
  VISION_NO_UPDATE = 0,     // No update file
  VISION_UPDATE_BAD_FILE,   // not a updateable file
  VISION_UPDATE_START_FAIL, // Update start failed
  VISION_UPDATE_STARTED,    // Update started
  VISION_UPDATE_OK          // Update finished (probably never gonna to use)
} vision_update_result_t;

////////////////////////
//
//  Variables
//
////////////////////////
/* Pwr button & Audio */
uint8_t audioPin = 25;
uint8_t pwrBtnPin = 26;
static OneButton *pwrButton;

/* LCD screen */
static LCD_panel_t LCD_panel = LCD_ST7789;
static LGFX_Device gfx;

/* LVGL Stuff */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;
unsigned long startup_time;
bool isInLVGL = true;

/* Things of files */
static LinkedList<String> filePaths;
uint8_t fileCount = 0;
uint8_t *vFileReadBuf = (uint8_t *)malloc(MJPEG_BUFFER_SIZE);

/* Mjpeg decoder & Image Buffers */
static MjpegClass mjpeg;
bool mjpegInited = false;

/* Proximity sensor Object */
PROX_LIGHT_METER apds;
uint16_t r, g, b, c;
OneButton *proxButton;

/* Accelmeter Object */
#define LOW_POWER
KXTJ3 acc(0x0E);
int rotation = 0;

/* NVS */
Preferences prefs;

/* Booleans for whether the sensors enabled. */
bool useProx;
bool useAcc;
bool useAutoBrightness;

////////////////////////
//
//  Function Declartions
//
////////////////////////
bool checkSDFiles(String *errMsg);
vision_update_result_t updateFromSD(String *errMsg);
vision_hw_result_t checkHardware(String *errMsg);
void wifiConfigure();
bool getDailyNote(Notedata *nd, String *errMsg);
void resinCalc(void *parameter);
bool connectWiFi();

void cb_switchToVideoScreen();
void mjpegInit();
void leaveVideoScreen(void *parameter);
void loadVideoScreen(void *parameter);
void playVideo(void *parameter);

void getDailyNoteFromResinScreen(void *parameter);

void lvglLoop(void *parameter);
void screenAdjustLoop(void *parameter);

void onChangeVideo();
void onSingleClick();
void onDoubleClick();
void onMultiClick();

////////////////////////
//
//  Functions
//
////////////////////////
/**
 *
 * @brief Custom scren update function for LVGL
 *
 */
void disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  if (xSemaphoreTake(LCDMutex, portMAX_DELAY) == pdTRUE)
  {
    gfx.setAddrWindow(area->x1, area->y1, w, h);
    gfx.pushPixelsDMA((uint16_t *)&color_p->full, w * h);
    xSemaphoreGive(LCDMutex);
  }

  lv_disp_flush_ready(disp);
}

/* Setup Function */
void setup()
{
  // Disable watchdog write protect to feed manually
  rtc_wdt_protect_off();

  // SD card Pull-Ups
  pinMode(DAT0, INPUT_PULLUP);
  pinMode(DAT1, INPUT_PULLUP);
  pinMode(DAT2, INPUT_PULLUP);
  pinMode(DAT3, INPUT_PULLUP);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(CMD, INPUT_PULLUP);

  // Enable Serial output
  Serial.begin(115200);

  // Init NVS
  prefs.begin("Project_Vision", false);

// SD card init
#ifdef _CONFIG_SD_USE_SPI_
  SPIClass SDSPI = SPIClass(HSPI);
  SDSPI.begin(CLK, DAT0, CMD, DAT3);
  SD.begin(DAT3, SDSPI, 80000000);
#endif
#ifdef _CONFIG_SD_USE_SDMMC_1BIT_
  SD_MMC.begin("/sdcard", true);
#endif
#ifdef _CONFIG_SD_USE_SDMMC_4BIT_
  SD_MMC.begin();
#endif

  // Check 
  if (digitalRead(audioPin) == HIGH)
  {
    audioPin = 26;
    pwrBtnPin = 25;
    LCD_panel = LCD_GC9A01;
  }

  // Buttons
  pwrButton = new OneButton(pwrBtnPin, true);
  proxButton = new OneButton(PROX_INT, true);

  // Audio Output
  pinMode(audioPin, INPUT_PULLDOWN);

  // Init Display
  LCDinit(&gfx, LCD_panel);
  gfx.init();
  gfx.setColorDepth(16);
  gfx.setSwapBytes(false);
  gfx.fillScreen(TFT_BLACK);

  ledcAttachPin(LCD_BL, 1);     // assign TFT_BL pin to channel 1
  ledcSetup(1, 12000, 8);       // 12 kHz PWM, 8-bit resolution
  ledcWrite(1, LCD_BRIGHTNESS); // brightness 0 - 255

  lv_init();

  screenWidth = gfx.width();
  screenHeight = gfx.height();

  if (!vFileReadBuf)
  {
    LV_LOG_ERROR("Video file buffer allocate failed!");
  }

  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 32, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

  if (!disp_draw_buf)
  {
    LV_LOG_ERROR("LVGL disp_draw_buf allocate failed!");
  }
  else
  {
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 32);

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

    xTaskCreatePinnedToCore(lvglLoop,        //任务函数
                            "lvglLoop",      //任务名称
                            8192,            //任务堆栈大小
                            NULL,            //任务参数
                            1,               //任务优先级
                            &lvglLoopHandle, //任务句柄
                            1);              //执行任务核心

    LV_LOG_INFO("LVGL booted.");
  }

  // vTaskDelete(NULL);
}

void mjpegInit()
{
  // Mjpeg初始化
  int fileNo = prefs.getUInt("currFileId", 0);
  if (!mjpeg.setup(filePaths.get(fileNo).c_str(), vFileReadBuf, &gfx, true, screenWidth, screenHeight))
  {
    LV_LOG_ERROR("Mjpeg decoder init failed!");
  }

  // Create task of video playing
  xTaskCreatePinnedToCore(playVideo,        //任务函数
                          "playVideo",      //任务名称
                          2048,             //任务堆栈大小
                          NULL,             //任务参数
                          2,                //任务优先级
                          &playVideoHandle, //任务句柄
                          1);               //执行任务核心
}

static int switchScreenDelay = 0;
void switchToVideoScreen(void *delayTime)
{
  // 等待延时
  vTaskDelay(pdMS_TO_TICKS(*((int *)delayTime)));

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    // 删除样式解决内存泄露
    removeStyles(lv_scr_act());

    ui_VideoScreen_screen_init();

    // 切换屏幕
    lv_scr_load_anim(ui_VideoScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);

    lv_task_handler();

    vTaskSuspend(lvglLoopHandle);
    isInLVGL = false;

    xSemaphoreGive(LVGLMutex);
  }

  if (!mjpegInited)
  {
    mjpegInit();
    mjpegInited = true;
  }

  vTaskDelete(NULL);
}

////////////////////////
//
//  Hardware Checkup
//
////////////////////////
vision_hw_result_t checkHardware(String *errMsg)
{
  vision_hw_result_t hwErrDetected = VISION_HW_OK;
  // lv_label_set_text(ui_StartupLabel2, "检查距离传感器...");
  if (apds.begin())
  {
    apds.enableColor(true);
    apds.enableProximity(true);
    apds.setProximityInterruptThreshold(0, PROX_THRS);
    apds.enableProximityInterrupt();
    pinMode(PROX_INT, INPUT_PULLUP);
    proxButton->attachDoubleClick(onChangeVideo);
    useProx = true;
    useAutoBrightness = true;
  }
  else
  {
    hwErrDetected = VISION_HW_SENSOR_ERR;
    errMsg->concat("距离传感器初始化失败\n");
    useProx = false;
    LV_LOG_ERROR("Prox sensor init failed!");
  }

  // lv_label_set_text(ui_StartupLabel2, "检查加速度计...");
  if (acc.begin(ACC_SAMPLE_RATE, ACC_RANGE) == 0)
  {
    useAcc = true;
  }
  else
  {
    hwErrDetected = VISION_HW_SENSOR_ERR;
    errMsg->concat("加速度计初始化失败\n");
    useAcc = false;
    LV_LOG_ERROR("IMU init failed!");
  }

  // lv_label_set_text(ui_StartupLabel2, "检查SD卡...");
  switch (SD_CLASS.cardType())
  {
  case CARD_MMC:
  case CARD_SD:
  case CARD_SDHC:
    break;
  case CARD_UNKNOWN:
    hwErrDetected = VISION_HW_SD_ERR;
    errMsg->concat("SD卡无法读取\n");
    LV_LOG_ERROR("Bad SD Card!");
    break;
  default:
    hwErrDetected = VISION_HW_SD_ERR;
    errMsg->concat("未检测到SD卡\n");
    LV_LOG_ERROR("No SD Card!");
  }

  return hwErrDetected;
}

bool checkSDFiles(String *errMsg)
{
  bool fileErrDetected = false;
  // lv_label_set_text(ui_StartupLabel2, "正在检查文件...");

  // 读取播放文件列表
  File f = SD_CLASS.open(PLAY_FILE_CONF_PATH);
  if (!f || f.isDirectory())
  {
    f.close();
    f = SD_CLASS.open(PLAY_FILE_CONF_PATH, FILE_WRITE, true);
    f.print(PLAY_FILE_DEFAULT_CONF);
    f.close();
    f = SD_CLASS.open(PLAY_FILE_CONF_PATH);
  }

  StaticJsonDocument<0> filter;
  filter.set(true);

  StaticJsonDocument<JSON_CONF_BUFFER_SIZE> doc;

  DeserializationError error = deserializeJson(doc, f, DeserializationOption::Filter(filter));

  if (error)
  {
    errMsg->concat(error.c_str());
    LV_LOG_ERROR("deserializeJson() failed:%s", error.c_str());
    return true;
  }

  f.close();

  JsonArray files = doc["files"];

  filePaths.clear();
  for (const char *fp : files)
  {
    lv_fs_res_t _input_op_result;
    lv_fs_file_t _input;
    _input_op_result = lv_fs_open(&_input, fp, LV_FS_MODE_RD);
    if (_input_op_result == LV_FS_RES_OK)
    {
      filePaths.add(String(fp));
    }
    lv_fs_close(&_input);
  }

  files.clear();
  doc.clear();

  fileCount = filePaths.size();
  if (fileCount < 1)
  {
    errMsg->concat("没有可播放的文件");
    return true;
  }

  // 读取米游社配置
  f = SD_CLASS.open(HOYOLAB_CONF_PATH);
  if (!f || f.isDirectory())
  {
    f.close();
    f = SD_CLASS.open(HOYOLAB_CONF_PATH, FILE_WRITE, true);
    f.print(HOYOLAB_DEFAULT_CONF);
    f.close();
    f = SD_CLASS.open(HOYOLAB_CONF_PATH);
  }

  error = deserializeJson(doc, f, DeserializationOption::Filter(filter));

  if (error)
  {
    errMsg->concat(error.c_str());
    LV_LOG_ERROR("deserializeJson() failed:%s", error.c_str());
    return true;
  }

  f.close();

  const char *uid = doc["uid"];
  const char *cookie = doc["cookie"];
  hyc.begin(cookie, uid);

  doc.clear();

  // LV_FONT_DECLARE(ui_font_HanyiWenhei16);
  // LV_FONT_DECLARE(ui_font_HanyiWenhei24);

  return fileErrDetected;
}

void cb_switchToVideoScreen()
{
  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_label_set_text(ui_StartupLabel2, "请稍候...");
    xSemaphoreGive(LVGLMutex);
  }

  xTaskCreatePinnedToCore(screenAdjustLoop, //任务函数
                          "screenAdjLoop",  //任务名称
                          2560,             //任务堆栈大小
                          NULL,             //任务参数
                          1,                //任务优先级
                          NULL,             //任务句柄
                          1);               //执行任务核心

  // 每30s计算一次树脂数据
  esp_timer_create_args_t resinCalc_timer_args = {
      .callback = &resinCalc,
      .name = "resinCalc"};
  ESP_ERROR_CHECK(esp_timer_create(&resinCalc_timer_args, &resinCalcTimer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(resinCalcTimer, 30000000));

  // 每15分钟同步一次树脂数据
  // esp_timer_create_args_t resinSync_timer_args = {
  //     .callback = &resinSync,
  //     .name = "resinSync"};
  // ESP_ERROR_CHECK(esp_timer_create(&resinSync_timer_args, &resinSyncTimer));
  // ESP_ERROR_CHECK(esp_timer_start_periodic(resinSyncTimer, 15000000));

  switchScreenDelay = 2500;

  xTaskCreatePinnedToCore(switchToVideoScreen,        //任务函数
                          "swToVideoScr",             //任务名称
                          4096,                       //任务堆栈大小
                          (void *)&switchScreenDelay, //任务参数
                          1,                          //任务优先级
                          NULL,                       //任务句柄
                          0);                         //执行任务核心
}

void hardwareSetup(void *parameter)
{
  startup_time = millis();
  vision_hw_result_t hwErr;
  vision_update_result_t updateStatus = VISION_NO_UPDATE;
  bool fileErr = false;
  String errMsg = "";

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_label_set_text(ui_StartupLabel2, "正在检查硬件...");
    xSemaphoreGive(LVGLMutex);
  }
  hwErr = checkHardware(&errMsg);

  if (hwErr != VISION_HW_SD_ERR)
  {
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_label_set_text(ui_StartupLabel2, "正在检查文件...");
      xSemaphoreGive(LVGLMutex);
    }
    updateStatus = updateFromSD(&errMsg);
    fileErr = checkSDFiles(&errMsg);
  }

  if (updateStatus == VISION_UPDATE_STARTED)
  {
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_label_set_text(ui_StartupLabel1, "正在升级...");
      lv_label_set_text(ui_StartupLabel2, "请不要关闭电源\n或拔出SD卡");
      xSemaphoreGive(LVGLMutex);
    }

    vTaskDelete(NULL);
  }

  // 若检查到错误则停止启动
  if (hwErr == VISION_HW_SD_ERR || fileErr || updateStatus)
  {
    ESP_LOGE("hardwareSetup", "Hardware err Detected!!!");
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_obj_t *mbox = lv_msgbox_create(ui_StartupScreen, LV_SYMBOL_WARNING " 发现如下问题,启动已终止:", errMsg.c_str(), {}, false);
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
      lv_obj_clean(ui_StartupScreen);

      lv_obj_t *ui_NetConfigureTitle = lv_label_create(ui_StartupScreen);

      lv_obj_set_width(ui_NetConfigureTitle, LV_SIZE_CONTENT);
      lv_obj_set_height(ui_NetConfigureTitle, LV_SIZE_CONTENT);

      lv_obj_set_x(ui_NetConfigureTitle, 25);
      lv_obj_set_y(ui_NetConfigureTitle, 35);

      lv_label_set_text(ui_NetConfigureTitle, "网络配置");

      lv_obj_set_style_text_color(ui_NetConfigureTitle, lv_color_hex(0xD3BC8E), LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_text_opa(ui_NetConfigureTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_text_font(ui_NetConfigureTitle, &ui_font_HanyiWenhei24ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

      lv_obj_t *ui_NetConfigureLabel = lv_label_create(ui_StartupScreen);

      lv_obj_set_width(ui_NetConfigureLabel, LV_SIZE_CONTENT);
      lv_obj_set_height(ui_NetConfigureLabel, LV_SIZE_CONTENT);

      lv_obj_set_x(ui_NetConfigureLabel, 30);
      lv_obj_set_y(ui_NetConfigureLabel, 85);

      lv_label_set_text(ui_NetConfigureLabel,
                        "神之眼的配置及部分功能\n依赖网络。\n\n使用微信\n扫描右侧\nQR码配\n置网络。");

      lv_obj_set_style_text_color(ui_NetConfigureLabel, lv_color_hex(0xECE5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_text_opa(ui_NetConfigureLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_text_font(ui_NetConfigureLabel, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);

      lv_obj_t *qr = lv_qrcode_create(ui_StartupScreen, 100, lv_color_black(), lv_color_white());

      /*Set data*/
      const char *data = "http://iot.espressif.cn/configWXDeviceWiFi.html";
      lv_qrcode_update(qr, data, strlen(data));
      lv_obj_set_x(qr, 105);
      lv_obj_set_y(qr, 110);

      /*Add a border with bg_color*/
      lv_obj_set_style_border_color(qr, lv_color_white(), 0);
      lv_obj_set_style_border_width(qr, 5, 0);
      xSemaphoreGive(LVGLMutex);
    }

    wifiConfigure();

    vTaskDelete(NULL);
  }
  else
  {
    // 若有已保存网络则尝试获取树脂数据
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_label_set_text(ui_StartupLabel2, "连接至网络...");
      xSemaphoreGive(LVGLMutex);
    }

    if (!getDailyNote(&nd, &errMsg))
    {
      lv_obj_t *mbox;
      if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
      {
        lv_obj_t *mbox = lv_msgbox_create(ui_StartupScreen, LV_SYMBOL_WARNING " 获取数据失败:", errMsg.c_str(), {}, false);
        lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_center(mbox);
        xSemaphoreGive(LVGLMutex);

        vTaskDelay(5000);

        xSemaphoreTake(LVGLMutex, portMAX_DELAY);
        // removeStyles(mbox);
        lv_obj_del(mbox);
        xSemaphoreGive(LVGLMutex);
      }
    }
  }

  pinMode(pwrBtnPin, INPUT);
  pwrButton->attachClick(onSingleClick);
  pwrButton->attachDoubleClick(onDoubleClick);
  pwrButton->attachMultiClick(onMultiClick);

  cb_switchToVideoScreen();

  vTaskDelete(NULL);
}

void wifiConfigure()
{
  // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector

  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig(SC_TYPE_ESPTOUCH_AIRKISS);

  // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 1); // disable brownout detector

  ESP_LOGI("wifiConfigure", "Waiting for Smartconfig...");

  while (!WiFi.smartConfigDone() || WiFi.status() != WL_CONNECTED)
  {
    vTaskDelay(pdMS_TO_TICKS(500));
  }

  ESP_LOGI("wifiConfigure", "Smartconfig success!");

  prefs.putString("wifiSSID1", WiFi.SSID());
  prefs.putString("wifiPSWD1", WiFi.psk());
  prefs.putUInt("wifiConfigured", 1);
  WiFi.stopSmartConfig();

  esp_restart();
}

bool connectWiFi()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    return true;
  }

  WiFi.mode(WIFI_STA);
  int wifiCount = WiFi.scanNetworks(false, true, false, 300, 0, prefs.getString("wifiSSID1").c_str());
  // WiFi.scanDelete();
  if (wifiCount < 1)
  {
    WiFi.mode(WIFI_OFF);
    return false;
  }

  WiFi.begin();
  unsigned long startConnect_ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    vTaskDelay(500);
    if (millis() - startConnect_ms > 10000)
    {
      WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);
      return false;
    }
  }
  return true;
}

void leaveVideoScreen(void *parameter)
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
    removeStyles(lv_scr_act());
    ui_MenuScreen_screen_init();
    lv_scr_load_anim(ui_MenuScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
    xSemaphoreGive(LVGLMutex);
  }

  vTaskResume(lvglLoopHandle);
  isInLVGL = true;

  vTaskDelete(NULL);
}

void loadVideoScreen(void *parameter)
{
  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_group_remove_all_objs(ui_group);                                  // 删除控制组内对象
    ui_VideoScreen_screen_init();                                        // 初始化下个要显示的屏幕
    lv_scr_load_anim(ui_VideoScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false); // 切换屏幕
    lv_async_call(delScr, ui_MenuScreen);                                // 异步释放资源
    lv_task_handler();                                                   // 调用任务处理器使LVGL完成操作
    vTaskSuspend(lvglLoopHandle);                                        // 挂起LVGL
    isInLVGL = false;                                                    // LVGL标志位设为false

    xSemaphoreGive(LVGLMutex);
  }

  // 恢复解码器工作
  vTaskResume(playVideoHandle);
  mjpeg.resume();

  vTaskDelete(NULL);
}

void getDailyNoteFromResinScreen(void *parameter)
{
  String errMsg = "";
  bool updateRes = false;

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_label_set_text(ui_NoteUpdateTimeLabel, LV_SYMBOL_REFRESH "正在更新...");
    xSemaphoreGive(LVGLMutex);
  }

  updateRes = getDailyNote(&nd, &errMsg);

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    if (!updateRes)
    {
      lv_obj_t *mbox = lv_msgbox_create(lv_scr_act(), LV_SYMBOL_WARNING " 获取数据失败:", errMsg.c_str(), {}, false);
      lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_center(mbox);
      lv_obj_move_foreground(mbox);
      xSemaphoreGive(LVGLMutex);

      vTaskDelay(5000);

      xSemaphoreTake(LVGLMutex, portMAX_DELAY);
      // removeStyles(mbox);
      lv_obj_del(mbox);
    }

    lv_timer_ready(ui_timer_ResinDispTimer); // 立即更新树脂显示

    xSemaphoreGive(LVGLMutex);
  }

  vTaskDelete(NULL);
}

//*****************************/
//  Updating from SD
//
//*****************************/
vision_update_result_t updateFromSD(String *errMsg)
{
  File f = SD_CLASS.open(UPDATE_FILE_PATH);
  if (!f)
  {
    f.close();
    return VISION_NO_UPDATE;
  }

  if (f.isDirectory() || f.size() < 1024)
  {
    f.close();
    errMsg->concat("升级文件错误\n");
    return VISION_UPDATE_BAD_FILE;
  }

  size_t fSize = f.size();

  if (!Update.begin(fSize))
  {
    f.close();
    errMsg->concat("升级程序启动失败\n");
    return VISION_UPDATE_START_FAIL;
  }

  LV_LOG_INFO("Start update...");
  Update.writeStream(f);

  if (Update.end())
  {
    if (Update.isFinished())
    {
      LV_LOG_INFO("Update finished!");
      f.close();
      SD_CLASS.remove(UPDATE_FILE_PATH);
      esp_restart();
    }
  }

  f.close();

  if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
  {
    lv_obj_t *mbox = lv_msgbox_create(ui_StartupScreen, LV_SYMBOL_WARNING " 更新失败", "请通过串口手动更新固件", {}, false);
    lv_obj_set_style_text_font(mbox, &ui_font_HanyiWenhei16ZhHans, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(mbox);
    xSemaphoreGive(LVGLMutex);
  }
  return VISION_UPDATE_STARTED;
}

////////////////////
//
//  LVGL Callbacks
//
////////////////////

void cb_hardwareSetup(lv_event_t *e)
{
  xTaskCreatePinnedToCore(hardwareSetup,   //任务函数
                          "hardwareSetup", //任务名称
                          8192,            //任务堆栈大小
                          NULL,            //任务参数
                          1,               //任务优先级
                          NULL,            //任务句柄
                          0);              //执行任务核心
}

void cb_getDailyNoteFromResinScreen(lv_event_t *e)
{
  xTaskCreatePinnedToCore(getDailyNoteFromResinScreen, //任务函数
                          "getDailyNoteFRS",           //任务名称
                          6144,                        //任务堆栈大小
                          NULL,                        //任务参数
                          1,                           //任务优先级
                          NULL,                        //任务句柄
                          0);                          //执行任务核心
}

void cb_loadVideoScreen(lv_event_t *e)
{
  xTaskCreatePinnedToCore(loadVideoScreen,   //任务函数
                          "loadVideoScreen", //任务名称
                          3072,              //任务堆栈大小
                          NULL,              //任务参数
                          2,                 //任务优先级
                          NULL,              //任务句柄
                          1);                //执行任务核心
}

////////////////////
//
//  Loop Functions
//
////////////////////
void loop()
{
  ESP_LOGI("loop", "Free MEM:%d\n", esp_get_free_heap_size());
  vTaskDelay(pdMS_TO_TICKS(5000));
}

void lvglLoop(void *parameter)
{
  while (1)
  {
    if (xSemaphoreTake(LVGLMutex, portMAX_DELAY) == pdTRUE)
    {
      lv_timer_handler(); /* let the GUI do its work */
      xSemaphoreGive(LVGLMutex);
    }
  }
}

void screenAdjustLoop(void *parameter)
{
  float accX = 0;
  float accY = 0;
  while (1)
  {
    pwrButton->tick();

    if (useProx)
    {
      proxButton->tick();
      if (!digitalRead(PROX_INT))
      {
        if (apds.readProximity() < PROX_THRS)
        {
          apds.clearInterrupt();
        }
      }

      if (useAutoBrightness)
      {
        apds.getColorData(&r, &g, &b, &c);
        int light = (c / 2) > 191 ? 191 : (c / 2);
        light += 64;
        ledcWrite(1, light);
      }
    }

    if (useAcc)
    {
      accX = acc.axisAccel(X);
      accY = acc.axisAccel(Y);
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
        if (xSemaphoreTake(LCDMutex, portMAX_DELAY) == pdTRUE)
        {
          gfx.setRotation(toRotate);
          rotation = toRotate;
          lv_obj_invalidate(lv_scr_act());
          xSemaphoreGive(LCDMutex);
        }
      }
    }

    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

//********************//
//  Video Play Loop
//
//********************//
unsigned long vfile_ms;
unsigned long vfile_frame_start_ms;
unsigned long vfile_frame_end_ms;
void playVideo(void *parameter)
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
    // LV_LOG_WARN("Current FPS:%d", (int)(1000 / (vfile_frame_end_ms - vfile_frame_start_ms)));
  }
  vTaskDelete(NULL);
}

////////////////////////
//
//  Resin Functions
//
////////////////////////
bool getDailyNote(Notedata *nd, String *errMsg)
{
  if (!connectWiFi())
  {
    errMsg->concat("无法连接至网络\n");
    return false;
  }

  bool res = true;

  configTime(GMTOFFSET, DAYLIGHTOFFSET, "pool.ntp.org");

  struct tm timeinfo;
  unsigned long ntp_start_ms = millis();
  while (!getLocalTime(&timeinfo))
  {
    vTaskDelay(100);
    if (millis() - ntp_start_ms > 10000)
    {
      ESP_LOGE("getDailyNote", "Failed to obtain time");
      res = false;
      errMsg->concat("同步时间失败\n");
      break;
    }
  }

  if (getLocalTime(&timeinfo))
  {
    int r = 0;
    if (xSemaphoreTake(NoteDataMutex, portMAX_DELAY) == pdTRUE)
    {
      r = hyc.syncDailyNote(nd);
      xSemaphoreGive(NoteDataMutex);
    }

    if (r < 0)
    {
      errMsg->concat("网络响应异常\n");
      res = false;
    }
    else if (r == 0)
    {
      errMsg->concat("未配置cookie\n");
      res = false;
    }
  }

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  return res;
}

void resinCalc(void *parameter)
{
  if (xSemaphoreTake(NoteDataMutex, portMAX_DELAY) == pdTRUE)
  {
    HoyoverseClient::updateDailyNote(&nd);

    xSemaphoreGive(NoteDataMutex);
  }
}

void onChangeVideo()
{
  int fileNo = prefs.getUInt("currFileId", 0);
  if (fileNo + 1 < fileCount)
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
bool inEditMode = false;
void onSingleClick()
{
  if (isInLVGL)
  {
    if (inEditMode)
    {
      lv_group_send_data(ui_group, LV_KEY_RIGHT);
    }
    else
    {
      lv_group_send_data(ui_group, LV_KEY_NEXT);
      lv_group_focus_next(ui_group);
    }
  }
}

void onDoubleClick()
{
  if (isInLVGL)
  {
    // lv_group_send_data(ui_group, LV_KEY_ENTER);
    lv_event_send(lv_group_get_focused(ui_group), LV_EVENT_CLICKED, NULL);

    if (inEditMode)
    {
      inEditMode = false;
      lv_obj_clear_state(lv_group_get_focused(ui_group), LV_STATE_PRESSED);
      return;
    }

    if (lv_obj_is_editable(lv_group_get_focused(ui_group)))
    {
      inEditMode = true;
      lv_obj_add_state(lv_group_get_focused(ui_group), LV_STATE_PRESSED);
      return;
    }
  }
  else
  {
    xTaskCreatePinnedToCore(leaveVideoScreen, //任务函数
                            "leaveVideoScr",  //任务名称
                            3072,             //任务堆栈大小
                            NULL,             //任务参数
                            2,                //任务优先级
                            NULL,             //任务句柄
                            1);               //执行任务核心
  }
}

void onMultiClick()
{
  if (isInLVGL)
  {
    if (inEditMode)
    {
      lv_group_send_data(ui_group, LV_KEY_LEFT);
    }
    else
    {
      lv_group_send_data(ui_group, LV_KEY_PREV);
      lv_group_focus_prev(ui_group);
    }
  }
  else
  {
    onChangeVideo();
  }
}